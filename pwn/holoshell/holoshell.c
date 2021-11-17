#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char passwd[10];

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        passwd[i] = 33 + (rand() % (126 - 32) + 1);
    }
}

void login_info()
{
    puts("Welcome to Ubuntu 20.04.2 LTS (GNU/Linux 5.11.0-36-generic x86_64)");
    puts("");
    puts("* Documentation:  https://help.ubuntu.com");
    puts("* Management:     https://landscape.canonical.com");
    puts("* Support:        https://ubuntu.com/advantage");
    puts("");
    puts("183 updates can be installed immediately.");
    puts("0 of these updates are security updates.");
    puts("To see these additional updates run: apt list --upgradable");
    puts("");
    puts("Your Hardware Enablement Stack (HWE) is supported until April 2025.");
}

void ls()
{
    puts("holo_shell holo_shell.c flag");
}

void cat()
{
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠎⠓⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠎⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠱⡀⠀⠀⣀⣀⣀⣀⣠⠤⠤⠤⢤⣀⣀⠀⠀⠀⡎⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠸⠀⠾⠓⢠⢜⣍⡿⣫⣷⣐⡄⠀⠀⠀⠀⠀⠀⡸⢏⣛⣶⣞⢹⡠⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⣠⠔⠃⠀⠀⢿⣮⢧⣿⣿⠿⢝⠇⠀⠀⠀⠀⠀⢸⢁⢯⣿⣞⡽⢹⠇⠈⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⡴⠁⠀⠀⠀⠀⠈⠈⠂⠭⠭⠐⠉⢠⣖⡆⠀⠀⠀⠀⠀⢉⣙⠋⠦⠋⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⢸⠁⠀⠀⠀⠀⠀⠀⠀⠀⡠⡀⠀⠀⠀⠉⠀⠀⢀⠔⡆⠀⠀⠀⠀⠀⠒⠒⠒⢻⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⢸⠤⠴⠒⠀⠀⠀⠀⠀⠀⢹⠙⣄⡀⠀⢀⣠⠴⠋⢰⠇⠀⠀⠀⠀⠀⠀⠀⢀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠈⣷⠖⠋⣡⠀⠀⠀⠀⠀⢸⡄⠀⠉⠉⠉⠀⠀⢀⡞⠀⠀⠀⠀⠀⠤⣄⣀⠜⠁⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢱⡄⠀⠀⠀⠀");
    puts("⠀⠀⠈⠀⠘⠶⣞⡁⡀⠀⠀⠀⠀⠀⠹⢦⣀⡀⠀⢀⣠⠎⠀⠀⠀⠀⠀⠀⣀⠔⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⡄⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠒⢲⠒⠶⠶⠶⠾⠿⠯⠭⢤⣤⣤⠤⠴⠶⠖⠋⠑⠒⠢⠤⠤⠤⠀⣀⣀⣀⣀⣀⠀⠀⠀⠀⢀⠁⡇⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢹⠊⠀⡇⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡄⡰⠁⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠒⠒⠒⠂⠀⠤⠤⠤⠤⠤⠤⠤⠀⠀⠀⡀⠀⠀⢀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⢸⠁⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠀⢠⢻⠀⢠⢧⢠⣇⠀⠀⢠⠤⠒⠉⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⡄⠎⠀⣄⡆⠘⠾⠈⡄⢀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠘⠀⠀⠀⠀⠘⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
    puts("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");
}

void sudo()
{
    char buf[10];
    char *command;
    write(1, "[sudo] password for yagoo: ", 27);
    read(0, buf, 10);
    if (strncmp(buf, passwd, 10) == 0)
    {
        puts("wow you hack into yagoo's computer");
        puts("now you have one chance to write your name to HololiveTW");
        write(1, "> ", 2);
        memset(buf, 0, 10);
        read(0, buf, 10);
        asprintf(&command, "echo \"%s\" >> HololiveTW.txt", buf);
        system(command);
        free(command);
        command = NULL;
    }
    else
    {
        puts("sudo: 1 incorrect password attempt");
    }
}

void parse_command(char *arg)
{
    if (strncmp(arg, "cat", 3) == 0)
    {
        cat();
    }
    else if (strncmp(arg, "ls", 2) == 0)
    {
        ls();
    }
    else if (strncmp(arg, "sudo -s", 7) == 0)
    {
        sudo();
    }
    else if (strncmp(arg, "exit", 4) == 0)
    {
        exit(0);
    }
    else
    {
        puts("holosh: command not found");
    }
}

int main()
{
    char command[0x10];
    init();
    login_info();

    while (1)
    {
        write(1, "yagoo@hololive:~$ ", 18);
        read(0, command, 0x10);
        parse_command(command);
    }

    return 0;
}