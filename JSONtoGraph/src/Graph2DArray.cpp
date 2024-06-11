#include "Graph2DArray.h"
using namespace Graph;

Graph2DArray::Graph2DArray(size_t vertexCapacity, size_t edgeCapacity)
{
    _vertices = new DynamicArray<Vertex>(vertexCapacity);
    _edges = new DynamicArray<Edge>(edgeCapacity);
}

Graph2DArray::~Graph2DArray()
{
    delete _vertices;
    delete _edges;
}

Vertex Graph2DArray::VertexAt(size_t index) const
{
    return _vertices->Get(index);
}

void Graph2DArray::AddVertex(Vertex vertex)
{
    _vertices->Append(vertex);
}

size_t Graph2DArray::VertexCount() const
{
    return _vertices->Length();
}

Edge Graph2DArray::EdgeAt(size_t index) const
{
    return _edges->Get(index);
}

void Graph2DArray::AddEdge(Edge edge)
{
    _edges->Append(edge);
}

size_t Graph2DArray::EdgeCount() const
{
    return _edges->Length();
}
