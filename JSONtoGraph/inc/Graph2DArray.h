#pragma once
#include "Graph.h"
#include "DynamicArray.h"
using Collections::DynamicArray;

namespace Graph
{
	class Graph2DArray : public Graph
	{
	private:
		DynamicArray<Vertex> _vertices;
		DynamicArray<Edge> _edges;

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
