#include <iostream>
#include <list>

using namespace std;

struct segment{
    int * current;
    int num;
};


int main()
{
    // TODO: move list to custom list to allow end->begin linking and erasing last node
    // store segments in a list ?

    int * values;
    int size, step, dstep;
    list<segment> segments;
    list<segment>::iterator cur_seg, last_seg;
    segment * temp;

    std::cin >> size >> step;

	dstep = step - 1;
    values = new int[size];

    for (int i = 0; i < size; i++)
        values[i] = i + 1;

    for (int i = 0; i < dstep; i++)
        segments.push_back({&values[i * dstep], dstep});
	segments.push_back({&values[dstep*dstep], size % dstep});

	//cur_seg points to first segment which points to the first element in value array
	cur_seg = segments.begin();
    last_seg = segments.end();
    last_seg--;

    cur_seg++;
	for(int i = 0; i < size; i++)
    {
        temp =  &cur_seg.operator*();
	    cout << * temp -> current << " ";
	    temp -> num--;
	    temp -> current++;

	    // removing this segment if it is empty
	    if (temp -> num == 0)
        {
	        // we only need to recalculate last when we removing something
            last_seg = segments.end();
            last_seg--;

	        //if cur_seg is the last element, then move it to start and remove last
            if(cur_seg == last_seg)
            {
                cur_seg = segments.begin();
                segments.erase(last_seg);
            }
            // Unfortunately I'm to stupid and lazy to check how erase works so
            // I'll just remove cur_seg by using last_seg (that's probably safe)
            else
            {
                last_seg = cur_seg;
                cur_seg++;
                segments.erase(last_seg);
            }
        }
	    //otherwise moving current pointer and moving to the next segment
	    else
        {
//	        cur_seg.operator*().current++;

	        // if cur_seg is the last element, then just move to start. else just inc cur_seg
            if(cur_seg == last_seg)
                cur_seg = segments.begin();

            cur_seg++;

        }

    }


    return 0;

}
