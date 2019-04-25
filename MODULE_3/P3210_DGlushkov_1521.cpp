#include <iostream>
#include <vector>
#include <cstdint>

enum direction{
    UP = 0,
    LEFT = 1,
    RIGHT = 2,
    NONE = 3,
    ROOT = 4
};

template <class T, class Size>
class Tree
{
    T * values;
    Size last_level;
    Size size;
    Size pop_step;
    Size current;


//TODO: remove
public:
    bool is_leaf(Size cur_id)
    {
        return cur_id >= last_level - 1;
    }

    void remove(Size cur_id)
    {
        do
        {
            // TODO: optional, remove later
            if (!values[cur_id])
                return;
            values[cur_id]--;
        }
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

    void fill(Size cur_id, int temp_N, int temp_last_level)
    {
        Size temp_cur_id = cur_id;
        values[temp_cur_id] = temp_N;

        if (temp_cur_id < last_level >> 1u)
        {
            to_left_son(temp_cur_id);
            fill(temp_cur_id, (temp_last_level / 2), (temp_last_level / 2));

            to_brother(temp_cur_id);
            fill(temp_cur_id, temp_N - (temp_last_level / 2), (temp_last_level / 2));
        }
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
        current = 0;

        fill(0, N, last_level);

        for (Size i = 0; i < N; i++)
            values[i + last_level - 1] = 1;
        for (Size i = N; i < last_level; i++)
            values[i + last_level - 1] = 0;

    }

    T pop()
    {
        if (current == 0)
        {
            current = last_level - 2 + pop_step;
            return current - last_level + 2;
        }

        remove(current);

        Size counter = pop_step ;
        direction prev = NONE;

//        std::cout << 'c' << ':' << current << '\n';

        while(counter > 0)
        {
            Size temp_left = current, temp_right = current;
            bool success_left = to_left_son(temp_left), success_right = to_right_son(temp_right);

            switch(prev)
            {
                case NONE:
                {
                    Size father = current;
                    to_father(father);
                    to_right_son(father);
                    prev = father == current ? RIGHT : LEFT;
                    current = father;
                    break;
                }

                case UP:
                {
                    if(is_leaf(current))
                        counter--;
                    else if(values[temp_left] < counter || !success_left)
                    {
                        counter -= values[temp_left];
                        prev = UP;
                        current = temp_right;
                    } else
                    {
                        prev = UP;
                        current = temp_left;
                    }
                    break;
                }

                case LEFT:
                {
                    if (values[temp_right] < counter || !success_right)
                    {
                        counter -= values[temp_right];
                        if (current == 0)
                        {
                            current = last_level - 1;
                            prev = ROOT;
                        }
                        else
                        {
                            Size father = current;
                            to_father(father);
                            to_right_son(father);
                            prev = father == current ? RIGHT : LEFT;
                            to_father(current);
                        }
                    }
                    else
                    {
                        prev = UP;
                        current = temp_right;
                    }
                    break;
                }
                case RIGHT:
                {
                    if (current == 0)
                    {
                        current = last_level;
                        prev = ROOT;
                    }
                    else
                    {
                        Size father = current;
                        to_father(father);
                        to_right_son(father);
                        prev = father == current ? RIGHT : LEFT;
                        to_father(current);
                    }

                    break;
                }
                case ROOT:
                {
                    counter -= values[current];
                    if (counter > 0)
                    {
                        prev = LEFT;
                        to_father(current);
                    }

                    break;
                }
            }

        }

        return current - last_level + 2;
    }

    void print()
    {
        std::cout << "===\n";
        for (int i = 0; i < size; i++)
        {
            std::cout << values[i] << " ";
        }
        std::cout << "\n===\n";
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

    if (k == 2)
    {
        for (int i = 2; i <= n; i+=2)
            cout << i << " ";
        for (int i = 1; i <= n; i+=2)
            cout << i << " ";
        return 0;

    }

    Tree<int, int> tree = Tree<int, int>(n, k);

    for (int i = 0; i < n; i++)
        cout << tree.pop() << " ";

    return 0;
}

