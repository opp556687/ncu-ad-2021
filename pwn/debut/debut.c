#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char name[0x20];
char fan_name[0x20];
unsigned long long fans = 0;
unsigned long long sc = 0;
int fan_2x = 0;
int fan_5x = 0;
int fan_10x = 0;
int fan_50x = 0;
int fan_100x = 0;
int stickers = 0;

void init()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

int read_int()
{
    char buf[0x10];
    read(0, buf, 0x10);
    return atoi(buf);
}

void menu()
{
    puts("======== VT ========");
    printf("name: %s\n", name);
    printf("fans: %llu\n", fans);
    printf("sc: %llu\n", sc);
    printf("number of stickers: %d\n", stickers);
    printf("[2x fan %s]\n", fan_2x ? "on" : "off");
    printf("[5x fan %s]\n", fan_5x ? "on" : "off");
    printf("[10x fan %s]\n", fan_10x ? "on" : "off");
    printf("[50x fan %s]\n", fan_50x ? "on" : "off");
    printf("[100x fan %s]\n", fan_100x ? "on" : "off");
    puts("====================");
    puts("");
    puts("What do you want to do?");
    puts("1. start stream");
    puts("2. shopping");
    puts("3. set fans name");
    puts("4. exit");
    write(1, "> ", 2);
}

void stream()
{
    unsigned long long fan_add = 100;
    if (fan_2x)
    {
        fan_add *= 2;
    }
    if (fan_5x)
    {
        fan_add *= 5;
    }
    if (fan_10x)
    {
        fan_add *= 10;
    }
    if (fan_50x)
    {
        fan_add *= 50;
    }
    if (fan_100x)
    {
        fan_add *= 100;
    }
    puts("Start streaming...");
    sleep(1);
    fans += fan_add;
    if (stickers)
    {
        sc += 1000 * stickers * 1.5;
    }
    else
    {
        sc += 1000;
    }
}

void shopping()
{
    char c;
    puts("Buy or Sell (B/S)");
    write(1, "> ", 2);
    c = getchar();
    if (c == 'B' || c == 'b')
    {
        puts("Which one to buy?");
        puts("1. fans number 2x every stream -- price: 81000 sc");
        puts("2. fans number 5x every stream -- price: 6666666 sc");
        puts("3. fans number 10x every stream -- price: 44500000 sc");
        puts("4. fans number 50x every stream -- price: 100000000 sc");
        puts("5. fans number 100x every stream -- price: 9999999999 sc");
        puts("6. membership stickers (one stickers sc 1.5x) -- price: 1500 sc");

        write(1, "> ", 2);
        int choice = read_int();
        switch (choice)
        {
        case 1:
            if (sc >= 81000)
            {
                fan_2x = 1;
                sc -= 81000;
                puts("buy success");
            }
            else
            {
                puts("you need more sc");
            }
            break;
        case 2:
            if (sc >= 6666666)
            {
                fan_5x = 1;
                sc -= 6666666;
                puts("buy success");
            }
            else
            {
                puts("you need more sc");
            }
            break;
        case 3:
            if (sc >= 44500000)
            {
                fan_10x = 1;
                sc -= 44500000;
                puts("buy success");
            }
            else
            {
                puts("you need more sc");
            }
            break;
        case 4:
            if (sc >= 100000000)
            {
                fan_50x = 1;
                sc -= 100000000;
                puts("buy success");
            }
            else
            {
                puts("you need more sc");
            }
            break;
        case 5:
            if (sc >= 9999999999)
            {
                fan_100x = 1;
                sc -= 9999999999;
                puts("buy success");
            }
            else
            {
                puts("you need more sc");
            }
            break;
        case 6:
            puts("How many stickers to buy? ");
            write(1, "> ", 2);
            int num = read_int();
            if (sc >= (1500 * num))
            {
                stickers += num;
                sc -= (1500 * num);
                printf("buy %d stickers success\n", num);
            }
            else
            {
                puts("you need more sc");
            }
            break;
        default:
            puts("Invalid operation!!");
            break;
        }
    }
    else if (c == 'S' || c == 's')
    {
        puts("How many stickers do you want to sell? ");
        write(1, "> ", 2);
        int num = read_int();
        if (stickers >= num)
        {
            stickers -= num;
            sc += num * 1000;
            printf("sell %d stickers success\n", num);
        }
        else
        {
            puts("Invalid num of stickers");
        }
    }
    else
    {
        puts("Invalid operation!!");
    }
}

void set_fan_name()
{
    if (fans >= 10000000 && stickers >= 200)
    {
        char buf[0x20];
        char y = '\0';

        while (1)
        {
            puts("Enter your fans name");
            write(1, "> ", 2);
            read(0, buf, (fans / 400000));
            printf("Set fans name to %s (Y/N)\n", buf);
            y = getchar();
            if (y == 'Y' || y == 'y')
            {
                break;
            }
        }

        strcpy(fan_name, buf);
        puts("Set fans name success");
    }
    else
    {
        puts("Only who has fans over 10M and stickers over 200 can set fans name");
    }
}

int main()
{
    init();
    puts("Today is your debut enter your name and start your vTuber life");
    write(1, "name: ", 6);
    read(0, name, 0x20);

    int choice = 0;
    while (1)
    {
        menu();
        choice = read_int();
        switch (choice)
        {
        case 1:
            stream();
            break;
        case 2:
            shopping();
            break;
        case 3:
            set_fan_name();
            break;
        case 4:
            puts("bye~");
            exit(0);
            break;
        default:
            puts("Invalid argument!!");
            break;
        }
    }

    return 0;
}
