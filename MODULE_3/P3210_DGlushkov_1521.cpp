#include <iostream>
#include <vector>
#include <cstdint>

template <class T, class Size>
class Tree
{
    T * values;
    Size last_level;
    Size size;

public:
    Size cur_id;

private:

    void to_left_son()
    {
        if (2 * cur_id + 2 < size)
            cur_id = 2 * cur_id + 1;
    }

    void to_right_son()
    {
        if (2 * cur_id + 2 < size)
            cur_id = 2 * cur_id + 2;
    }

    void to_father()
    {
        if (cur_id != 0)
            cur_id = (cur_id - 1) / 2;
    }

    void to_brother()
    {
        if (cur_id != 0)
        {
            if(cur_id % 2)
            {
                to_father();
                to_right_son();
            } else
            {
                to_father();
                to_left_son();
            }
        }
    }

public:

    Tree (Size N)
    {
        last_level = 1;
        while (last_level < N)
            last_level = last_level << 1u;

        /// check if this -1 is needed
        size = last_level << 1u - 1;
        values = new T[size];
        cur_id = 0;

        //TODO: после заполнения дерева переставить указатель на самый левый элемент

    }

    // переместиться из текущей ячейки в ячейку += k
    // при этом мы перемешаемся только по нижнему уровню






};

//using namespace std;

int main()
{
//    Tree<int, int> tree = Tree<int, int>(6);


    return 0;
}
