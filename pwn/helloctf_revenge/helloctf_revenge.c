#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    return;
}

void magic()
{
    system("/bin/sh");
    return;
}

int main()
{
    init();
    char buf[0x10];
    puts("I check every input so it is very safe now");

    puts("Do you like VTuber?");
    scanf("%s", buf);

    if (strlen(buf) > 0x10)
    {
        puts("input toooooooo long");
        exit(0);
    }

    if (strcmp(buf, "yes"))
    {
        puts(" (✖╭╮✖)  (✖╭╮✖)  (✖╭╮✖)");
        exit(0);
    }

    return 0;
}