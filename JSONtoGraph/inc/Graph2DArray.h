#pragma once
#include "Graph.h"

namespace Graph
{
	class Graph2DArray : public Graph
	{
	private:
		Vertex* vertices;
		Edge* edges;

	public:
		// Inherited via Graph
		Vertex VertexAt(size_t index) override;
		bool AddVertex(Vertex vertex) override;
		size_t VertexCount() override;
		Edge EdgeAt(size_t index) override;
		bool AddEdge(Edge edge) override;
		size_t EdgeCount() override;
	};
}
