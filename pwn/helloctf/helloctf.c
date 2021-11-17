#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    return;
}

void magic()
{
    execve("/bin/sh", NULL, NULL);
    return;
}

int main()
{
    init();
    char buf[0x10];
    puts("Do you like VTuber?");
    gets(buf);
    if (strncmp(buf, "yes", 3))
        exit(0);
    return 0;
}