#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    char pw[10];
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        pw[i] = 33 + (rand() % (126 - 32) + 1);
    }
    printf("pw: %s\n", pw);
}