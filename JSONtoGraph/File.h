#include <fstream>
#include "Graph2DArray.h"
#include "GraphLinkedList.h"

#pragma once
namespace IO
{
	static class File
	{
	public:
		static int LoadFromList(const char* path, Graph2DArray& graph);

	private:
		static const char* ToString(const char* path);
	};
}
