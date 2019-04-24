#include <iostream>
#include <list>

using namespace std;

struct segment{
    int * current;
    int num;
    int deleted;
};


/// this function moving cur_seg iterator
void next_seg(list<segment> & segments, int dstep, list<segment>::iterator & cur_seg, list<segment>::iterator & last_seg)
{
    bool all_counted = false;
    auto started_from = cur_seg;


    for (int counter = 1; counter > 0; counter--)
    {

        if(cur_seg == last_seg)
            cur_seg = segments.begin();
        else
            cur_seg++;

        if (!all_counted && cur_seg != started_from)
        {
            counter += cur_seg.operator*().deleted;
//            if(cur_seg == last_seg)
//                counter += last_num - cur_seg.operator*().num;
//            else
//                counter += dstep - cur_seg.operator*().num;
        }
        if (cur_seg == started_from)
            all_counted = true;

    }
}


int main()
{

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

    for (int i = 0; i < size / dstep; i++)
        segments.push_back({&values[i * dstep], dstep, 0});
	segments.push_back({&values[dstep*dstep], size % dstep, 0});

	///cur_seg points to first segment which points to the first element in value array
	cur_seg = segments.begin();
    last_seg = segments.end();
    last_seg--;

    cur_seg++;
	for(int i = 0; i < size; i++)
    {
        temp =  &cur_seg.operator*();
	    cout << * temp -> current << " ";
//	    temp -> num--;
	    temp -> current++;
	    temp -> deleted++;

	    /// removing this segment if it is empty
	    if (temp -> num == temp -> deleted)
        {
            /// if cur_seg is the last element, then move it to start and remove last
            if(cur_seg == last_seg)
            {
                cur_seg = segments.begin();
                segments.erase(last_seg);
            }
            /// Unfortunately I'm to stupid and lazy to check how erase works so
            /// I'll just remove cur_seg by using last_seg (that's probably safe)
            else
            {
                last_seg = cur_seg;
//                next_seg(segments, dstep, cur_seg, last_seg);
                cur_seg++;
                segments.erase(last_seg);
            }

            /// we only need to recalculate last when we removing something
            last_seg = segments.end();
            last_seg--;
        }
	    ///otherwise moving current pointer and moving to the next segment
	    else
        {

	        /// if cur_seg is the last element, then just move to start. else just inc cur_seg
//            if(cur_seg == last_seg)
//                cur_seg = segments.begin();
//
//            cur_seg++;
            next_seg(segments, dstep, cur_seg, last_seg);

        }

    }


    return 0;

}
