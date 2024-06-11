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

    static DynamicArray<string>* GetStringArray(const char* source, const size_t bracketStartIndex, DynamicArray<string>* arr)
    {
        size_t bracketEndIndex = FindClosingBracket(source, bracketStartIndex);
        auto fullArrayString = string(source).substr(bracketStartIndex, bracketEndIndex - bracketStartIndex + INDEX_SHIFT);
        fullArrayString.erase(remove_if(fullArrayString.begin(), fullArrayString.end(), isspace), fullArrayString.end()); // Strip spaces
        fullArrayString = fullArrayString.substr(fullArrayString.find('[') + INDEX_SHIFT, fullArrayString.rfind(']') - INDEX_SHIFT); // Strip brackets

        arr->Clear();
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

    static bool GetStringArray(const char* source, const char* key, DynamicArray<string>* arr)
    {
        size_t arrayStartIndex;
        if (GetArrayStartIndex(source, key, arrayStartIndex))
        {
            GetStringArray(source, arrayStartIndex, arr);
            return true;
        }
        return false;
    }

    template <class T>
    static bool GetTArray(const char* source, const char* key, T (*conversionFunc)(const string&), DynamicArray<T>* out)
    {
        auto strArr = new DynamicArray<string>();
        if (!GetStringArray(source, key, strArr))
        {
            delete strArr;
            return false;
        }
        out->Clear();
        for (size_t i = START_INDEX; i < strArr->Length(); i++)
            out->Append(conversionFunc(strArr->Get(i)));
        delete strArr;
        return true;
    }

    static int StrToInt(const string& source)
    {
        return std::stoi(source);
    }

    static Graph::Edge StrToEdge(const string& source)
    {
        auto strArr = new DynamicArray<string>();
        GetStringArray(source.c_str(), START_INDEX, strArr);
        Graph::Edge edge{ StrToInt(strArr->Get(0)), StrToInt(strArr->Get(1)) };
        delete strArr;
        return edge;
    }

    static bool GetIntArray(const char* source, const char* key, DynamicArray<int>* out)
    {
        return GetTArray<int>(source, key, StrToInt, out);
    }

    static bool GetEdgeArray(const char* source, const char* key, DynamicArray<Graph::Edge>* out)
    {
        return GetTArray<Graph::Edge>(source, key, StrToEdge, out);
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
        auto vertices = DynamicArray<Graph::Vertex>();
        if (!GetIntArray(str, VERTICIES_KEY, &vertices))
            return false;
        for (size_t i = START_INDEX; i < vertices.Length(); i++)
            graph->AddVertex(vertices.Get(i));

        // Edges
        auto edges = DynamicArray<Graph::Edge>();
        if (!GetEdgeArray(str, EDGES_KEY, &edges))
        {
            delete[] str;
            return false;
        }
        delete[] str;
        for (size_t i = START_INDEX; i < edges.Length(); i++)
            graph->AddEdge(edges.Get(i));
        return true;
    }
}
