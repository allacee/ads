#include <iostream>
#include <stack>
#include <cstdint>
#include <vector>

using namespace std;


int main()
{
    uint32_t N, temp;
    int counter_lower = 0, counter_bigger = 0;
    stack<uint32_t> main;
    vector<int> lower, bigger;

    cin >> N;

    lower = vector<int>(N / 2 + 1);
    bigger = vector<int>(N / 2 + 1);

    for (uint32_t i = 0; i < N; i++)
    {
        cin >> temp;
        main.push(temp);
    }

//    temp = N % 2 == 0 ? N / 2 : N / 2 + 1;

    if (!(N % 2))
    {
        temp = N / 2 + 1;
        for (uint32_t i = 0; i < N; i++)
        {
            if(main.top() > temp)
                bigger.push_back(main.top());
            else if(main.top() < temp)
                lower.push_back(main.top());
            main.pop();
        }
    }
    else
    {
        temp = N / 2;
        for (uint32_t i = 0; i < N; i++)
        {
            if(main.top() <= temp)
                lower.push_back(main.top());
            else
                bigger.push_back(main.top());
            main.pop();
        }
    }

    for (uint32_t i = 1; i < N; i++)
    {
        if (lower[i] > lower [i - 1])
            counter_lower++;
        else
            counter_lower--;

        if (bigger[i] > bigger [i - 1])
            counter_bigger++;
        else
            counter_bigger--;
    }

    for (auto it: lower)
        cout << it << " ";

    if (counter_bigger - counter_lower == N || counter_bigger - counter_lower == -N || counter_bigger - counter_lower == 0)
        cout << "Not a proof";
    else
        cout << "Cheater";

    return 0;
}