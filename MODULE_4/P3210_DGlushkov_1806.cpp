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
    vector<int16_t> price;
    unordered_map<string, pair<int16_t, unordered_map<string, int16_t>>> edges;
    vector<string> id_to_num;
    vector<int32_t> length;
    stack<int16_t> path;
    vector<int16_t> parents;

    int32_t n, iter;


public:

    explicit Graph(int32_t n): n(n)
    {
        length = vector<int32_t>(n, INF);
        parents = vector<int16_t>(n);
        id_to_num = vector<string>(n);
        iter = 0;
    }

    void insert_price(int16_t val)
    {
        price.push_back(val);
    }

    void insert_num(string & val)
    {
        bool conn = false;

        edges[val].first = edges.size();
        id_to_num[iter++] = val;

        for(auto & it: edges)
            //it.first <- следующий узел
            for (int16_t i = 0, first_diff = 0, counter = 0; i < 10; i++)
            {
                if (val[i] != it.first[i])
                {
                    if (counter == 0)
                    {
                        string temp = val;
                        temp[i] = it.first[i];
                        first_diff = i;
                        if (temp == it.first)
                        {
                            it.second.second.insert({val, price[first_diff]});
                            edges[val].second.insert({it.first, price[first_diff]});
                            break;
                        }
                        else
                            counter++;
                    }
                    else if (counter == 1)
                    {
                        string temp = val;
                        swap(temp[first_diff], temp[i]);
                        if (temp == it.first)
                        {
                            it.second.second.insert({val, price[first_diff]});
                            edges[val].second.insert({it.first, price[first_diff]});
                        }
                        break;
                    }
                }
            }
    }

    void solve()
    {
        vector<bool> checked = vector<bool>(n, false);

        length[0] = 0;
        for (int32_t i = 0; i < n; i++)
        {
            int32_t v = -1;
            for (int32_t j = 0; j < n; j++)
                if(!checked[j] && (v == -1 || length[j] < length[v]))
                    v = j;

            if(length[v] == INF)
                break;
            checked[v] = true;

            for (const auto& it : edges[id_to_num[v]].second)
            {
                int16_t to = edges[it.first].first, len = it.second;
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

    void print_result(int16_t end)
    {

        if (length[end] == INF)
        {
            cout << "-1";
            return;
        }

        for (int16_t i = end; i != 0; i = parents[i])
            path.push(i);
        path.push(0);

        cout << length[end] << '\n'
        << path.size() << '\n';
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

    int32_t n;
    int16_t price;
    string num;

    cin >> n;
    Graph graph = Graph(n);

    for (int16_t i = 0; i < 10; i++)
    {
        cin >> price;
        graph.insert_price(price);
    }

    for (int16_t i = 0; i < n; i++)
    {
        cin >> num;
        graph.insert_num(num);
    }

    graph.solve();
    graph.print_result(n - 1);

    return 0;
}