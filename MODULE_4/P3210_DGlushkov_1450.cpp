#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <class T, class S>
class Graph
{
    map<S, map<S, T>> edges;
    S nof_nodes;
    vector<T> max_path;

public:
    explicit Graph(S nof_nodes): nof_nodes(nof_nodes)
    {
        max_path = vector<T>(nof_nodes, 0);
        for (S i = 0; i < nof_nodes; i++)
            edges[i] = map<S, T>();
    }

    void insert_edge(S from, S to, T weight)
    {
        edges[from].insert({to, weight});
    }

    void solve(S cur_node)
    {
        for (auto it : edges[cur_node])
        {
            S temp = max_path[cur_node] + it.second;
            if (temp > max_path[it.first])
            {
                max_path[it.first] = temp;
                solve(it.first);
            }
        }
    }

    void print_result(S destination)
    {
        if (max_path[destination])
            cout << max_path[destination];
        else
            cout << "No solution";
    }


};


int main()
{
    uint32_t nof_nodes, nof_edges, node_from, node_to, node_weight;
    cin >> nof_nodes >> nof_edges;
    Graph<uint32_t , uint32_t > graph(nof_nodes);

    for (uint32_t i = 0; i < nof_edges; i++)
    {
        cin >> node_from >> node_to >> node_weight;
        graph.insert_edge(node_from - 1, node_to - 1, node_weight);
    }

    cin >> node_from >> node_to;

    graph.solve(node_from - 1);
    graph.print_result(node_to - 1);
    return 0;
}