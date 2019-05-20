#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph
{
    vector<int16_t> price;
    map<int64_t, map<int64_t, int16_t>> edges;

    static pair<int16_t, int16_t> compare_nums(int64_t num1, int64_t num2, bool & conn)
    {
        int16_t first_diff = -1, num_of_diff = 0;
        pair<int16_t, int16_t> first = {-1, -1}, second = {-1, -1};
        for(int16_t i = 9; num1 > 0 || num2 > 0; num1/=10, num2/=10, i--)
        {
            if (num1 % 10 != num2 % 10)
            {
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

    void insert_price(int16_t val)
    {
        price.push_back(val);
    }

    void insert_num(int64_t val)
    {
        edges[val];
        bool conn = false;

        for(auto & it: edges)
        {
            auto diff = compare_nums(val, it.first, conn);
            if (conn)
            {
                it.second.insert({val, price[diff.first]});
                edges[val].insert({it.first, price[diff.first]});
                conn = false;
            }
        }

    }

};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    uint16_t n;
    int16_t price;
    int64_t num;

    cin >> n;
    Graph graph = Graph();

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



    return 0;
}