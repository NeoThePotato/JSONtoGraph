#include <string>
#include <fstream>
#include "File.h"
#include "DynamicArray.h"
#include "Graph2DArray.h"
#include "GraphLinkedList.h"
using std::string;
using Collections::DynamicArray;

namespace IO
{
    constexpr size_t START_INDEX = 0;
    constexpr size_t INDEX_SHIFT = 1;
    constexpr int BASELINE_DEPTH = 0;

    static const char* ToString(const char* path)
    {
        std::ifstream f(path);
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

    static size_t FindClosingBracket(const char* source, size_t start)
    {
        int depth = BASELINE_DEPTH;
        size_t index;
        for (index = start; source[index] != '\0'; index++)
        {
            if (source[index] == '[')
                depth++;
            else if (source[index] == ']')
                depth--;
            if (depth <= BASELINE_DEPTH)
                break;
        }
        return index;
    }

    static bool GetArrayRangeIndicies(const char* source, const char* key, size_t& start, size_t& end)
    {
        size_t keyIndex = string(source).find(key);
        if (keyIndex == string::npos)
            return false;
        start = string(source + keyIndex).find('[') + keyIndex;
        end = FindClosingBracket(source, start);
        return true;
    }

    static DynamicArray<string>* GetStringArray(const char* source, const char* key)
    {
        size_t arrayStartIndex, arrayEndIndex;
        if (GetArrayRangeIndicies(source, key, arrayStartIndex, arrayEndIndex))
        {
            auto fullArrayString = string(source + arrayStartIndex, ++arrayEndIndex);
            fullArrayString.erase(remove_if(fullArrayString.begin(), fullArrayString.end(), isspace), fullArrayString.end()); // Strip spaces
            fullArrayString = fullArrayString.substr(fullArrayString.find('[') + INDEX_SHIFT, fullArrayString.rfind(']') - INDEX_SHIFT); // Strip brackets

            auto arr = new DynamicArray<string>();
            size_t strStart = START_INDEX, strEnd;
            do
            {
                strEnd = fullArrayString.find(',', strStart) + INDEX_SHIFT;
                string subString = fullArrayString.substr(strStart, strEnd - strStart - INDEX_SHIFT);
                arr->Append(subString);
                strStart = strEnd;
            } while (strEnd != START_INDEX);
            return arr;
        }
        return nullptr;
    }

    template <class T>
    static DynamicArray<T>* GetTArray(const char* source, const char* key, T (*conversionFunc)(const string&))
    {
        auto strArr = GetStringArray(source, key);
        if (strArr == nullptr)
            return nullptr;
        DynamicArray<T>* tArr = new DynamicArray<T>(strArr->Length());
        for (size_t i = START_INDEX; i < strArr->Length(); i++)
            tArr->Append(conversionFunc(strArr->Get(i)));
        delete strArr;
        return tArr;
    }

    static int StrToInt(const string& source)
    {
        return std::stoi(source);
    }

    static DynamicArray<int>* GetIntArray(const char* source, const char* key)
    {
        return GetTArray<int>(source, key, StrToInt);
    }

    static DynamicArray<int[2]>* GetInt2DArray(const char* source, const char* key)
    {
        size_t arrayStartIndex, arrayEndIndex;
        if (GetArrayRangeIndicies(source, key, arrayStartIndex, arrayEndIndex))
        {
            auto arrayString = string(source + arrayStartIndex, ++arrayEndIndex);
            arrayString.erase(remove_if(arrayString.begin(), arrayString.end(), isspace), arrayString.end()); // Strip spaces
            arrayString = arrayString.substr(arrayString.find('[') + INDEX_SHIFT, arrayString.find(']') - INDEX_SHIFT); // Strip brackets

            auto arr = new DynamicArray<int[2]>();
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

    bool File::LoadFromJson(const char* path, Graph::Graph* graph)
    {
        auto str = ToString(path);
        if (str == nullptr)
        {
            delete[] str;
            return false;
        }

        // Vertices
        auto arr = GetIntArray(str, VERTICIES_KEY);
        if (arr == nullptr)
            return false;
        for (size_t i = 0; i < arr->Length(); i++)
            graph->AddVertex(arr->Get(i));
        delete arr;

        // Edges
        auto arr2D = GetInt2DArray(str, EDGES_KEY);
        delete[] str;
        if (arr == nullptr)
            return false;
        for (size_t i = 0; i < arr2D->Length(); i++)
        {
            Graph::Edge edge{arr2D->Get(i)[0], arr2D->Get(i)[1]};
            graph->AddEdge(Graph::Edge {arr2D->Get(i)[0], arr2D->Get(i)[1]});
        }
        delete arr;
        return true;
    }
}
