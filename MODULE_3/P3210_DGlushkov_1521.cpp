/// this problem is pure evil, have fun
#include <iostream>
#include <vector>
#include <cstdint>

enum direction{
    none = 0,
    root = 1,
    left = 2,
    right = 3,
    up = 4
};

template <class T, class Size>
class Tree
{
    T * values;
    Size last_level;
    Size size;
    Size pop_step;
    Size current_node;

    void remove(Size cur_id)
    {
        do
            values[cur_id]--;
        while(to_father(cur_id));
    }

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


public:

    Tree (Size N, Size K)
    {
        last_level = 1;
        while (last_level < N)
            last_level = last_level << 1u;

        size = (last_level << 1u) - 1;
        pop_step = K;
        values = new T[size];
        current_node = 0;

        for (Size i = 0; i < N; i++)
            values[i + last_level - 1] = 1;
        for (Size i = N; i < last_level; i++)
            values[i + last_level - 1] = 0;

        for (int i = last_level - 2; i >= 0; i--)
        {
            Size temp_left = i, temp_right = i;

            values[i] = (to_left_son(temp_left) ? values[temp_left] : 0) +
                     (to_right_son(temp_right) ? values[temp_right] : 0);
        }



    }

    T pop()
    {
        if (current_node == 0)
        {
            current_node = last_level - 2 + pop_step;
            return current_node - last_level + 2;
        }

        remove(current_node);

        Size counter = pop_step ;
        direction prev = right;

        while(counter > 0)
        {
            Size temp_left = current_node, temp_right = current_node;
            bool success_left = to_left_son(temp_left), success_right = to_right_son(temp_right);

            switch(prev)
            {
                case right:
                {
                    Size father = current_node;
                    to_father(father);
                    to_right_son(father);
                    prev = father == current_node ? left : root;
                    current_node = father;
                    break;
                }

                case none:
                {
                    if(current_node > last_level - 1)
                        counter--;
                    else if(values[temp_left] < counter || !(temp_left <= (last_level - 1 + size) && temp_left > 0))
                    {
                        counter -= values[temp_left];
                        prev = none;
                        current_node = temp_right;
                    } else
                    {
                        prev = none;
                        current_node = temp_left;
                    }
                    break;
                }

                case root:
                {
                    if (values[temp_right] < counter || !(temp_right <= (last_level - 1 + size) && temp_right > 0))
                    {
                        counter -= values[temp_right];
                        if (current_node == 0)
                        {
                            current_node = last_level - 1;
                            prev = up;
                        }
                        else
                        {

                            Size father = current_node;
                            to_father(father);
                            to_right_son(father);
                            prev = father == current_node ? left : root;
                            to_father(current_node);
                        }
                    }
                    else
                    {
                        prev = none;
                        current_node = temp_right;
                    }
                    break;
                }
                case left:
                {
                    if (current_node == 0)
                    {
                        current_node = last_level - 1 ;
                        prev = up;
                    }
                    else
                    {
                        Size father = current_node;
                        to_father(father);
                        to_right_son(father);
                        prev = father == current_node ? left : root;
                        to_father(current_node);
                    }

                    break;
                }
                case up:
                {
                    counter -= values[current_node];
                    if (counter > 0)
                    {
                        prev = root;
                        to_father(current_node);
                    }

                    break;
                }
            }

        }
        return current_node - last_level + 2;
    }

};

using namespace std;

int main()
{
    int n, k;

    cin >> n >> k;

    if (k == 1)
    {
        for (int i = 1; i <= n; i++)
            cout << i << " ";
        return 0;
    }

    Tree<int, int> tree = Tree<int, int>(n, k);

    for (int i = 0; i < n; i++)
        cout << tree.pop() << " ";

    return 0;
}

