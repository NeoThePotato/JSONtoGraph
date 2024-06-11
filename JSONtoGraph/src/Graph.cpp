#include "Graph.h"
#include "Queue.h"
#include "Set.h"
using Collections::DynamicArray, Collections::Queue, Collections::Set;

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

	void Graph::GetNeighbors(Vertex v, DynamicArray<Vertex>* out) const
	{
		if (!Exists(v))
			return;
		out->Clear();
		for (size_t i = START_INDEX; i < EdgeCount(); i++)
		{
			Vertex neighbor = EdgeAt(i).GetOther(v);
			if (neighbor != INVALID_VERTEX)
				out->Append(neighbor);
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

	void Graph::BreadthFirstSearch(Vertex start, DynamicArray<Vertex>* out) const
	{
		auto visitQueue = new Queue<Vertex>(VertexCount());
		auto visited = new Set<Vertex>(VertexCount());
		auto neighbors = new DynamicArray<Vertex>();
		visitQueue->Enqueue(start);
		visited->TryAdd(start);

		while (visitQueue->Length() > 0)
		{
			auto node = visitQueue->Dequeue();
			GetNeighbors(node, neighbors);

			for (size_t n = START_INDEX; n < neighbors->Length(); n++)
			{
				Vertex next = neighbors->Get(n);
				if (visited->TryAdd(next)) // If not visited yet
				{
					visitQueue->Enqueue(next);
					out->Insert(next, node);
				}
			}
		}
		delete visitQueue;
		delete visited;
		delete neighbors;
	}

	void Graph::ReconstructPath(Vertex start, Vertex end, DynamicArray<Vertex>* path) const
	{

	}

	bool Graph::ShortestPath(Vertex start, Vertex end, DynamicArray<Vertex>* out) const
	{
		if (Exists(start) && Exists(end))
		{
			auto path = new DynamicArray<Vertex>(VertexCount());
			BreadthFirstSearch(start, out);

			delete path;
		}
		return false;
	}
}
