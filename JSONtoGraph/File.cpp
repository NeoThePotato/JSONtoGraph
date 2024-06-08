#include <string>
#include <iostream> // TODO Debug
#include <vector> // TODO Debug
#include <fstream>
#include "File.h"
#include "DynamicArray.h"
#include "Graph2DArray.h"
#include "GraphLinkedList.h"
using namespace std;

namespace IO
{
    constexpr int START_INDEX = 0;
    constexpr size_t INDEX_SHIFT = 1;

    static const char* ToString(const char* path)
    {
        ifstream f(path);
        if (!f.is_open())
        {
            return nullptr;
        }
        f.seekg(START_INDEX, std::ios::end);
        size_t str_size = f.tellg();
        auto str = new char[str_size];
        f.seekg(START_INDEX);
        f.read(str, str_size);
        f.close();
        return str;
    }

    static bool GetArrayRangeIndicies(const char* source, const char* key, size_t& start, size_t& end)
    {
        size_t keyIndex = string(source).find(key);
        if (keyIndex == string::npos)
            return false;
        start = string(source + keyIndex).find('[') + keyIndex;
        end = string(source + start).find(']');
        return true;
    }

    static DynamicArray<int>* GetIntArray(const char* source, const char* key)
    {
        size_t arrayStartIndex, arrayEndIndex;
        if (GetArrayRangeIndicies(source, key, arrayStartIndex, arrayEndIndex))
        {
            auto arrayString = string(source + arrayStartIndex, ++arrayEndIndex);
            arrayString.erase(remove_if(arrayString.begin(), arrayString.end(), isspace), arrayString.end()); // Strip spaces
            arrayString = arrayString.substr(arrayString.find('[') + INDEX_SHIFT, arrayString.find(']') - INDEX_SHIFT); // Strip brackets

            auto arr = new DynamicArray<int>();
            size_t intStart = START_INDEX, intEnd;
            do
            {
                intEnd = arrayString.find(',', intStart) + INDEX_SHIFT;
                string numberStr = arrayString.substr(intStart, intEnd - intStart - INDEX_SHIFT);
                arr->Append(stoi(numberStr));
                intStart = intEnd;
            } while (intEnd != START_INDEX);
            return arr;
        }
        return nullptr;
    }

    bool File::LoadFromJson(const char* path, Graph::Graph2DArray& graph)
    {
        auto str = ToString(path);
        if (str == nullptr)
        {
            delete[] str;
            return false;
        }
        auto arr = GetIntArray(str, VERTICIES_KEY);
        delete[] str;
        if (arr == nullptr)
            return false;
        // TODO To graph
        delete arr;
        return true;
    }

    bool File::LoadFromJson(const char* path, Graph::GraphLinkedList& graph)
    {
        auto str = ToString(path);
        if (str != nullptr)
        {
            auto arr = GetIntArray(str, VERTICIES_KEY);
            delete[] str;
            // TODO To graph
            delete arr;
            return true;
        }
        return false;
    }
}
