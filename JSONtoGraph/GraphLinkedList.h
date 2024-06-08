#pragma once
#include "Graph.h"
#include "LinkedList.h"
using Collections::LinkedList;

namespace Graph
{
	class GraphLinkedList : public Graph
	{
	private:
		LinkedList<Vertex> _vertices;
		LinkedList<Edge> _edges;

	public:
		// Inherited via Graph
		Vertex VertexAt(size_t index) override;
		bool AddVertex(Vertex vertex) override;
		Edge EdgeAt(size_t index) override;
		bool AddEdge(Edge edge) override;
	};
}
