#include <stdio.h>

int main() {
    int *numbers;
    numbers = (int)malloc(50 * sizeof(int));

    numbers[0] = 1;

    return 0;
}