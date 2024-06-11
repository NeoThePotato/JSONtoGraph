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
        str[f.gcount()] = '\0';
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

    static size_t FindNextComma(const char* source, size_t start)
    {
        int depth = BASELINE_DEPTH;
        size_t index;
        for (index = start; source[index] != '\0'; index++)
        {
            if (source[index] == '[')
                depth++;
            else if (source[index] == ']')
                depth--;
            if (source[index] == ',' && depth <= BASELINE_DEPTH)
                break;
        }
        return index;
    }

    static bool GetArrayStartIndex(const char* source, const char* key, size_t& start)
    {
        size_t keyIndex = string(source).find(key);
        if (keyIndex == string::npos)
            return false;
        start = string(source + keyIndex).find('[') + keyIndex;
        return true;
    }

    static bool GetArrayRangeIndicies(const char* source, const char* key, size_t& start, size_t& end)
    {
        if (GetArrayStartIndex(source, key, start))
        {
            end = FindClosingBracket(source, start);
            return true;
        }
        return false;
    }

    static DynamicArray<string>* GetStringArray(const char* source, const size_t bracketStartIndex)
    {
        size_t bracketEndIndex = FindClosingBracket(source, bracketStartIndex);
        auto fullArrayString = string(source).substr(bracketStartIndex, bracketEndIndex - bracketStartIndex + INDEX_SHIFT);
        fullArrayString.erase(remove_if(fullArrayString.begin(), fullArrayString.end(), isspace), fullArrayString.end()); // Strip spaces
        fullArrayString = fullArrayString.substr(fullArrayString.find('[') + INDEX_SHIFT, fullArrayString.rfind(']') - INDEX_SHIFT); // Strip brackets

        auto arr = new DynamicArray<string>();
        size_t strStart = START_INDEX, strEnd;
        do
        {
            strEnd = FindNextComma(fullArrayString.c_str(), strStart) + INDEX_SHIFT;
            string subString = fullArrayString.substr(strStart, strEnd - strStart - INDEX_SHIFT);
            arr->Append(subString);
            strStart = strEnd;
        } while (strEnd < fullArrayString.size());
        return arr;
    }

    static DynamicArray<string>* GetStringArray(const char* source, const char* key)
    {
        size_t arrayStartIndex;
        if (GetArrayStartIndex(source, key, arrayStartIndex))
        {
            return GetStringArray(source, arrayStartIndex);
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
        return tArr;
    }

    static int StrToInt(const string& source)
    {
        return std::stoi(source);
    }

    static Graph::Edge StrToEdge(const string& source)
    {
        auto arr = GetStringArray(source.c_str(), START_INDEX);
        Graph::Edge edge{ StrToInt(arr->Get(0)), StrToInt(arr->Get(1)) };
        delete arr;
        return edge;
    }

    static DynamicArray<int>* GetIntArray(const char* source, const char* key)
    {
        return GetTArray<int>(source, key, StrToInt);
    }

    static DynamicArray<Graph::Edge>* GetEdgeArray(const char* source, const char* key)
    {
        return GetTArray<Graph::Edge>(source, key, StrToEdge);
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
        for (size_t i = START_INDEX; i < arr->Length(); i++)
            graph->AddVertex(arr->Get(i));
        delete arr;

        // Edges
        auto arrEdge = GetEdgeArray(str, EDGES_KEY);
        delete[] str;
        if (arrEdge == nullptr)
            return false;
        for (size_t i = START_INDEX; i < arrEdge->Length(); i++)
            graph->AddEdge(arrEdge->Get(i));
        delete arrEdge;
        return true;
    }
}
