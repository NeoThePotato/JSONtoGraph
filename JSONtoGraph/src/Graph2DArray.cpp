#include "Graph2DArray.h"
using namespace Graph;

constexpr size_t DEFAULT_CAPACITY = 5;

Graph2DArray::Graph2DArray(size_t vertexCapacity = DEFAULT_CAPACITY, size_t edgeCapacity = DEFAULT_CAPACITY)
{
    _vertices = DynamicArray<Vertex>(vertexCapacity);
    _edges = DynamicArray<Edge>(edgeCapacity);
}

Vertex Graph2DArray::VertexAt(size_t index) const
{
    return _vertices.Get(index);
}

void Graph2DArray::AddVertex(Vertex vertex)
{
    _vertices.Append(vertex);
}

size_t Graph2DArray::Graph2DArray::VertexCount() const
{
    return _vertices.Length();
}

Edge Graph2DArray::EdgeAt(size_t index) const
{
    return _edges.Get(index);
}

void Graph2DArray::AddEdge(Edge edge)
{
    _edges.Append(edge);
}

size_t Graph2DArray::Graph2DArray::EdgeCount() const
{
    return _edges.Length();
}
