#include "framework.h"
#include "Windows midEXam.h"
#include <windows.h>
#include "Resource.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("My Windows");

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
        350,                                  //윈도우 위치, x좌표
        300,                                  //윈도우 위치, y좌표
        800,                                  //윈도우 폭   
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
static int x = 300, y = 200;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT_PTR ievent, DWORD dwTime)
{
    x += 10;
    if (x > 700) {
        x = 100;
    }
    InvalidateRect(hwnd, NULL, TRUE);
}
static COLORREF ColorValue;
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;
   

    switch (iMsg)
    {
    case WM_CREATE:
        SetTimer(hwnd, 1, 500, TimerProc1);
        break;

    case WM_COMMAND:
        switch (wParam)
        {
        case ID_SPEED_FAST:
            SetTimer(hwnd, 1, 100, TimerProc1);
            break;
        case ID_SPEED_NORMAL:
            SetTimer(hwnd, 1, 500, TimerProc1);
            break;
        case ID_SPEED_SLOW:
            SetTimer(hwnd, 1, 1000, TimerProc1);
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
        case ID_GAME_START:
            SetTimer(hwnd, 1, 500, TimerProc1);
            break;
        case ID_GAME_PAUSE:
            KillTimer(hwnd, 1);
            break;
        }


	case WM_KEYDOWN:
        switch(wParam){
        case VK_UP: //위로
            y -= 1;
            break;
		/*하*/
        case VK_DOWN:
            y += 1;
            break;

		/*좌*/
        case VK_LEFT:
            x -= 1;
            break;

		/*우*/
        case VK_RIGHT:
            x += 1;
            break;
        }
            InvalidateRect(hwnd, NULL, FALSE);
            break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        SetTextColor(hdc, ColorValue);
        TextOut(hdc, x, y, "M", 1);
        for (int i = 1; i < 5; i++) {
            TextOut(hdc, x - 20 * i, y - 20 * i, "M", 1);
            TextOut(hdc, x + 20 * i, y - 20 * i, "M", 1);
        }
            TextOut(hdc, x - 60, y - 100, "M", 1);
            TextOut(hdc, x + 60, y - 100, "M", 1);
            TextOut(hdc, x - 40, y - 120, "M", 1);
            TextOut(hdc, x + 40, y - 120, "M", 1);
            TextOut(hdc, x - 20, y - 100, "M", 1);
            TextOut(hdc, x + 20, y - 100, "M", 1);
            TextOut(hdc, x, y - 80, "M", 1);
        EndPaint(hwnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}