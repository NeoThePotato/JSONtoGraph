#include "File.h"
#include "Graph2DArray.h"

int main(int argc, char* argv[])
{
    Graph::Graph2DArray g;
    IO::File::LoadFromList("source.json", g);
}
