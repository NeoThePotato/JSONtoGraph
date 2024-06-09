#include <iostream>
#include "File.h"
#include "GraphLinkedList.h"
#include "Graph2DArray.h"
using std::cout, std::endl, std::cin;

constexpr size_t START_INDEX = 0;

static Graph::Graph* CreateGraph()
{
    cout << "Select graph implementation\n1: Linked List\n2: 2D Array" << endl;
    unsigned int selection;
    while (true)
    {
        cin >> selection;
        if (selection <= 2)
            break;
        else
            cout << "Invalid Input." << endl;
    }
    switch (selection)
    {
    case 1:
        return new Graph::GraphLinkedList();
    case 2:
        return new Graph::Graph2DArray();
    default:
        return nullptr;
    }
}

static void LoadFromJson(Graph::Graph* graph)
{
    IO::File::LoadFromJson("source.json", graph);
    cout << "Loaded Graph:" << endl;
}

static void PrintGraph(Graph::Graph* graph)
{
    cout << "Vertices:\n";
    for (size_t i = START_INDEX; i < graph->VertexCount(); i++)
        cout << '\t' << graph->VertexAt(i) << '\n';
    cout << "Edges:\n";
    for (size_t i = START_INDEX; i < graph->EdgeCount(); i++)
        cout << "\t(" << graph->EdgeAt(i).v1 << ", " << graph->EdgeAt(i).v2 << ")\n";
    cout << endl;
}

static void SelectVertex(Graph::Graph* graph, Graph::Vertex* vertex)
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

static void SelectPath(Graph::Graph* graph, Graph::Vertex* v1, Graph::Vertex* v2)
{
    cout << "Select 2 vertices on the graph:" << endl;
    SelectVertex(graph, v1);
    SelectVertex(graph, v2);
}

static void PrintShortestPath(Graph::Graph* graph, Graph::Vertex v1, Graph::Vertex v2)
{
    auto path = new DynamicArray<Graph::Vertex>();
    if (graph->ShortestPath(v1, v2, path))
    {
        cout << "Shortest path between " << v1 << " and " << v2 << " is:" << '\n';
        for (size_t i = START_INDEX; i < path->Length(); i++)
            cout << path->Get(i) << '\n';
        cout << endl;
    }
    else
    {
        cout << "No path found between " << v1 << " and " << v2 << endl;
    }
    delete path;
}

int main(int argc, char* argv[])
{
    auto graph = CreateGraph();
    LoadFromJson(graph);
    PrintGraph(graph);
    Graph::Vertex v1, v2;
    SelectPath(graph, &v1, &v2);
    PrintShortestPath(graph, v1, v2);
    delete graph;
}
