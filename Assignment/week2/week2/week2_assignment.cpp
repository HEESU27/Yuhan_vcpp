#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() 
{
    printf("희수의 행복한 VC++");
    Sleep(3000);
    system("cls");

    char cmd;
    char buffer[100];

    while (1)
    {
        int i = 0;
        printf("command>");

        while (1)
        {
            cmd = _getch();

            if (cmd == 27)
            {
                return 0;
            }
            else if (cmd == 13)
            {
                buffer[i] = '\0';
                break;
            }
            else
            {
                buffer[i] = cmd;
                printf("%c", cmd);
                i++;
            }
        }

        if (strcmp(buffer, "q") == 0)
        {
            printf("\nqwer 화이팅\n");
        }
        else if (strcmp(buffer, "w") == 0)
        {
            printf("\n과제 너무 좋다\n");
        }
        else if (strcmp(buffer, "e") == 0)
        {
            printf("\n담주부턴 과제량 3배다\n");
        }
        else if (strcmp(buffer, "r") == 0)
        {
            printf("\n행복합니다.\n");
        }
        else
        {
            printf("\n잘못된 커맨드입니다 (q, w, e, r, 중에 입력해 주세요)\n");
        }
    }

    return 0;
}