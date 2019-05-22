#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <deque>
#include <queue>
#include <cmath>

#define INF 64000u

using namespace std;

class Graph
{
    vector<uint16_t> price;
    unordered_map<int64_t, pair<uint16_t, unordered_map<int64_t, uint16_t>>> edges;
    vector<int64_t> id_to_num;
    vector<uint16_t> length;
    deque<uint16_t> path;
    vector<uint16_t> parents;
    uint16_t n, iter;

    inline int64_t swap_digits(int64_t num, int16_t src, int16_t dst)
    {
        int64_t res = num;
        auto pow1 = (int64_t)(pow(10, 9 - src)), pos2 = (int64_t)(pow(10, 9 - dst));
        int16_t dig1 = (num / pow1) % 10, dig2 = (num / pos2) % 10;
        res -= pow1 * dig1;
        res -= pos2 * dig2;
        res += pos2 * dig1;
        res += pow1 * dig2;
        return res;
    }

    inline int64_t change_digit(int64_t num, int16_t pos, int16_t new_val)
    {
        int64_t res = num;
        auto pow1 = (int64_t)(pow(10, 9 - pos));
        int16_t dig1 = (num / pow1) % 10;
        res -= (dig1 - new_val) * pow1;
        return res;
    }


public:

    explicit Graph(uint16_t n): n(n)
    {
        length = vector<uint16_t>(n + 5, INF);
        parents = vector<uint16_t>(n + 5);
        id_to_num = vector<int64_t>(n + 5);
        iter = 0;
    }

    void insert_price(uint16_t val)
    {
        price.push_back(val);
    }

    void insert_num(int64_t & val_num)
    {

        edges[val_num].first = edges.size();
        id_to_num[iter++] = val_num;

        for (int16_t i = 0; i < 10; i++)
        {
            for(int16_t j = i + 1; j < 10; j++)
            {
                int64_t temp = swap_digits(val_num, i, j);

                if(edges.find(temp) != edges.end() && temp != val_num)
                {
                    edges[val_num].second.insert({temp, price[i]});
                    edges[temp].second.insert({val_num, price[i]});
                }
            }

            for(int16_t ch = 0; ch < 9; ch++)
            {

                int64_t temp = change_digit(val_num, i, ch);
                if(edges.find(temp) != edges.end() && temp != val_num)
                {
                    edges[val_num].second.insert({temp, price[i]});
                    edges[temp].second.insert({val_num, price[i]});
                }

            }

        }

    }

    void solve()
    {
        priority_queue <pair<uint16_t, uint16_t>> que;

        length[0] = 0;
        que.push({0, 0});
        while(!que.empty())
        {
            uint16_t v = que.top().second;
            que.pop();

            for (auto it : edges[id_to_num[v]].second)
            {
                uint16_t to = edges[it.first].first, len = it.second;
                if (length[v] + len < length[to])
                {
                    length[to] = length[v] + len;
                    parents[to] = v;
                    que.push({length[to], to});
                }
            }
        }
    }



    void print_result(uint16_t end)
    {

        if (length[end] == INF)
        {
            cout << "-1";
            return;
        }

        for (int64_t i = end; i != 0; i = parents[i])
            path.push_front(i);
        path.push_front(0);

        cout << length[end] << '\n' << path.size() << '\n';
        for (auto i : path)
            cout << i + 1 << " ";
    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint16_t n;
    uint16_t price;
    int64_t num;

    cin >> n;
    Graph graph = Graph(n);

    for (int16_t i = 0; i < 10; i++)
    {
        cin >> price;
        graph.insert_price(price);
    }

    for (uint16_t i = 0; i < n; i++)
    {
        cin >> num;
        graph.insert_num(num);
    }

    graph.solve();
    graph.print_result(n - 1);

    return 0;
}