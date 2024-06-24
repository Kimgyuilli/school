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
        100,                                  //������ ��ġ, x��ǥ
        50,                                  //������ ��ġ, y��ǥ
        700,                                  //������ ��   
        600,                                  //������ ����   
        NULL,                                        //�θ� ������ �ڵ�    
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),                                        //�޴� �ڵ�
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

static int x[3] = {30, 80, 130}, y[3] = {130, 80, 30}, indx;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT_PTR idevent, DWORD dwTime)
{
    indx = rand() % 3;
    x[indx] += 100;
    y[indx] += 100;
    InvalidateRect(hwnd, NULL, TRUE);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;

    static int mouseX, mouseY, left_button, clickx, clicky;
    static COLORREF ColorValue;
    static HCURSOR hCursor = LoadCursorFromFile(TEXT("C:\\Users\\rlarb\\OneDrive\\���� ȭ��\\2024 1�б�\\��������ý������α׷���\\4���� �� �ٲٱ�\\�ĸ�ä.cur"));

    switch (iMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, 1, 500, TimerProc1);
        break;


    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        MoveToEx(hdc, 0, 200, NULL);
        LineTo(hdc, 200, 0);
        if (x[indx] + y[indx] >= 1000) {
            KillTimer(hwnd, 1);
            char str[20];
            sprintf_s(str, "%d�� �� ���!!", indx + 1);
            TextOut(hdc, 250, 150, str, strlen(str));
        }
        else {
            TextOut(hdc, x[0], y[0], "H", 1);
            TextOut(hdc, x[1], y[1], "H", 1);
            TextOut(hdc, x[2], y[2], "H", 1);
        }
        MoveToEx(hdc, 700, 300, NULL);
        LineTo(hdc, 300, 700);
        EndPaint(hwnd, &ps);
        break;



    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}
