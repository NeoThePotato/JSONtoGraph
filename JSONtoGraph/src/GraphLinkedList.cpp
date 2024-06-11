#include "GraphLinkedList.h"
using namespace Graph;

GraphLinkedList::GraphLinkedList()
{
    _vertices = LinkedList<Vertex>();
    _edges = LinkedList<Edge>();
}

Vertex GraphLinkedList::VertexAt(size_t index) const
{
    return _vertices.Get(index);
}

void GraphLinkedList::AddVertex(Vertex vertex)
{
    return _vertices.Insert(vertex);
}

size_t GraphLinkedList::VertexCount() const
{
    return _vertices.Count();
}

Edge GraphLinkedList::EdgeAt(size_t index) const
{
    return _edges.Get(index);
}

void GraphLinkedList::AddEdge(Edge edge)
{
    return _edges.Insert(edge);
}

size_t GraphLinkedList::EdgeCount() const
{
    return _edges.Count();
}
