#include <iostream>  // 표준 입출력 스트림을 사용하기 위한 헤더 파일
#include <conio.h>   // _getch 함수를 사용하기 위한 헤더 파일
#include <chrono>    // 시간 지연을 위한 헤더 파일
#include <thread>    // 스레드를 사용하기 위한 헤더 파일

int main()
{
    const char ESC = 27;     // ESC 키의 ASCII 값 상수 선언
    const char UP = 72;      // 방향키 '↑'의 ASCII 값 상수 선언
    const char LEFT = 75;    // 방향키 '←'의 ASCII 값 상수 선언
    const char RIGHT = 77;   // 방향키 '→'의 ASCII 값 상수 선언
    const char DOWN = 80;    // 방향키 '↓'의 ASCII 값 상수 선언
    const char A = 97;       // 'a' 키의 ASCII 값 상수 선언

    char cmd;               // 입력된 커맨드를 저장할 변수
    char prev_cmd = 0;      // 이전에 입력된 커맨드를 저장할 변수
    int state = 0;          // 상태를 나타내는 변수

    std::cout << "대전액션 커맨드를 입력해 주세요!\n";

    while (1)
    {
        cmd = _getch();  // 커맨드 입력을 받음

        if (cmd == UP)  // 입력된 커맨드가 방향키 '↑'일 경우
        {
            state = 0;  // 초기 상태 0으로 설정
            std::cout << "↑";  // 화면에 '↑' 출력
            if (prev_cmd == DOWN)  // 이전에 입력된 커맨드가 방향키 '↓'일 경우
            {
                state = 4;  // 상태를 4(서머솔트 킥 기술이 가능한 상태)로 설정
            }
            prev_cmd = UP;  // 이전에 입력된 커맨드를 방향키 '↑'로 설정
        }
        else if (cmd == LEFT)  // 입력된 커맨드가 방향키 '←'일 경우
        {
            state = 0;
            std::cout << "←";  // 화면에 '←' 출력
            prev_cmd = LEFT;  // 이전에 입력된 커맨드를 방향키 '←'로 설정
        }
        else if (cmd == RIGHT)  // 입력된 커맨드가 방향키 '→'일 경우
        {
            state = 0;
            std::cout << "→";  // 화면에 '→' 출력
            if (prev_cmd == DOWN)  // 이전에 입력된 커맨드가 방향키 '↓'일 경우
            {
                state = 1;  // 상태를 1(아도겐 기술이 가능한 상태)로 설정
            }
            else if (prev_cmd == LEFT)  // 이전에 입력된 커맨드가 방향키 '←'일 경우
            {
                state = 3;  // 상태를 3(소닉붐 기술이 가능한 상태)로 설정
            }
            prev_cmd = RIGHT;  // 이전에 입력된 커맨드를 방향키 '→'로 설정
        }
        else if (cmd == DOWN)  // 입력된 커맨드가 방향키 '↓'일 경우
        {
            state = 0;
            std::cout << "↓";  // 화면에 '↓' 출력
            if (prev_cmd == RIGHT)  // 이전에 입력된 커맨드가 방향키 '→'일 경우
            {
                state = 2;  // 상태를 2(오류겐 기술이 가능한 상태)로 설정
            }
            prev_cmd = DOWN;  // 이전에 입력된 커맨드를 방향키 '↓'로 설정
        }
        else if (cmd == A)  // 입력된 커맨드가 방향키 'a'일 경우
        {
            std::cout << "a";  // 화면에 'a' 출력
            if (state == 1)  // 상태가 1인 경우 상태가 1(아도겐 기술이 가능한 상태)인 경우
            {
                std::cout << "\n아도겐! =o\n";  // 화면에 "아도겐! =o" 출력
            }
            else if (state == 2)  // 상태가 2인 경우 상태가 1(오류겐 기술이 가능한 상태)인 경우
            {
                std::cout << "\n오류겐!\n";  // 화면에 "오류겐!" 출력
            }
            else if (state == 3)  // 상태가 3인 경우 상태가 1(소닉붐 기술이 가능한 상태)인 경우
            {
                std::cout << "\n소닉붐\n";  // 화면에 "소닉붐" 출력
            }
            else if (state == 4)  // 상태가 4인 경우 상태가 1(서머솔트 킥 기술이 가능한 상태)인 경우
            {
                std::cout << "\n서머솔트 킥\n";  // 화면에 "서머솔트 킥" 출력
            }
            state = 0;
            prev_cmd = A;  // 이전에 입력된 커맨드를 방향키 'a'로 설정
        }
        else if (cmd == ESC)  // 입력된 커맨드가 방향키 'ESC'일 경우
        {
            return 0;
        }
        else if (cmd == -32)  // 특수키 입력을 처리하기 위한 부분
        {
            continue;  // 다음 커맨드를 입력받기 위해 넘김
        }
        else
        {
            state = 0;
            std::cout << cmd; // 입력된 커맨드를 화면에 출력
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));  // 0.3초(300ms) 시간 지연
    }

    return 0;
}
