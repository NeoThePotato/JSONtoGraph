#include <string>
#include <iostream>
#include <fstream>
#include "File.h"
using namespace std;

namespace IO
{
    int File::LoadFromList(const char* path, Graph2DArray& graph)
    {
        const char* json_str = ToString(path);
        return 0;
    }

    const char* File::ToString(const char* path)
    {
        ifstream f(path);
        if (!f.is_open())
        {
            return nullptr;
        }
        string text;
        while (getline(f, text))
        {
            cout << text;
        }
        f.close();
        return 0;
    }
}
