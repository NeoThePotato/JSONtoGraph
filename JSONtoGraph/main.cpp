#include <iostream>
#include <stdexcept>
#include "File.h"
#include "GraphLinkedList.h"
#include "Graph2DArray.h"
using std::cout, std::endl, std::cin;

constexpr size_t START_INDEX = 0;
constexpr size_t SHORTEST_PATH_START_INDEX = 1;
constexpr unsigned int INPUT_LINKED_LIST = 1;
constexpr unsigned int INPUT_2D_ARRAY = 2;
constexpr const char* JSON_PATH = "source.json";

static Graph::Graph* CreateGraph()
{
    cout << "Select graph implementation\n" << INPUT_LINKED_LIST << ": Linked List\n" << INPUT_2D_ARRAY << ": 2D Array" << endl;
    unsigned int selection;
    while (true)
    {
        cin >> selection;
        if (selection == INPUT_LINKED_LIST || selection == INPUT_2D_ARRAY)
            break;
        else
            cout << "Invalid Input." << endl;
    }
    switch (selection)
    {
    case INPUT_LINKED_LIST:
        return new Graph::GraphLinkedList();
    case INPUT_2D_ARRAY:
        return new Graph::Graph2DArray();
    default:
        return nullptr;
    }
}

static bool LoadFromJson(const char * path, Graph::Graph* graph)
{
    try
    {
        return IO::File::LoadFromJson(path, graph);
    }
    catch (std::exception e)
    {
        cout << "Failed to load JSON file:\n" << e.what() << endl;
        return false;
    }
}

static void PrintGraph(const Graph::Graph* graph)
{
    cout << "Loaded Graph:\nVertices:\n";
    for (size_t i = START_INDEX; i < graph->VertexCount(); i++)
        cout << '\t' << graph->VertexAt(i) << '\n';
    cout << "Edges:\n";
    for (size_t i = START_INDEX; i < graph->EdgeCount(); i++)
        cout << "\t(" << graph->EdgeAt(i).v1 << ", " << graph->EdgeAt(i).v2 << ")\n";
    cout << endl;
}

static void SelectVertex(const Graph::Graph* graph, Graph::Vertex* vertex)
{
    while (true)
    {
        cin >> *vertex;
        if (graph->Exists(*vertex))
            break;
        else
            cout << *vertex << " is not a vertex in graph." << endl;
    }
}

static void SelectPath(const Graph::Graph* graph, Graph::Vertex* v1, Graph::Vertex* v2)
{
    cout << "Select 2 vertices on the graph:" << endl;
    SelectVertex(graph, v1);
    SelectVertex(graph, v2);
}

static void PrintShortestPath(const Graph::Graph* graph, Graph::Vertex v1, Graph::Vertex v2)
{
    auto path = new DynamicArray<Graph::Vertex>();
    if (graph->ShortestPath(v1, v2, path))
    {
        cout << "\nShortest path between " << v1 << " and " << v2 << " is:" << endl << path->Get(START_INDEX);
        for (size_t i = SHORTEST_PATH_START_INDEX; i < path->Length(); i++)
            cout << " -> " << path->Get(i);
        cout << endl;
    }
    else
    {
        cout << "\nNo path found between " << v1 << " and " << v2 << endl;
    }
    delete path;
}

int main(int argc, char* argv[])
{
    auto graph = CreateGraph();
    if (graph == nullptr)
    {
        cout << "\nCouldn't create graph." << endl;
        return 1;
    }
    if (!LoadFromJson(JSON_PATH, graph))
    {
        cout << "\nCouldn't load JSON file \"" << JSON_PATH << "\"." << endl;
        return 1;
    }
    PrintGraph(graph);
    Graph::Vertex v1, v2;
    SelectPath(graph, &v1, &v2);
    PrintShortestPath(graph, v1, v2);
    delete graph;
    return 0;
}
