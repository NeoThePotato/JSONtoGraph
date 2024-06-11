#pragma once
#include "Graph.h"

namespace IO
{
	constexpr auto VERTICIES_KEY = "\"vertices\"";
	constexpr auto EDGES_KEY = "\"edges\"";

	class File
	{
	public:
		static bool LoadFromJson(const char* path, Graph::Graph* graph);
	};
}
