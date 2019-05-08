#include <iostream>
#include <vector>

using namespace std;

template<class T, class S>
class Graph
{
    struct edge{
        S from, to;
        T weight;
    };
    vector<edge> edges;
    vector<T> max_path;
    S nof_nodes, nof_edges, nof_checked;

public:

    explicit Graph(S nof_nodes, S nof_edges): nof_nodes(nof_nodes), nof_edges(nof_edges)
    {
        nof_checked = 0;
//        edges = vector<edge>(nof_edges);
        max_path = vector<T>(nof_nodes, -1);
    }

    void insert(S from, S to, T weight)
    {
        edges.push_back({from, to, weight});
    }

    T solve(S start_node, S end_node)
    {
        max_path[start_node] = 0;

        for (S i = 0; i < nof_checked; i++)
            for (S j = 0; j < nof_edges; j++)
                if (max_path[edges[j].from] != -1 && max_path[edges[j].to] < max_path[edges[j].from] + edges[j].weight)
                {
                    max_path[edges[j].to] = max_path[edges[j].from] + edges[j].weight;
                    nof_checked ++;
                }
        return max_path[end_node];
    }


};


int main()
{
    uint32_t nof_nodes, nof_edges, node_from, node_to, start, end;
    int node_weight, result;

    cin >> nof_nodes >> nof_edges;

    Graph<int, uint32_t> graph = Graph<int, uint32_t>(nof_nodes, nof_edges);

    for (uint32_t i = 0; i < nof_edges; i++)
    {
        cin >> node_from >> node_to >> node_weight;
        graph.insert(node_from - 1, node_to - 1, node_weight);
    }

    cin >> start >> end;


    if ((result = graph.solve(start - 1, end - 1)) == -1)
        cout << "No solution";
    else
        cout << result;

    return 0;
}