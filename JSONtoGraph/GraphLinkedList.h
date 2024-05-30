#pragma once
#include "Graph.h"
#include "LinkedList.h"

namespace Graph
{
	class GraphLinkedList
	{
	private:
		LinkedList<Vertex> _vertices;
		LinkedList<Edge> _edges;
	};
}
