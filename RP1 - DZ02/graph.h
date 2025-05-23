#include <map>
#include <set>
#include <tuple>
#include <vector>

struct graph
{
    std::set<char> vertices;
    std::map<std::set<char>, int> weights;

    graph();
    graph(std::set<std::tuple<char, char, int>>);

    bool insertVertex(char);
    bool insertEdge(char, char, int);
    bool eraseVertex(char);
    bool eraseEdge(char, char);
    std::vector<std::vector<int>> laplacianMatrix();
    std::set<std::set<char>> distancePartition(char);
};
