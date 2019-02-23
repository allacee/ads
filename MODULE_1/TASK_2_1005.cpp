#include <stdio.h>

/*
 * У вас есть несколько камней известного веса w1, …, wn.
 * Напишите программу, которая распределит камни в две кучи так,
 * что разность весов этих двух куч будет минимальной.
 * Исходные данные
 * Ввод содержит количество камней n (1 ≤ n ≤ 20) и веса камней w1, …, wn (1 ≤ wi ≤ 100 000) — целые, разделённые пробельными символами.
 * Результат
 * Ваша программа должна вывести одно число — минимальную разность весов двух куч.
 */

//fail on 5 2 3 2 3 2
//THIS ON FAILS!
int main()
{
    int num;

    scanf("%d", &num);
    int arr[num], s1 = 0, s2 = 0, max = 0, maxid;

    for (int i = 0; i < num; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            if ( arr[j] > max )
            {
                max = arr[j];
                maxid = j;
            }
        }

        if (s1 > s2)
            s2 += max;
        else s1 += max;

        arr[maxid] = 0;
        max = 0;
    }

    printf("first : %d, second: %d\n", s1, s2);
    printf("%d", s1 > s2? s1-s2 : s2-s1);

    return 0;
}