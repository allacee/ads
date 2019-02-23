#include "stdio.h"

/*
 * Команд - от 2 до k
 * Бойцов - n, каждый боец ровно в одной команде
 * 2 бойца сразятся в течение боя, если они в разных командах
 * Максимизировать количество схваток
 *
 * Вход: количество тестов
 * Вход: n k
 * Выход: количество схваток
 */


/*
 * t - num of tests
 * n - num of fighters
 * k - num of teams
 * a - value of n div k
 * b = a + 1
 * r - value of n mod k - num of b
 * nta - num of a
 */
int main()
{
    int t, n, k, a, b, r, nta;
    scanf("%d", &t);
    for(int j = 0; j < t; j++)
    {
        scanf("%d %d", &n, &k);
        a = n / k;
        b = a + 1;
        r = n % k;
        nta = k - r;
        printf("%d\n", r*(r-1)/2*b*b + nta*(nta-1)/2*a*a + nta*r*a*b);
    }

    return 0;
}