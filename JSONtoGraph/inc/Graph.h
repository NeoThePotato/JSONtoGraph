#include "DynamicArray.h"
using Collections::DynamicArray;

#pragma once
namespace Graph
{
	using Vertex = int;

	struct Edge
	{
		Vertex v1;
		Vertex v2;

		bool operator ==(Edge e) const
		{
			return v1 == e.v1 && v2 == e.v2;
		}
	};

	class Graph
	{
	public:
		// Vertices
		virtual Vertex VertexAt(size_t) const = 0;
		virtual void AddVertex(Vertex) = 0;
		virtual size_t VertexCount() const = 0;
		bool Exists(Vertex v) const;

		// Edges
		virtual Edge EdgeAt(size_t) const = 0;
		virtual void AddEdge(Edge) = 0;
		virtual size_t EdgeCount() const = 0;
		bool Exists(Edge e) const;

		bool ShortestPath(DynamicArray<Edge>* out, Vertex v1, Vertex v2) const;
	};
}
