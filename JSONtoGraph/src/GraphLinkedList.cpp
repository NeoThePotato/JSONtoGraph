#include "GraphLinkedList.h"
using namespace Graph;

Vertex GraphLinkedList::VertexAt(size_t index)
{
    _vertices.Get(index);
}

bool GraphLinkedList::AddVertex(Vertex vertex)
{
    _vertices.Insert(vertex);
}

size_t GraphLinkedList::GraphLinkedList::VertexCount()
{
    return _vertices.Count();
}

Edge GraphLinkedList::EdgeAt(size_t index)
{
    _edges.Get(index);
}

bool GraphLinkedList::AddEdge(Edge edge)
{
    _edges.Insert(edge);
}

size_t GraphLinkedList::GraphLinkedList::EdgeCount()
{
    return _edges.Count();
}
