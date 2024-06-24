// Timer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "4주차 색 바꾸기.h"
#include "Resource.h"

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("나는 파리가 싫어");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
    LPSTR lpszCmdLine, int nCmdShow)                   //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{                                                 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
    HWND   hwnd;                                     //iCmdShow : 윈도우가 화면에 출력될 형태
    MSG      msg;
    WNDCLASS WndClass;                                  //WndClass 라는 구조체 정의                            
    WndClass.style = CS_HREDRAW | CS_VREDRAW;          //출력스타일 : 수직/수평의 변화시 다시 그림
    WndClass.lpfnWndProc = WndProc;                      //프로시저 함수명
    WndClass.cbClsExtra = 0;                         //O/S 사용 여분 메모리 (Class)
    WndClass.cbWndExtra = 0;                         //O/s 사용 여분 메모리 (Window)
    WndClass.hInstance = hInstance;                   //응용 프로그램 ID
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //아이콘 유형
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);       //커서 유형
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
    WndClass.lpszMenuName = NULL;                         //메뉴 이름
    WndClass.lpszClassName = lpszClass;                   //클래스 이름
    RegisterClass(&WndClass);                            //앞서 정의한 윈도우 클래스의 주소

    hwnd = CreateWindow(lpszClass,                         //윈도우가 생성되면 핸들(hwnd)이 반환
        lpszClass,                                     //윈도우 클래스, 타이틀 이름
        WS_OVERLAPPEDWINDOW,                            //윈도우 스타일
        100,                                  //윈도우 위치, x좌표
        50,                                  //윈도우 위치, y좌표
        600,                                  //윈도우 폭   
        400,                                  //윈도우 높이   
        NULL,                                        //부모 윈도우 핸들    
        LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),                                        //메뉴 핸들
        hInstance,                                      //응용 프로그램 ID
        NULL                                          //생성된 윈도우 정보
    );
    ShowWindow(hwnd, nCmdShow);                            //윈도우의 화면 출력
    UpdateWindow(hwnd);                                  //O/S 에 WM_PAINT 메시지 전송

    while (GetMessage(&msg, NULL, 0, 0))                      //WinProc()에서 PostQuitMessage() 호출 때까지 처리
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);                            //WinMain -> WinProc  
    }
    return (int)msg.wParam;
}

HDC hdc;

static int x, y, score = 0;
static BOOL ShowFly = FALSE, click = TRUE;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT_PTR idevent, DWORD dwTime)
{

    ShowFly = !ShowFly;

    if (ShowFly) {
        x = rand() % 600;
        y = rand() % 400;
        click = TRUE;
    }
    InvalidateRect(hwnd, NULL, TRUE);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;

    static char linebfr[256] = { 0, }, scoreText[20];
    static int mouseX, mouseY, left_button, clickx, clicky;
    static COLORREF ColorValue;
    static HCURSOR hCursor = LoadCursorFromFile(TEXT("C:\\Users\\rlarb\\OneDrive\\바탕 화면\\2024 1학기\\윈도우즈시스템프로그래밍\\과제\\4주차 색 바꾸기\\파리채.cur"));

    switch (iMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, 1, 1000, TimerProc1);
        break;



    case WM_SETCURSOR: //커서 모양 바꾸기
        if (hCursor != NULL) {
            // 커서를 설정.
            SetCursor(hCursor);
        }
        else {
            // 로드 실패 시 기본 커서 사용.
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        return TRUE;

    case WM_MOUSEMOVE: // 마우스 좌표 확인
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_COMMAND:
        switch (wParam)
        {
        case ID_TIMER_START:
            SetTimer(hwnd, 1, 1000, TimerProc1);
            break;
        case ID_TIMER_STOP:
            KillTimer(hwnd, 1);
            break;
        case ID_COLOR_RED:
            ColorValue = RGB(255, 0, 0);
            break;
        case ID_COLOR_GREEN:
            ColorValue = RGB(0, 255, 0);
            break;
        case ID_COLOR_BLUE:
            ColorValue = RGB(0, 0, 255);
            break;
        case ID_COLOR_BLACK:
            ColorValue = RGB(0, 0, 0);
            break;
        case ID_ENDGAME:
            KillTimer(hwnd, 1);
            ShowFly = false;
            score = 0;
            click = TRUE;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }



    case WM_CHAR:
        InvalidateRect(hwnd, NULL, FALSE);
        break;



    case WM_LBUTTONDOWN:
        clickx = LOWORD(lParam);
        clicky = HIWORD(lParam);
        left_button = TRUE;
        if (clickx < x + 15 && clickx > x - 15 and clicky < y + 15 && clicky > y - 15 and click and ShowFly) {
            score += 1;
            click = FALSE;
            InvalidateRect(hwnd, NULL, FALSE);
        }
        break;

    case WM_RBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        left_button = FALSE;

        InvalidateRect(hwnd, NULL, FALSE);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        wsprintf(scoreText, "Score: %d", score);
        SetTextColor(hdc, ColorValue);
        if (ShowFly) { // 일정시간마다 H 출현
            TextOut(hdc, x, y, "H", 1);
        }
        if (!click) { // 클릭 성공하면 텍스트 출력
            TextOut(hdc, x - 10, y, "잡았다!", 7);
        }
        TextOut(hdc, 500, 10, scoreText, lstrlen(scoreText));
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
