
// Timer.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "������ �׽�Ʈ��.h"
#include <windows.h>
#include "Resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("���� �ĸ��� �Ⱦ�");

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
        600,                                  //������ ��   
        400,                                  //������ ����   
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

HANDLE hFile, hout;
int count = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM
    lParam)//IParam�����콺����ġ����, wParam��Ű����
{
    static char bfr;
    static char show[256];
    DWORD  n_out, n_in;
    static int flag;
    PAINTSTRUCT ps;
    static COLORREF ColorValue;

    switch (iMsg)
    {
    case WM_CREATE://���α׷������Ҷ��ѹ�������Ǵºκ�(�ʱ�ȭ��)
        hFile = CreateFile("a.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, 0);
        flag = 0;
        break;

    case WM_CHAR:
        if (wParam == 'r') {
            ColorValue = RGB(255, 0, 0);
        }
        if (wParam == 'g') {
            ColorValue = RGB(0, 255, 0);
        }
        InvalidateRect(hwnd, NULL, TRUE);//ȭ�����ٽñ׷�����¸޽����߻�
        break;

    case WM_COMMAND:
        switch (wParam)
        {
        case ID_OPEN:
            count = 0;
            if (!flag) {
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                while (ReadFile(hFile, &bfr, 1, &n_out, NULL) && n_out > 0 && count < 255) {
                    show[count] = bfr;
                    count++;
                }
                show[count] = '\0';
                flag = 1;
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;

        case ID_CLOSE:
            PostQuitMessage(0);
            break;

        case ID_COPY:
        {
            hout = CreateFile("copy.txt", GENERIC_WRITE, 0, NULL,
                CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hout != INVALID_HANDLE_VALUE) {
                // ���� ����
                SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
                while (ReadFile(hFile, &bfr, 1, &n_out, NULL) && n_out > 0) {
                    WriteFile(hout, &bfr, 1, &n_in, NULL);
                    if (n_out != n_in) {
                        CloseHandle(hout);
                        return 1;
                    }
                }
                CloseHandle(hout);
            }
            else {
                MessageBox(hwnd, "Failed to create file for copying.", "Error", MB_OK | MB_ICONERROR);
            }
        }
        break;
        }

    case WM_PAINT://ȭ�鿡�׸��ºκ�
        hdc = BeginPaint(hwnd, &ps);
        SetTextColor(hdc, ColorValue);
        if (flag == 1) {
            TextOut(hdc, 100, 100, show, count);
        }
        EndPaint(hwnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        count = 0;
        if (!flag) {
            while (ReadFile(hFile, &bfr, 1, &n_out, NULL) && n_out > 0 && count < 255) {
                show[count] = bfr;
                count++;
            }
            show[count] = '\0';
            flag = 1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY://���α׷�����������Ǵºκ�( �ַ��ڿ�����, �޸��Ҵ������free)
        CloseHandle(hFile);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}