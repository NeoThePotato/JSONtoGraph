#include <fstream>
#include "Graph2DArray.h"
#include "GraphLinkedList.h"

#pragma once
namespace IO
{
	constexpr auto VERTICIES_KEY = "\"vertices\"";
	constexpr auto EDGES_KEY = "\"edges\"";

	static class File
	{
	public:
		static bool LoadFromJson(const char* path, Graph::Graph2DArray& graph);

		static bool LoadFromJson(const char* path, Graph::GraphLinkedList& graph);
	};
}
