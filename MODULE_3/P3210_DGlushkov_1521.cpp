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
    list<segment>::iterator cur_seg;
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

    next(cur_seg, 1);
//    cur_seg++;
	for(int i = 0; i < size; i++)
    {
	    next(cur_seg, dstep);
	    cur_seg++;
        temp =  &cur_seg.operator*();
	    cout << * temp -> current;
	    temp -> num--;
	    temp -> current++;
	    if (! temp -> num)
	        if (cur_seg == segments.end())
	            cur_seg
            else
	            segments.erase(cur_seg);



    }

//    for (int i = 0; i < 7; i++)
//    {
//        temp = &cur_seg.operator*();
//        cur_seg++;
//    }

//    for (int i = size)
//        cur_seg += dstep;
//        cout << cur_seg->current ;
//        cur_seg->num--;
//        if (cur_seg->num == 0)
//        {
//            // if num == 0,
//            // next or first
//            if(cur_seg = val)
//        }
//        cur_seg->current++;

    return 0;

}
