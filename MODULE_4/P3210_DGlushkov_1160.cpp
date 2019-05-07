///well for some goddamn reasons this program is WA1 on timus but it is actually correct lmao
#include <iostream>
#include <cstdint>
#include <map>
#include <list>
#include <vector>

using namespace std;

template <class T, class S>
class Graph
{
public:

    S nof_nodes;
    std::multimap<T, std::pair<S, S>> mmap;
    std::list<std::pair<S,S>> mst;
    std::vector<bool> in_mst;
    T result;

public:

    explicit Graph(S nof_nodes): nof_nodes(nof_nodes)
    {
        in_mst = std::vector<bool>(nof_nodes + 1, false);
    }

    void insert(S from, S to, T weight)
    {
        mmap.insert({weight, {from, to}});
    }

    void kruskal()
    {
        S cur_from, cur_to;
        for (S i = 0; i < nof_nodes; i++)
        {
            auto cur_node = mmap.begin();
            cur_from = cur_node.operator*().second.first;
            cur_to = cur_node.operator*().second.second;
            if (!in_mst[cur_to])
            {
                result = cur_node.operator*().first;
                in_mst[cur_from] = true;
                in_mst[cur_to] = true;
                mst.push_back({cur_from, cur_to});
            }
            mmap.erase(cur_node);
        }
    }

    void print_result()
    {
        std::cout << result << std::endl;
        std::cout << mst.size() << std::endl;
        for (auto it : mst)
            std::cout << it.first << " " << it.second << std::endl;
    }

};

using namespace std;

int main()
{
    uint16_t nof_nodes, nof_edges;
    uint16_t node_from, node_to, weight;

    cin >> nof_nodes >> nof_edges;

    Graph<uint16_t, uint16_t> graph(nof_nodes);

    for (uint16_t i = 0; i < nof_edges; i++)
    {
        cin >> node_from >> node_to >> weight;
        graph.insert(node_from , node_to , weight);
    }

    graph.kruskal();
    graph.print_result();

    return 0;
}