#include <string>
#include <fstream>
#include "Graph2DArray.h"
#include "GraphLinkedList.h"

#pragma once
namespace IO
{
	static class File
	{
	public:
		const char* VERTICIES_KEY = "vertices";
		const char* EDGES_KEY = "edges";

		static bool LoadFromList(const char* path, Graph::Graph2DArray& graph);

	private:
		static const char* ToString(const char* path);
	};
}
