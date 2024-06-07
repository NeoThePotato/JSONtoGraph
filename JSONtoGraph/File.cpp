#include <string>
#include <iostream>
#include <fstream>
#include "File.h"
#include "Graph2DArray.h"
#include "GraphLinkedList.h"
using namespace std;

namespace IO
{
    bool File::LoadFromList(const char* path, Graph::Graph2DArray& graph)
    {
        auto str = ToString(path);
        if (str != nullptr)
        {
            // TODO To graph
        delete[] str;
            return true;
        }
        return false;
    }

    const char* File::ToString(const char* path)
    {
        ifstream f(path);
        if (!f.is_open())
        {
            return nullptr;
        }
        f.seekg(0, std::ios::end);
        size_t str_size = f.tellg();
        auto str = new char[str_size];
        f.seekg(0);
        f.read(str, str_size);
        f.close();
        return str;
    }
}
