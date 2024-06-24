// Timer.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "������ �׽�Ʈ��.h"
#include <windows.h>
#include <string>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("���޸���");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : ������ ���α׷��̶�� �ǹ�
    LPSTR lpszCmdLine, int nCmdShow)                   //hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{                                                 //szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
    HWND   hwnd;                                     //iCmdShow : �����찡 ȭ�鿡 ��µ� ����
    MSG      msg;
    WNDCLASS WndClass;                                  //WndClass ��� ����ü ����                            
    WndClass.style = CS_HREDRAW | CS_VREDRAW;          //��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
    WndClass.lpfnWndProc = WndProc;                      //���ν��� �Լ���
    WndClass.cbClsExtra = 0;                         //O/S ��� ���� �޸� (Class)
    WndClass.cbWndExtra = 0;                         //O/s ��� ���� �޸� (Window)
    WndClass.hInstance = hInstance;                   //���� ���α׷� ID
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //������ ����
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);       //Ŀ�� ����
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����   
    WndClass.lpszMenuName = NULL;                         //�޴� �̸�
    WndClass.lpszClassName = lpszClass;                   //Ŭ���� �̸�
    RegisterClass(&WndClass);                            //�ռ� ������ ������ Ŭ������ �ּ�

    hwnd = CreateWindow(lpszClass,                         //�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
        lpszClass,                                     //������ Ŭ����, Ÿ��Ʋ �̸�
        WS_OVERLAPPEDWINDOW,                            //������ ��Ÿ��
        100,                                   //������ ��ġ, x��ǥ
        50,                                  //������ ��ġ, y��ǥ
        600,                                  //������ ��   
        400,                                  //������ ����   
        NULL,                                        //�θ� ������ �ڵ�    
        NULL,                                        //�޴� �ڵ�
        hInstance,                                      //���� ���α׷� ID
        NULL                                          //������ ������ ����
    );
    ShowWindow(hwnd, nCmdShow);                            //�������� ȭ�� ���
    UpdateWindow(hwnd);                                  //O/S �� WM_PAINT �޽��� ����

    while (GetMessage(&msg, NULL, 0, 0))                      //WinProc()���� PostQuitMessage() ȣ�� ������ ó��
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);                            //WinMain -> WinProc  
    }
    return (int)msg.wParam;
}

HDC hdc;

static int x[5], indx;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT_PTR idevent, DWORD dwTime)
{
    indx = rand() % 5;
    x[indx] += 100;
    InvalidateRect(hwnd, NULL, TRUE);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;

    static int mouseX, mouseY, left_button, clickx, clicky, speed = 500;
    static COLORREF ColorValue;
    static HCURSOR hCursor = LoadCursorFromFile(TEXT("C:\\Users\\rlarb\\OneDrive\\���� ȭ��\\2024 1�б�\\��������ý������α׷���\\4���� �� �ٲٱ�\\�ĸ�ä.cur"));

    switch (iMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, 1, 500, TimerProc1);
        break;

    case WM_LBUTTONDOWN:
        speed -= 100;
        SetTimer(hwnd, 1, speed, TimerProc1);

    case WM_RBUTTONDOWN:
        speed += 100;
        SetTimer(hwnd, 1, speed, TimerProc1);

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        if (x[indx] >= 600) {
            KillTimer(hwnd, 1);
            char str[20];
            sprintf_s(str, "%d�� �� ���", indx + 1);
            TextOut(hdc, 250, 150, str, strlen(str));
        }
        else {
            TextOut(hdc, x[0], 50, "H", 1);
            TextOut(hdc, x[1], 100, "H", 1);
            TextOut(hdc, x[2], 150, "H", 1);
            TextOut(hdc, x[3], 200, "H", 1);
            TextOut(hdc, x[4], 250, "H", 1);
        }
        EndPaint(hwnd, &ps);
        break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}
