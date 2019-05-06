#include <iostream>
#include <map>
#include <cstdint>

using namespace std;

typedef uint64_t money_t;

struct city
{
    uint16_t num_of_days = 0;
    map<string, money_t> humans;
    money_t sum = 0;

//    explicit city(uint16_t numOfDays) : num_of_days(numOfDays)
//    {}

    void insert_human(string & name, money_t money)
    {
        humans[name] = money;
        sum += money;
    }

};


int main()
{
    map<string, city> world;
    uint16_t num_of_humans;
    string cur_name, cur_city;
    money_t cur_money;
    uint32_t num_of_moves, num_of_days, prev_day, cur_day = 1;
    //TODO: check if first cur_day is 0

    cin >> num_of_humans;
    for (uint16_t i = 0; i < num_of_humans; i++)
    {
        prev_day = cur_day;
        cin >> cur_name >> cur_city >> cur_money;
        auto richest_city = world.end();
        auto rich_city = richest_city--;
        rich_city--;
        // in case there only one richest city rn
        if (richest_city.operator*().second.sum != rich_city.operator*().second.sum)
            richest_city.operator*().second.num_of_days += cur_day - prev_day;





        world[cur_city].insert_human(cur_name, cur_money);
    }

    cin >> num_of_days >> num_of_moves;
    for (uint32_t i = 0; i < num_of_moves; i++)
    {
        cin >> cur_day >> cur_name >> cur_city;


    }

//    cout << world.begin().operator*().second.sum << " ";
    auto temp = world.end();
    temp--;




    return 0;
}

