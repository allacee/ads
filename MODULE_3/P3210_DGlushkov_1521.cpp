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
    //Size cur_id;

private:

    bool to_left_son(Size& cur_id)
    {
        if (2 * cur_id + 2 < size)
        {
            cur_id = 2 * cur_id + 1;
            return true;
        }
        else return false;
    }

    bool to_right_son(Size& cur_id)
    {
        if (2 * cur_id + 2 < size)
        {
            cur_id = 2 * cur_id + 2;
            return true;
        }
        else return false;
    }

    bool to_father(Size& cur_id)
    {
        if (cur_id != 0)
        {
            cur_id = (cur_id - 1) / 2;
            return true;
        }
        else return false;
    }

    bool to_brother(Size& cur_id)
    {
        if (cur_id != 0)
        {
            if(cur_id % 2)
            {
                to_father(cur_id);
                to_right_son(cur_id);
            }
            else
            {
                to_father(cur_id);
                to_left_son(cur_id);
            }
            return true;
        }
        else return false;
    }

    void fill(Size cur_id, int temp_N, int temp_last_level)
    {
        Size temp_cur_id = cur_id;
        values[temp_cur_id] = temp_N;

        if (temp_cur_id < last_level >> 2u)
        {
            to_left_son(temp_cur_id);
            fill(temp_cur_id, (temp_last_level / 2), (temp_last_level / 2));

            to_brother(temp_cur_id);
            fill(temp_cur_id, temp_N - (temp_last_level / 2), (temp_last_level / 2));
        }
    }

public:

    Tree (Size N)
    {
        last_level = 1;
        while (last_level < N)
            last_level = last_level << 1u;

        size = (last_level << 1u) - 1;
        values = new T[size];

        // TODO: replace recursion with cycles
        fill(0, N, last_level);

        for (Size i = 0; i < N; i++)
            values[i + last_level - 1] = 1;

        for (Size i = N; i < last_level; i++)
            values[i + last_level - 1] = 0;


    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << values[i] << " ";
            if (i == 0 || i == 2 || i == 6 || i == 14 || i == 30 || i ==31)
                std::cout << std::endl;
        }
    }



};

//using namespace std;

int main()
{
    Tree<int, int> tree = Tree<int, int>(3);

//    tree.test();
//    std::cout << tree.cur_id;

    tree.print();
    return 0;
}
