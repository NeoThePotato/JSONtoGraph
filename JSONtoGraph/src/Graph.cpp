#include "Graph.h"
#include "Queue.h"
#include "Set.h"
using Collections::DynamicArray, Collections::Queue, Collections::Set;

namespace Graph
{
	constexpr size_t START_INDEX = 0;

	bool Edge::operator==(Edge e) const
	{
		return v1 == e.v1 && v2 == e.v2;
	}

	bool Edge::Contains(Vertex v) const
	{
		return v1 == v || v2 == v;
	}

	Vertex Edge::GetOther(Vertex v) const
	{
		if (Contains(v))
			return v == v1 ? v2 : v1;
		return INVALID_VERTEX;
	}

	bool Graph::Exists(Vertex v) const
	{
		for (size_t i = START_INDEX; i < VertexCount(); i++)
		{
			if (v == VertexAt(i))
				return true;
		}
		return false;
	}

	void Graph::GetNeighbors(Vertex v, DynamicArray<Vertex>* neighbors) const
	{
		if (!Exists(v))
			return;
		neighbors->Clear();
		for (size_t i = START_INDEX; i < EdgeCount(); i++)
		{
			Vertex neighbor = EdgeAt(i).GetOther(v);
			if (neighbor != INVALID_VERTEX)
				neighbors->Append(neighbor);
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

	void Graph::BreadthFirstSearch(Vertex start, DynamicArray<Vertex>* parents) const
	{
		parents->SetAll(INVALID_VERTEX, VertexCount());
		// TODO Consider stack-allocating these
		auto visitQueue = new Queue<Vertex>(VertexCount());
		auto visited = new Set<Vertex>(VertexCount());
		auto neighbors = new DynamicArray<Vertex>();
		visitQueue->Enqueue(start);
		visited->TryAdd(start);

		while (!visitQueue->Empty())
		{
			auto current = visitQueue->Dequeue();
			GetNeighbors(current, neighbors);

			for (size_t n = START_INDEX; n < neighbors->Length(); n++)
			{
				Vertex next = neighbors->Get(n);
				if (visited->TryAdd(next)) // If not visited yet
				{
					visitQueue->Enqueue(next);
					parents->Insert(next, current);
				}
			}
		}
		delete visitQueue;
		delete visited;
		delete neighbors;
	}

	bool Graph::ReconstructPath(Vertex start, Vertex end, DynamicArray<Vertex>* path) const
	{
		auto oldPath = new DynamicArray<Vertex>(path);
		path->Clear();
		for (Vertex current = end; current != INVALID_VERTEX; current = oldPath->Get(current))
			path->Insert(current, 0);
		delete oldPath;
		return path->Get(0) == start;
	}

	bool Graph::ShortestPath(Vertex start, Vertex end, DynamicArray<Vertex>* shortestPath) const
	{
		if (Exists(start) && Exists(end))
		{
			BreadthFirstSearch(start, shortestPath);
			return ReconstructPath(start, end, shortestPath);
		}
		return false;
	}
}
