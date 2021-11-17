#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// struct
struct info
{
    char name[0x20];
    char channel[0x20];
    char twitter[0x20];
};

// global variable
struct info vTubers[5];

// function
void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

void banner()
{
    puts("");
    puts("          ▄ .▄      ▄▄▌        ▄▄▄▄▄            ▄▄▌  ");
    puts("         ██▪▐█▪     ██•  ▪     •██  ▪     ▪     ██•  ");
    puts("         ██▀▐█ ▄█▀▄ ██▪   ▄█▀▄  ▐█.▪ ▄█▀▄  ▄█▀▄ ██▪  ");
    puts("         ██▌▐▀▐█▌.▐▌▐█▌▐▌▐█▌.▐▌ ▐█▌·▐█▌.▐▌▐█▌.▐▌▐█▌▐▌");
    puts("         ▀▀▀ · ▀█▄▀▪.▀▀▀  ▀█▄▀▪ ▀▀▀  ▀█▄▀▪ ▀█▄▀▪.▀▀▀ ");
    puts("");
}

void init_info()
{
    strcpy(vTubers[0].name, "Gawr Gura");
    strcpy(vTubers[0].channel, "https://ppt.cc/fHT61x");
    strcpy(vTubers[0].twitter, "https://ppt.cc/fHP2Ax");

    strcpy(vTubers[1].name, "Watson Amelia");
    strcpy(vTubers[1].channel, "https://ppt.cc/fIaIsx");
    strcpy(vTubers[1].twitter, "https://ppt.cc/f675Ox");

    strcpy(vTubers[2].name, "Uruha Rushia");
    strcpy(vTubers[2].channel, "https://ppt.cc/fYCxrx");
    strcpy(vTubers[2].twitter, "https://ppt.cc/f4dK6x");

    strcpy(vTubers[3].name, "Usada Pekora");
    strcpy(vTubers[3].channel, "https://ppt.cc/fHdPDx");
    strcpy(vTubers[3].twitter, "https://ppt.cc/fqbVSx");

    strcpy(vTubers[4].name, "Shirakami Fubuki");
    strcpy(vTubers[4].channel, "https://ppt.cc/fG5UCx");
    strcpy(vTubers[4].twitter, "https://ppt.cc/fmEPUx");
}

int read_int()
{
    char buf[0x10];
    read(0, buf, 0x10);
    return atoi(buf);
}

void show_info()
{
    int idx = 0;
    puts("Enter which info to read (index should between 0-4)");
    write(1, "idx> ", 5);
    idx = read_int();

    if (idx >= 5)
    {
        puts("Invalid index!!");
        return;
    }

    printf("name: %s\n", vTubers[idx].name);
    printf("YT channel: %s\n", vTubers[idx].channel);
    printf("Twitter: %s\n", vTubers[idx].twitter);
}

void edit_info()
{
    int idx = 0;
    int choice = 0;
    char buf[0x20];
    puts("Enter which info to edit (index should between 0-4)");
    write(1, "idx> ", 5);
    idx = read_int();

    if (idx >= 5)
    {
        puts("Invalid index!!");
        return;
    }

    puts("Enter which info to edit");
    puts("1.name");
    puts("2.YT cahnnel");
    puts("3.Twitter");
    write(1, "> ", 2);
    choice = read_int();

    if (choice <= 0 || choice > 3)
    {
        puts("Wrong argument");
        return;
    }
    write(1, "Content: ", 9);
    read(0, buf, 0x20);

    switch (choice)
    {
    case 1:
        memcpy(vTubers[idx].name, buf, 0x20);
        break;
    case 2:
        memcpy(vTubers[idx].channel, buf, 0x20);
        break;
    case 3:
        memcpy(vTubers[idx].twitter, buf, 0x20);
        break;
    default:
        puts("Invalid argument");
    }

    puts("Edit success");
}

int main()
{
    init();
    banner();
    init_info();

    int choice;
    while (1)
    {
        puts("1. show info");
        puts("2. edit info");
        puts("3. exit");
        write(1, "> ", 2);
        choice = read_int();
        switch (choice)
        {
        case 1:
            show_info();
            break;
        case 2:
            edit_info();
            break;
        case 3:
            puts("bye~");
            exit(0);
        default:
            puts("Invalie choice!!");
        }
        puts("");
    }

    return 0;
}
