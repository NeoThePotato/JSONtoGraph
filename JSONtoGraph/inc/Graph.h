#include "DynamicArray.h"

#pragma once
namespace Graph
{
	using Vertex = int;

	struct Edge
	{
		Vertex v1;
		Vertex v2;
	};

	class Graph
	{
	public:
		// Vertices
		virtual Vertex VertexAt(size_t) const = 0;
		virtual void AddVertex(Vertex) = 0;
		virtual size_t VertexCount() const = 0;

		// Edges
		virtual Edge EdgeAt(size_t) const = 0;
		virtual void AddEdge(Edge) = 0;
		virtual size_t EdgeCount() const = 0;

		Collections::DynamicArray<Edge>* ShortestPath(Vertex v1, Vertex v2);
	};
}
