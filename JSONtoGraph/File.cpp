#include <stdio.h>;
#include "File.h"

namespace IO
{
    int File::LoadFromList(const char* path, Graph2DArray& graph)
    {
        FILE* json_file;
        fopen_s(&json_file, path, "r");
        if (!json_file)
        {
            return 1;
        }
        int c;
        while ((c = std::fgetc(json_file)) != EOF)
        {
            printf("%c", c);
        }
        fclose(json_file);
        return 0;
    }
}
