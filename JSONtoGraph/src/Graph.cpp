#include "Graph.h"
using Collections::DynamicArray;

namespace Graph
{
	constexpr size_t START_INDEX = 0;

	bool Graph::Exists(Vertex v) const
	{
		for (size_t i = START_INDEX; i < VertexCount(); i++)
		{
			if (v == VertexAt(i))
				return true;
		}
		return false;
	}

	bool Graph::Exists(Edge e) const
	{
		for (size_t i = START_INDEX; i < EdgeCount(); i++)
		{
			if (e == EdgeAt(i))
				return true;
		}
		return false;
	}

	bool Graph::ShortestPath(DynamicArray<Edge>* out, Vertex v1, Vertex v2) const {
		// TODO Implement
		return false;
	}
}
