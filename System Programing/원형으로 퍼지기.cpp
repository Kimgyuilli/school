// Wave_M.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "윈시프 테스트용.h"
#include "cmath"

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
    WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("New Title Hong Gil Dong");

HDC hdc;
const int TIMER_ID = 1;

int radius = 10; // 반지름
int m_count = 20; // M 문자의 개수
const double PI = 3.14159265358979323846; // PI 값
static int wide = 5; // 이전에 그린 M과 새로 그린 M과의 거리

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
        NULL,                                        //메뉴 핸들
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
BOOL left_button = true;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

    PAINTSTRUCT ps;

    static int m_count, x, y, round_x, round_y, timeset = 10;



    switch (iMsg)
    {



    case WM_LBUTTONDOWN:
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        timeset = 0;
        m_count = 10;
        wide = 2;
        InvalidateRect(hwnd, NULL, false); //클릭하면 새로운 곳에 원 만들기
        SetTimer(hwnd, TIMER_ID, 500, NULL); // 100ms마다 타이머 트리거
        break;

    case WM_RBUTTONDOWN:
        KillTimer(hwnd, TIMER_ID); // 타이머 제거
        break;
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        if (timeset < 1) {
            TextOut(hdc, x, y, "M", 1);
        }
        else {
            for (int i = 0; i < m_count; ++i) {
                // 각도 계산
                double angle = 2 * PI * i / m_count; // i가 0부터 증가하면서 각도를 증가 시킴
                // 중심에서부터 반지름 만큼 떨어진 위치 계산
                round_x = x + static_cast<int>((radius + wide) * cos(angle)); // 각도 angle이면서, 
                round_y = y + static_cast<int>((radius + wide) * sin(angle));
                // M 문자 그리기
                TextOut(hdc, round_x, round_y, "M", 1);
            }
        }
        timeset += 1;
        EndPaint(hwnd, &ps);
        break;

    case WM_TIMER:
        wide = wide + 20;
        // 화면 갱신 요청
        InvalidateRect(hwnd, NULL, TRUE); //원이 커지면서 이전의 원을 없앨지
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}