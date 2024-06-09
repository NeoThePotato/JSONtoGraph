#include "Graph.h"
#include "Queue.h"
using Collections::DynamicArray, Collections::Queue;

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

	void Graph::GetNeighbors(Vertex v, DynamicArray<Edge>* out) const
	{
		if (!Exists(v))
			return;
		for (size_t i = START_INDEX; i < EdgeCount(); i++)
		{
			Edge edge = EdgeAt(i);
			if (edge.Contains(v))
				out->Append(edge);
		}
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

	void Graph::BreadthFirstSearch(Vertex start, Vertex end, DynamicArray<Edge>* out) const
	{
		auto q = new Queue<Vertex>(VertexCount());
		q->Enqueue(start);

		delete q;
	}

	bool Graph::ShortestPath(Vertex start, Vertex end, DynamicArray<Vertex>* out) const
	{
		if (Exists(start) && Exists(end))
		{
			// TODO Implement
		}
		return false;
	}
}
