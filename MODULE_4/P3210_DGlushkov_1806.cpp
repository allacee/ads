#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include <algorithm>

#define INF 10001

using namespace std;

class Graph
{
    vector<int> price;
    unordered_map<string, pair<int, unordered_map<string, int>>> edges;
    vector<string> id_to_num;
    vector<int> length;
    stack<int> path;
    vector<int> parents;

    int n, iter;


public:

    explicit Graph(int n): n(n)
    {
        length = vector<int>(2*n, INF);
        parents = vector<int>(2*n);
        id_to_num = vector<string>(2*n);
        iter = 0;
    }

    void insert_price(int val)
    {
        price.push_back(val);
    }

    void insert_num(string & val)
    {
        bool conn = false;

        edges[val].first = edges.size();
        id_to_num[iter++] = val;

        for (int i = 0; i < 10; i++)
        {
            for(int j = i + 1; j < 10; j++)
            {
                string temp = val;
                swap(temp[i], temp[j]);
                if(edges.find(temp) != edges.end() && temp != val)
                {
                    edges[val].second.insert({temp, price[i]});
                    edges[temp].second.insert({val, price[i]});
                }
            }

            for(char e = 48; e < 58; e++)
            {
                if(val[i] != e)
                {
                    string temp = val;
                    temp[i] = e;
                    if(edges.find(temp) != edges.end())
                    {
                        edges[val].second.insert({temp, price[i]});
                        edges[temp].second.insert({val, price[i]});
                    }
                }
            }

        }

    }

    void solve()
    {
        vector<bool> checked = vector<bool>(2*n, false);

        length[0] = 0;
        for (int i = 0; i < n; i++)
        {
            int v = -1;
            for (int j = 0; j < n; j++)
                if(!checked[j] && (v == -1 || length[j] < length[v]))
                    v = j;

            if(length[v] == INF)
                break;
            checked[v] = true;

            for (auto it : edges[id_to_num[v]].second)
            {
                int to = edges[it.first].first, len = it.second;
                if (length[v] + len < length[to])
                {
                    length[to] = length[v] + len;
                    parents[to] = v;
                }
            }
            if (v == n - 1)
                break;
        }
    }

    void print_result(int end)
    {

        if (length[end] == INF)
        {
            cout << "-1";
            return;
        }

        for (int i = end; i != 0; i = parents[i])
            path.push(i);
        path.push(0);

        cout << length[end] << '\n' << path.size() << '\n';
        while(!path.empty())
        {
            cout << path.top() + 1 << " ";
            path.pop();
        }

    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    int price;
    string num;

    cin >> n;
    Graph graph = Graph(n);

    for (int i = 0; i < 10; i++)
    {
        cin >> price;
        graph.insert_price(price);
    }

    for (int i = 0; i < n; i++)
    {
        cin >> num;
        graph.insert_num(num);
    }

    graph.solve();
    graph.print_result(n - 1);

    return 0;
}