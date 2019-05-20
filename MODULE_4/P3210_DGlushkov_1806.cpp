#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph
{
    vector<int16_t> price = vector<int16_t>(10);
    map<int64_t, map<int64_t, int16_t>> edges;

    pair<int16_t, int16_t> compare_num(string & str1, string & str2)
    {
        int16_t first_diff = -1, num_of_diff = 0;
        for (int16_t i = 0; i < str1.size(); i++)
        {
            if(str1[i] != str2[i])
            {
                num_of_diff++;
                if(first_diff == -1)
                    first_diff = i;
            }
        }
        return {first_diff, num_of_diff};
    }

    pair<int16_t, int16_t> compare_nums(int64_t num1, int16_t num2)
    {
        int16_t first_diff = -1, num_of_diff = 0;
        for(int16_t i = 9; num1 > 0 || num2 > 0; num1/=10, num2/=10, i--)
        {
            if (num1 % 10 != num2 % 10)
            {
                num_of_diff++;
                first_diff = i;
            }
        }

        return {first_diff, num_of_diff};
    }

    int64_t str_to_int64(string & str)
    {
        int64_t num = 0;
        for(char ch : str)
            num = num * 10 + ch - '0';
        return num;
    }

public:


    void insert_price(int16_t val)
    {
        price.push_back(val);
    }

    void insert_num(int64_t val)
    {

        for(auto it: edges)
        {
            auto diff = compare_nums(val, it.first);
            if (diff.second == 1)
            {
                it.second.insert({val, price[diff.first]});
                edges[val].insert({it.first, price[diff.first]});
            }
        }

    }



};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int16_t n;
    string num;

    cin >> n;
    Graph graph = Graph();




    return 0;
}