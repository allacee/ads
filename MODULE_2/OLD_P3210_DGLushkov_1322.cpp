//IM SO TIRED OF THIS sht

#include <stdint.h>
#include <iostream>
#include <algorithm>

using namespace std;

class Letter
{

private:
    char value;
    size_t id;

public:

    Letter()
    {
        id = 0;
        value = 0;
    }

    char getValue() const
    {
        return value;
    }

    void setValue(char let)
    {
        Letter::value = let;
    }

    size_t getId() const
    {
        return id;
    }

    void setId(size_t id)
    {
        Letter::id = id;
    }

};


int main()
{
    char prev_sym = 0;
    int counter;
    uint32_t in_id;
    size_t string_size;
    char in_string[100000];
    Letter * last_letters, * first_letters;
    char * result;

    size_t symbols[255];

    for (size_t i = 0; i < 100000; i++)
        in_string[i] = 0;

    for (size_t i = 0; i < 255; i++)
        symbols[i]=0;

    cin >> in_id;
    scanf("%s", in_string);
    in_id--;

    for(string_size = 0; string_size < 100000; string_size++)
        if (in_string[string_size] == '\0')
        {
            break;
        }

    first_letters = new Letter[string_size];
    last_letters = new Letter[string_size];
    result = new char[string_size];


    for (size_t i = 0; i < string_size; i++)
    {
        last_letters[i].setValue(in_string[i]);
        last_letters[i].setId(symbols[in_string[i]]++);
    }

    sort(in_string, in_string + string_size);

    counter = -1;
    prev_sym = in_string[0];
    for (size_t i = 0; i < string_size; i++)
    {
        first_letters[i].setValue(in_string[i]);

        if (prev_sym == in_string[i])
            first_letters[i].setId(static_cast<size_t>(++counter));
        else
        {
            prev_sym = in_string[i];
            counter = 0;
            first_letters[i].setId(static_cast<size_t>(counter));
        }
    }



  /*  for (size_t i = 0; i < string_size; i++)
    {
        cout << last_letters[i].getValue() << last_letters[i].getId() << " ";
    }
*/
    // rdarcaaaabb

/*    cout << endl;

    for (size_t i = 0; i < string_size; i++)
    {
        cout << first_letters[i].getValue() << first_letters[i].getId() << " ";
    }

    cout << endl;*/


    result[0] = first_letters[in_id].getValue();
    result[string_size - 1] = last_letters[in_id].getValue();
    result[string_size] = 0;

    char next_letter = first_letters[in_id].getValue();
    size_t cur_id = first_letters[in_id].getId();
//    cout << next_letter << cur_id << endl;



    for (size_t i = 1; i < string_size - 1; i++)
    {

        for (size_t j = 0; j < string_size ; j++)
        {

            if (cur_id == last_letters[j].getId() && next_letter == last_letters[j].getValue())
            {
                next_letter = first_letters[j].getValue();
                cur_id = first_letters[j].getId();
                break;
            }

        }
        result[i] = next_letter;

    }

    printf ("%s", result);

    delete[] result;
    delete[] last_letters;
    delete[] first_letters;

    return 0;
}
