#include <stdio.h>

int main()
{
    int n, square, cube;

    printf("Enter a number: ");
    scanf("%d", &n);

    square = n * n;
    cube = n * n * n;

    printf("Square = %d\n", square);
    printf("Cube = %d", cube);

    return 0;
}
