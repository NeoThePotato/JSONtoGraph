#include "DynamicArray.h"
using Collections::DynamicArray;

#pragma once
namespace Graph
{
	using Vertex = int;

	constexpr Vertex INVALID_VERTEX = -1;

	struct Edge
	{
		Vertex v1;
		Vertex v2;

		bool operator ==(Edge e) const
		{
			return v1 == e.v1 && v2 == e.v2;
		}

		bool Contains(Vertex v) const
		{
			return v1 == v || v2 == v;
		}

		Vertex GetOther(Vertex v) const
		{
			if (Contains(v))
				return v == v1 ? v2 : v1;
			return INVALID_VERTEX;
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
		void GetNeighbors(Vertex v, DynamicArray<Vertex>* out) const;

		// Edges
		virtual Edge EdgeAt(size_t) const = 0;
		virtual void AddEdge(Edge) = 0;
		virtual size_t EdgeCount() const = 0;
		bool Exists(Edge e) const;

		bool ShortestPath(Vertex v1, Vertex v2, DynamicArray<Vertex>* out) const;

	private:
		void BreadthFirstSearch(Vertex, DynamicArray<Vertex>*) const;
		bool ReconstructPath(Vertex, Vertex, DynamicArray<Vertex>*) const;
	};
}
