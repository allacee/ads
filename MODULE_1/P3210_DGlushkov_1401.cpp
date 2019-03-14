#include <stdio.h>
#include <stdint.h>
#include <math.h>

//number of next figure
static uint16_t num = 0;

typedef struct{
    uint32_t raw;
    uint32_t col;
} coord_t;

void create_figure(uint32_t ** matrix, coord_t point)
{

    coord_t is_even = {point.raw % 2, point.col % 2};

    if(is_even.raw && is_even.col)
        matrix[point.raw - 1][point.col - 1]
                = matrix[point.raw - 1][point.col]
                = matrix[point.raw][point.col - 1]
                = ++num;

    else if(!is_even.raw && !is_even.col)
        matrix[point.raw + 1][point.col + 1]
                = matrix[point.raw + 1][point.col]
                = matrix[point.raw][point.col + 1]
                = ++num;

    else if(!is_even.raw && is_even.col)
        matrix[point.raw + 1][point.col]
                = matrix[point.raw][point.col - 1]
                = matrix[point.raw + 1][point.col - 1]
                = ++num;

    else if(is_even.raw && !is_even.col)
        matrix[point.raw - 1][point.col]
                = matrix[point.raw][point.col + 1]
                = matrix[point.raw - 1][point.col + 1]
                = ++num;



}

void solve(uint32_t ** matrix, uint32_t side_size, coord_t start, coord_t point)
{

    if(side_size == 2)
    {
        create_figure(matrix, {start.raw + point.raw % 2, start.col + point.col % 2});
        return;
    }
    uint32_t new_side_size = side_size / 2;

    if (point.raw>= new_side_size && point.col >= new_side_size) {
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col + new_side_size}, {point.raw - new_side_size, point.col - new_side_size});

        matrix[start.raw + new_side_size - 1][start.col + new_side_size - 1] =
        matrix[start.raw + new_side_size][start.col + new_side_size - 1] =
        matrix[start.raw + new_side_size - 1][start.col + new_side_size] = ++num;

        solve(matrix, new_side_size, {start.raw, start.col + new_side_size}, {new_side_size - 1, 0});
        solve(matrix, new_side_size, {start.raw, start.col}, {new_side_size - 1, new_side_size - 1});
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col}, {0, new_side_size - 1});

    }
    else if (point.raw < new_side_size && point.col < new_side_size) {
        solve(matrix, new_side_size, {start.raw, start.col}, { point.raw, point.col});

        matrix[start.raw + new_side_size][start.col + new_side_size] =
        matrix[start.raw + new_side_size][start.col + new_side_size - 1] =
        matrix[start.raw + new_side_size - 1][start.col + new_side_size] = ++num;

        solve(matrix, new_side_size, {start.raw + new_side_size, start.col + new_side_size}, { 0, 0});
        solve(matrix, new_side_size, {start.raw, start.col + new_side_size}, { new_side_size - 1, 0});
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col}, { 0, new_side_size - 1});

    }
    else if (point.raw < new_side_size && point.col >= new_side_size) {
        solve(matrix, new_side_size, {start.raw, start.col + new_side_size}, { point.raw, point.col - new_side_size});

        matrix[start.raw + new_side_size][start.col + new_side_size] =
        matrix[start.raw + new_side_size][start.col + new_side_size - 1] =
        matrix[start.raw + new_side_size - 1][start.col + new_side_size - 1] = ++num;

        solve(matrix, new_side_size, {start.raw, start.col}, { new_side_size - 1, new_side_size - 1});
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col + new_side_size}, { 0, 0});
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col}, { 0, new_side_size - 1});

    }
    else {
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col}, { point.raw - new_side_size, point.col});

        matrix[start.raw + new_side_size][start.col + new_side_size] =
        matrix[start.raw + new_side_size - 1][start.col + new_side_size] =
        matrix[start.raw + new_side_size - 1][start.col + new_side_size - 1] = ++num;

        solve(matrix, new_side_size, {start.raw, start.col}, {new_side_size - 1, new_side_size - 1});
        solve(matrix, new_side_size, {start.raw + new_side_size, start.col + new_side_size}, { 0, 0});
        solve(matrix, new_side_size, {start.raw, start.col + new_side_size}, { new_side_size - 1, 0});
    }

}

int main()
{

    uint32_t ** matrix, side_size;
    uint8_t n;
    coord_t point;
    scanf("%hhu %u %u", &n, &point.raw, &point.col);
    side_size = (uint32_t) pow(2, n);

    matrix = new uint32_t * [side_size];
    for(uint32_t i = 0; i < side_size; i++)
    {
        matrix[i] = new uint32_t[side_size];
        for (uint32_t j = 0; j < side_size; j++)
            matrix[i][j] = 0;
    }

    point.raw--; point.col--;
    solve(matrix, side_size, {0, 0}, point);

    for(uint32_t i = 0; i < side_size; i++)
    {
        for(uint32_t j = 0; j < side_size; j++)
            printf("%2d ", matrix[i][j]);

        printf("\n");
    }
    return 0;

}