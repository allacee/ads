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
    unordered_map<int64_t, pair<int16_t, unordered_map<int64_t, int16_t>>> edges;
    vector<int64_t> id_to_num;
    vector<int32_t> length;
    stack<int16_t> path;
    vector<int16_t> parents;

    int32_t n, iter;

    static pair<int16_t, int16_t> compare_nums(int64_t num1, int64_t num2, bool & conn)
    {
        int16_t first_diff = -1, num_of_diff = 0;
        pair<int16_t, int16_t> first = {-1, -1}, second = {-1, -1};
        for(int16_t i = 9; num1 > 0 || num2 > 0; num1/=10, num2/=10, i--)
        {
            if (num1 % 10 != num2 % 10)
            {
                if (num_of_diff == 2)
                {
                    return {first_diff, num_of_diff};
                }

                num_of_diff++;
                first_diff = i;
                first.first = num1 % 10;
                second.first = num2 % 10;
                if (first.second == -1)
                {
                    first.second = num1 % 10;
                    second.second = num2 % 10;
                }
            }
        }

        if (num_of_diff == 1 || (num_of_diff == 2 && first.first == second.second && first.second == second.first))
            conn = true;
        return {first_diff, num_of_diff};
    }

public:

    explicit Graph(int32_t n): n(n)
    {
        length = vector<int32_t>(n, INF);
        parents = vector<int16_t>(n);
        id_to_num = vector<int64_t>(n);
        iter = 0;
    }

    void insert_price(int16_t val)
    {
        price.push_back(val);
    }

    void insert_num(int64_t val)
    {
        bool conn = false;

        edges[val].first = edges.size();
        id_to_num[iter++] = val;

        for(auto & it: edges)
        {
            auto diff = compare_nums(val, it.first, conn);
            if (conn)
            {
                it.second.second.insert({val, price[diff.first]});
                edges[val].second.insert({it.first, price[diff.first]});
                conn = false;
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

            for (auto it : edges[id_to_num[v]].second)
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
    int64_t num;

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