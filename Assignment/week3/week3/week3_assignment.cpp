#include <iostream>  // ǥ�� ����� ��Ʈ���� ����ϱ� ���� ��� ����
#include <conio.h>   // _getch �Լ��� ����ϱ� ���� ��� ����
#include <chrono>    // �ð� ������ ���� ��� ����
#include <thread>    // �����带 ����ϱ� ���� ��� ����

int main()
{
    const char ESC = 27;     // ESC Ű�� ASCII �� ��� ����
    const char UP = 72;      // ����Ű '��'�� ASCII �� ��� ����
    const char LEFT = 75;    // ����Ű '��'�� ASCII �� ��� ����
    const char RIGHT = 77;   // ����Ű '��'�� ASCII �� ��� ����
    const char DOWN = 80;    // ����Ű '��'�� ASCII �� ��� ����
    const char A = 97;       // 'a' Ű�� ASCII �� ��� ����

    char cmd;               // �Էµ� Ŀ�ǵ带 ������ ����
    char prev_cmd = 0;      // ������ �Էµ� Ŀ�ǵ带 ������ ����
    int state = 0;          // ���¸� ��Ÿ���� ����

    std::cout << "�����׼� Ŀ�ǵ带 �Է��� �ּ���!\n";

    while (1)
    {
        cmd = _getch();  // Ŀ�ǵ� �Է��� ����

        if (cmd == UP)  // �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
        {
            state = 0;  // �ʱ� ���� 0���� ����
            std::cout << "��";  // ȭ�鿡 '��' ���
            if (prev_cmd == DOWN)  // ������ �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
            {
                state = 4;  // ���¸� 4(���Ӽ�Ʈ ű ����� ������ ����)�� ����
            }
            prev_cmd = UP;  // ������ �Էµ� Ŀ�ǵ带 ����Ű '��'�� ����
        }
        else if (cmd == LEFT)  // �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
        {
            state = 0;
            std::cout << "��";  // ȭ�鿡 '��' ���
            prev_cmd = LEFT;  // ������ �Էµ� Ŀ�ǵ带 ����Ű '��'�� ����
        }
        else if (cmd == RIGHT)  // �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
        {
            state = 0;
            std::cout << "��";  // ȭ�鿡 '��' ���
            if (prev_cmd == DOWN)  // ������ �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
            {
                state = 1;  // ���¸� 1(�Ƶ��� ����� ������ ����)�� ����
            }
            else if (prev_cmd == LEFT)  // ������ �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
            {
                state = 3;  // ���¸� 3(�Ҵк� ����� ������ ����)�� ����
            }
            prev_cmd = RIGHT;  // ������ �Էµ� Ŀ�ǵ带 ����Ű '��'�� ����
        }
        else if (cmd == DOWN)  // �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
        {
            state = 0;
            std::cout << "��";  // ȭ�鿡 '��' ���
            if (prev_cmd == RIGHT)  // ������ �Էµ� Ŀ�ǵ尡 ����Ű '��'�� ���
            {
                state = 2;  // ���¸� 2(������ ����� ������ ����)�� ����
            }
            prev_cmd = DOWN;  // ������ �Էµ� Ŀ�ǵ带 ����Ű '��'�� ����
        }
        else if (cmd == A)  // �Էµ� Ŀ�ǵ尡 ����Ű 'a'�� ���
        {
            std::cout << "a";  // ȭ�鿡 'a' ���
            if (state == 1)  // ���°� 1�� ��� ���°� 1(�Ƶ��� ����� ������ ����)�� ���
            {
                std::cout << "\n�Ƶ���! =o\n";  // ȭ�鿡 "�Ƶ���! =o" ���
            }
            else if (state == 2)  // ���°� 2�� ��� ���°� 1(������ ����� ������ ����)�� ���
            {
                std::cout << "\n������!\n";  // ȭ�鿡 "������!" ���
            }
            else if (state == 3)  // ���°� 3�� ��� ���°� 1(�Ҵк� ����� ������ ����)�� ���
            {
                std::cout << "\n�Ҵк�\n";  // ȭ�鿡 "�Ҵк�" ���
            }
            else if (state == 4)  // ���°� 4�� ��� ���°� 1(���Ӽ�Ʈ ű ����� ������ ����)�� ���
            {
                std::cout << "\n���Ӽ�Ʈ ű\n";  // ȭ�鿡 "���Ӽ�Ʈ ű" ���
            }
            state = 0;
            prev_cmd = A;  // ������ �Էµ� Ŀ�ǵ带 ����Ű 'a'�� ����
        }
        else if (cmd == ESC)  // �Էµ� Ŀ�ǵ尡 ����Ű 'ESC'�� ���
        {
            return 0;
        }
        else if (cmd == -32)  // Ư��Ű �Է��� ó���ϱ� ���� �κ�
        {
            continue;  // ���� Ŀ�ǵ带 �Է¹ޱ� ���� �ѱ�
        }
        else
        {
            state = 0;
            std::cout << cmd; // �Էµ� Ŀ�ǵ带 ȭ�鿡 ���
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));  // 0.3��(300ms) �ð� ����
    }

    return 0;
}