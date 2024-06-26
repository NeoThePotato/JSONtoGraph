#pragma once
#include "Graph.h"
#include "DynamicArray.h"
using Collections::DynamicArray;

namespace Graph
{
	constexpr size_t DEFAULT_CAPACITY = 5;

	class Graph2DArray : public Graph
	{
	private:
		DynamicArray<Vertex>* _vertices;
		DynamicArray<Edge>* _edges;

	public:
		Graph2DArray(size_t vertexCapacity = DEFAULT_CAPACITY, size_t edgeCapacity = DEFAULT_CAPACITY);
		~Graph2DArray();
		// Inherited via Graph
		Vertex VertexAt(size_t index) const override;
		void AddVertex(Vertex vertex) override;
		size_t VertexCount() const override;
		Edge EdgeAt(size_t index) const override;
		void AddEdge(Edge edge) override;
		size_t EdgeCount() const override;
	};
}
