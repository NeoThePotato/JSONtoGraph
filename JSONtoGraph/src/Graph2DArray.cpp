#include "Graph2DArray.h"
using namespace Graph;

constexpr size_t DEFAULT_CAPACITY = 5;

Graph2DArray::Graph2DArray(size_t vertexCapacity = DEFAULT_CAPACITY, size_t edgeCapacity = DEFAULT_CAPACITY)
{
    _vertices = DynamicArray<Vertex>(vertexCapacity);
    _edges = DynamicArray<Edge>(edgeCapacity);
}

Vertex Graph2DArray::VertexAt(size_t index)
{
    return _vertices.Get(index);
}

bool Graph2DArray::AddVertex(Vertex vertex)
{
    if (_vertices.Exists(vertex))
        return false;
    _vertices.Append(vertex);
    return true;
}

size_t Graph2DArray::Graph2DArray::VertexCount()
{
    return _vertices.Length();
}

Edge Graph2DArray::EdgeAt(size_t index)
{
    return _edges.Get(index);
}

bool Graph2DArray::AddEdge(Edge edge)
{
    if (_edges.Exists(edge))
        return false;
    _edges.Append(edge);
    return true;
}

size_t Graph2DArray::Graph2DArray::EdgeCount()
{
    return _edges.Length();
}
