#include "GraphLinkedList.h"
using namespace Graph;

Vertex GraphLinkedList::VertexAt(size_t index)
{
    return _vertices.Get(index);
}

void GraphLinkedList::AddVertex(Vertex vertex)
{
    return _vertices.Insert(vertex);
}

size_t GraphLinkedList::GraphLinkedList::VertexCount()
{
    return _vertices.Count();
}

Edge GraphLinkedList::EdgeAt(size_t index)
{
    return _edges.Get(index);
}

void GraphLinkedList::AddEdge(Edge edge)
{
    return _edges.Insert(edge);
}

size_t GraphLinkedList::GraphLinkedList::EdgeCount()
{
    return _edges.Count();
}
