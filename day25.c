#include <stdio.h>

#define ROW 2947
#define COL 3029

size_t col = 1;
size_t row = 1;

size_t calc(size_t val)
{
    const size_t mul = 252533;
    const size_t div = 33554393;
    static size_t start_row = 1;

    --row;
    ++col;
    if (row == 0)
    {
        row = ++start_row;
        col = 1;
    }
    return (val * mul) % div;
}

int main(void)
{
    size_t code = 20151125;

    do
        code = calc(code);
    while (row != ROW || COL != col);

    printf("Code: %zu\n", code);

    return 0;
}
