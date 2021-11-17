# 2021 攻防 HW1 writeup

## helloctf_revenge
### 考點
1. BOA
2. '\0'繞過strlen
3. stack alignment
### exploit
本題主要漏洞位置在於`sacnf("%s")`沒有對輸入的長度做限制，所以就存在buffer overflow的漏洞
```c=
scanf("%s", buf);
```
接著會使用`strlen`對於字串長度的檢查長度不能大於0x10否則會直接`exit(0)`
```c=
if (strlen(buf) > 0x10)
{
    puts("input toooooooo long");
    exit(0);
}
```
但是`strlen`只會算到字串到`\0`的長度，所以如果字串是`yes\0aaaaaaaaaaaaaa`則strlen出來的長度只有3而已，因此就可以繞過字串長度的檢查
而本題存在一個`magic`的function能夠開啟shell
```c=
void magic()
{
    system("/bin/sh");
    return;
}
```
如果成功將return address覆蓋成`magic`的起始位置如下圖的情況
![](https://i.imgur.com/vasNAcy.png)

接著如果繼續往後走會segmentation fault，這邊是考點之一需要用gdb去追看他為甚麼會segmentation fault
用gdb往後追之後就能找到他發生segmentation fault的原因如下圖所示
![](https://i.imgur.com/LCCFMu9.png)

可以知道造成segmentation fault的主要原因是因為下面這個指令
```
movaps xmmword ptr [rsp + 0x50], xmm0
```
如果拿去google就能找到很多相關的文章在說明是為甚麼了，主要的原因就是因為stack沒有對齊所以造成在call system的時候會出問題，所以為了要讓stack能夠對齊主要兩個個做法
1. 在覆蓋return address的時候不要跳進magic的開頭讓他不要做function prologue
2. 在跳進magic前先塞一個ret的gadget幫他把stack對齊再跳進magic裡面

[exploit](/pwn/helloctf_revenge/solve.py)

## peko
### 考點
1. shellcode
### exploit
本題主要在考的重點就是自己寫shellcode而不是直接去網路上複製別人寫的shellcode，規定第5 16 27...的位置必須是`\x87`的字元
```c=
for (i = 0; i < 64; i++)
{
    if (i % 11 == 5 && squeak[i] != '\x87')
    {
        puts("wwwwwww");
        exit(0);
    }
}
```
這題有非常多種做法並不限定只有一種shellcode的寫法
這邊的作法是先用寫一個`read(0, buf, 0xff)`的shellcode，而當遇到需要填入`\x87`的位置就用`jmp`指令跳過去
```
\x90\x90\x90\xeb\x02\x87
\x49\x89\xD7                          mov r15, rdx
\x48\x31\xFF                          xor rdi,rdi
\xeb\x03\x90\x90\x87                  jmp
\x49\x83\xC7\x50                      add r15, 0x50
\x4C\x89\xFE                          mov rsi, r15
\xeb\x02\x90\x87                      jmp
\x48\xC7\xC2\xFF\xFF\x00\x00          mov rdx, 0xffff
\xeb\x02\x90\x87                      jmp
\x48\x31\xC0                          xor rax,rax
\x0F\x05                              syscall
\x41\xFF\xE7                          jmp    r15
```
一開始先把要放shellcode的位置存在r15上面所以就構造出`read(0, r15, 0xffff)`的shellcode之後可以進行第二次寫入，寫入`execve("/bin/sh", NULL, NULL)`的shellcode來開shell，然後因為shellcode的位置已經存在r15上就直接`jmp r15`跳進去shellcode就可以了

[exploit](/pwn/peko/solve.py)

## gawr_gura
### 考點
1. ret2libc
2. rop
3. stack migration
### exploit
一開始先觀察全域變數的位置，可以看到`Gawr_gura`存放的起始位置+0x40有stdout
![](https://i.imgur.com/CXJHsxh.png)

而第5個功能可以對`Gawr_grua.note`裡面寫入0x30的大小
```c=
case 5:
    puts("What do you want to say?");
    read(0, Gawr_grua.note, 0x30);
    break;
```
`Gawr_grua.note`在0x407090如果寫入0x30個字會一路從0x407090到0x4070bf都覆蓋掉如下圖
![](https://i.imgur.com/1VZUWOW.png)

這時如果使用第6個功能他會從`Gawr_grua.note`開始用`printf("%s")`把裡面的字串印出來，但是因為`printf("%s")`會一路往下印直到遇到`\x00`為止，所以也會把stdout給印出來，因為stdout是在libc裡面所以可以透過stdout來回推libc的base address
```c=
case 6:
    puts("You say: ");
    printf("%s", Gawr_grua.note);
    break;
```
拿到libc的base之後因為最後面是`read(0, buf, 100)`所以有buffer overflow的漏洞，但是因為這題library裡面的system已經被拔掉的，所以不能直接call `system("/bin/sh")`來拿shell必須透過ROP的方式來做
但是如果要做ROP蓋完return address之後就沒有太多空間可做ROP了，因此必須使用stack migration的技巧來另外找一塊更大的空間疊ROP chain
因為bss段是可寫的所以先把stack搬到bss段上然後讓return address蓋成`read(0, buf, 100)`的位置就能再做一次寫入並且是寫在bss段上，如下圖所示RBP已被搬到bss段上
![](https://i.imgur.com/9JkID0G.png)

由於read會寫到\[rbp-0x50\]的位置所以當RBP已經在bss段上時就能把ROP chain寫在bss段上，在上面疊好ROP chain之後就跳進去就能成功get shell
![](https://i.imgur.com/cegj4ww.png)

[exploit](/pwn/gawr_gura/solve.py)


## holoshell
### 考點
1. time(0)當rand的seed
2. command injection
### exploit
本題第一步在於當使用者連上後會透過`srand(time(0))`來設定rand的seed然後用這個rand來產生一組10個字的密碼
```c=
srand(time(0));
for (int i = 0; i < 10; i++)
{
    passwd[i] = 33 + (rand() % (126 - 32) + 1);
}
```
因為是用連線當下的時間來做rand的seed所以如果在和他連線的同時做一樣的事情就能拿到一樣的seed，因為同樣的seed會讓rand產生相同的隨機數，所以就能夠產生一組相同的密碼了
```c=
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
```
接著透過密碼登錄後會進到第二個部分，這部分會把使用者輸入的內容和本來的字串做串接接著放到system裡面去執行
```c=
read(0, buf, 10);
asprintf(&command, "echo \"%s\" >> HololiveTW.txt", buf);
system(command);
free(command);
```
由於輸入的內容會被放到雙引號之間所以如果輸入123會變成`echo "123" >> HololiveTW.txt`然後丟到system裡面執行，但是因為沒有對輸入的內容作任何檢查所以可以將`"`閉合掉然後用`;`來結束前一個指令接下一個指令，所以如果輸入`";sh;"`最後就會變成`echo "";sh;"" >> HololiveTW.txt`這樣丟進system裡面就會變成一次執行三個指令分別是
1. echo ""
2. sh
3. "" >> HololiveTW.txt

這樣就能成功達成command injection的效果來執行`system("sh")`來把shell開啟

[exploit](/pwn/holoshell/exploit.py)

## holotool
### 考點
1. OOB
2. GOT Hijacking
### exploit
由於變數是存在全域變數中，觀察一下附近有哪些值可以看到如下圖的結果
![](https://i.imgur.com/pnUlJMf.png)

由於在讀取時沒有對輸入做嚴謹的檢查，所以如果輸入負數就可以把got表裡面的東西讀出來，由於got表裡面存放的是function在library中實際的位置，所以只要任意leak出其中一個的值就能推算出libc的base address，而leak出libc的base之後就能透過offset算出system所在的位置
由於在修改時也沒有對輸入作嚴謹的檢查，所以一樣可以輸入負數就能修改got表裡的值來達到got hijacking的效果，這邊因為有一個read_int的function會把輸入的東西丟進去把字串轉數字
```c=
int read_int()
{
    char buf[0x10];
    read(0, buf, 0x10);
    return atoi(buf);
}
```
所以如果把`atoi`的got改成system的位置，這時如果在buf輸入`sh`原本的`atoi("sh")`就會變成`system("sh")`就能成功拿到shell

[exploit](/pwn/holotool/exploit.py)

## debut
### 考點
1. integer overflow
2. canary
3. rop
### exploit
這邊主要的漏洞在於賣東西時只有檢查數量是否大於自己所擁有的數量，但是沒有檢查是否大於0
```c=
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
```
如果輸入的是-1的話stickers會`+1`然後sc會`-1*1000`而sc的type是`unsigned long long`
```c=
unsigned long long sc = 0;
int stickers = 0;
```
所以如果-1之後變成負的會因為type的關係變成最大的正數所以這邊存在integer overflow的漏洞
![](https://i.imgur.com/ogDCTIT.png)

那在拿到很多錢之後就能把商店所有東西都買齊，接著只要開一次直播就有5千萬粉絲就能使用`set_fan_name`的功能
```c=
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
```
由於這邊fans數量已經很大所以除以400000之後會有overflow而且這邊可以無限制的讀取跟寫入，這時可先觀察stack上的東西有canary有libc的位置該有的都有了，所以可以在這邊把所有東西都leak出來
![](https://i.imgur.com/HiZLIaF.png)

當成功leak出canary跟libc base address之後因為overflow的部分可以覆蓋到return address甚至更後面所以直接在這邊疊rop chain就可以get shell

[exploit](/pwn/debut/exploit.py)

## pekopeko
### 考點
1. shellcode
2. seccomp
### exploit
這題內容跟`peko`那題幾乎相同一樣是需要手寫shellcode，但是這題有上了seccomp限制能夠使用的syscall
![](https://i.imgur.com/MGb5dSP.png)

用`seccomp-tools`可以看到限制只能使用x64的syscall並且只有`read, open, exit, exit_group`四個syscall可以使用，所以不能直接使用`execve("/bin/sh")`來開shell
然後因為一開始給的長度只有64而已一定不夠用，所以就跟`peko`那題的做法一樣用`read`去寫入到隨便一個地方再跳進去執行
```=
\x90\x90\x90\xeb\x02\x87
\x49\x89\xD7                          mov r15, rdx
\x48\x31\xFF                          xor rdi,rdi
\xeb\x03\x90\x90\x87                  jmp
\x49\x83\xC7\x50                      add r15, 0x50
\x4C\x89\xFE                          mov rsi, r15
\xeb\x02\x90\x87                      jmp
\x48\xC7\xC2\xFF\xFF\x00\x00          mov rdx, 0xff
\xeb\x02\x90\x87                      jmp
\x48\x31\xC0                          xor rax,rax
\x0F\x05                              syscall
\x41\xFF\xE7                          jmp    r15
```
既然題目有說flag會放在`/home/pekopeko/flag`而且可以使用`open`跟`read`那就使用open來把flag打開
```=
mov rax, 0x67616c
push rax
mov rax, 0x662f6f6b65706f6b
push rax
mov rax, 0x65702f656d6f682f
push rax
mov rdi, rsp
xor rsi, rsi
xor rdx, rdx
mov rax, 2
syscall     /* open */
```
然後用read把她讀出來放在bss段上
```=
mov rdi, rax
mov rsi, 0x406e00
mov rdx, 0x30
xor rax, rax
syscall     /* read */
```
讀出來後沒有`write`可以使用，所以讀完沒辦法直接印在螢幕上，但是可以控制用一個暫存器指向存放flag的bss段，接著把裡面的東西一次1 byte讀出來用`cmp`做比較比較看看是不是相等的，就可以把flag給1 byte 1 byte戳出來
```=
add al, {idx}
mov bl, byte ptr [rax]
cmp bl, {i}
```

[exploit](/pwn/pekopeko/exploit.py)

## maplemiko
author: maple3142
### 考點
1. fmt
### exploit
#### TA version
這題存在format string的漏洞
```c=
printf(str, str);
```
所以如果輸入%p %p %p %p之類的可以把stack後面的東西印出來
![](https://i.imgur.com/iHb515J.png)

而stack上有canary libc等等所需的東西再加上沒有次數限制，所以只要知道它存在第幾個位置就可以用`%x$p`把東西給leak出來
![](https://i.imgur.com/KnspxsZ.png)

因為我們寫入的東西沒有在main的stack上，所以不能直接在stack上寫東西然後直接利用fmt的漏洞對她進行修改，但是可以觀察stack上的東西會發現有個像a->b->c的結構
```
05:0028│     0x7fffffffdd98 —▸ 0x7fffffffde78 —▸ 0x7fffffffe1f6 ◂— '/home/opp556687/Desktop/2021-ctf/maplemiko/distribute/share/maplemiko'
```
然後可以看到他們和存return address那個位置之間的差異只有2byte所以可以嘗試利用fmt改最低的2個byte，可以嘗試透過a把b改成指向return address的位置，如下圖的結果原本的第5個是指向環境變數但改完後她變成指向return address
![](https://i.imgur.com/bEi0XsW.png)
再透過b把return address改成one gadget就能get shell了

![](https://i.imgur.com/UlcshTM.png)

[exploit](/pwn/maplemiko/exploit.py)


#### maple version
因為有fmt的漏洞，所以可以先利用這個漏洞把所有所需用到的東西如canary libc base等等都leak出來
然後觀察一下暫存器上的值可以發現`RSI`會指向剛剛輸入字串的地方，然後根據x64的calling convention前幾個參數會利用`rdi rsi ...`把值存在暫存器上傳給function，而`RSI`是第二個參數所以利用`%1$p`就可以把`RSI`的值印出來，這樣就能夠找到存放輸入的那段stack了

![](https://i.imgur.com/EI0i8gX.png)

接著因為readstr存在buffer overflow的漏洞，但長度只能剛剛好蓋到RBP的位置，所以可以去蓋RBP的位置來做到stack migration
```c=
void *readstr()
{
    char s[512 - 8 * 2];
    memset(s, 0, sizeof(s));
    read(0, s, 520);
    str = s;
}
```
這邊直接把RBP控成readstr的stack位置
![](https://i.imgur.com/Bk9qp3f.png)

這樣再進一次readstr在讀取輸入的時候就會直接寫在剛剛控好的RBP上，就可以在上面寫入ROP chain，最後main離開的時候會踩到`leave ret`就會跳進去剛剛控好的ROP chain的位置就能夠拿到shell
![](https://i.imgur.com/P27eJYh.png)

[exploit](/pwn/maplemiko/maple_exploit.py)

## mapleasm
author: maple3142
### 考點
1. stack migration
2. ROP
3. 了解syscall特性
### exploit
這題存在一個很明顯的buffer overflow的漏洞，可以覆蓋到RBP和return address
```=
mov rdx, 0x50
lea rsi, [rbp-0x40]
mov rdi, 0
mov rax, 0 ; read
syscall
```
既然return address可控就可以任意控制要跳去哪裡，但是因為只能剛好蓋到return address沒有辦法構造出 get shell 的 payload，所以要利用`stack migration`的技巧把stack搬到另一塊地方然後return address再跳一次read這樣就可以在上面構造出要用到的payload，這裡就可以使用ROP來堆出需要的東西
看一下比較好利用的gadget應該只有以下四個
```=
0x000000000040105e : pop rdi ; ret
0x0000000000401062 : pop rdx ; ret
0x0000000000401060 : pop rsi ; ret
0x000000000040100f : syscall
```
但是如果要開shell的話就要使用`execve("/bin/sh", NULL, NULL)`而execve的syscall number是59，但是沒有可以控到rax的gadget可以利用，但是因為`read`這個syscall會回傳成功讀取多少個byte並把結果放在rax上，所以如果在跳進ROP chain之前先用一次`read`去讀59個字這樣rax就會是59，這樣就已經控好rax了接著再進到ROP chain裡面去把其他要用到的參數填好最後就能拿到shell了

[exploit](/pwn/mapleasm/maple_exploit.py)
