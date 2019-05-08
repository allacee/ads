#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

template <class T, class S>
class Graph
{

//TODO: REMOVE
public:
    map<S, map<S, T>> edges;
    S nof_nodes;
    vector<T> max_path;
    stack<S> top_order;
    bool * checked;

    void topological_sort(S cur_node = 0)
    {
        for (auto it : edges[cur_node])
            if (it.second > 0)
                topological_sort(it.first);

        if(!checked[cur_node])
        {
            checked[cur_node] = true;
            top_order.push(cur_node);
        }
    }

public:
    explicit Graph(S nof_nodes): nof_nodes(nof_nodes)
    {
        max_path = vector<T>(nof_nodes, 0);
        checked = new bool[nof_nodes];
        for (S i = 0; i < nof_nodes; i++)
        {
            edges[i] = map<S, T>();
            checked[i] = false;
        }
    }

    void insert_edge(S from, S to, T weight)
    {
        edges[from].insert({to, weight});
        edges[to].insert({from, -1*weight});
    }

    void solve(S root)
    {
        topological_sort(root);

        S prev_node, cur_node;

        while (!top_order.empty())
        {
            prev_node = cur_node;
            cur_node = top_order.top();
            top_order.pop();

            for (auto it : edges[cur_node])
            {
                if (it.second < 0)
                {
                    S temp = max_path[it.first] - it.second;
                    if (temp > max_path[cur_node])
                        max_path[cur_node] = temp;
                }
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
    int nof_nodes, nof_edges, node_from, node_to, node_weight;
    cin >> nof_nodes >> nof_edges;
    Graph<int, int> graph(nof_nodes);

    for (int i = 0; i < nof_edges; i++)
    {
        cin >> node_from >> node_to >> node_weight;
        graph.insert_edge(node_from - 1, node_to - 1, node_weight);
    }

    cin >> node_from >> node_to;

    graph.solve(node_from - 1);
//    graph.topological_sort(node_from - 1);
    graph.print_result(node_to - 1);
    return 0;
}