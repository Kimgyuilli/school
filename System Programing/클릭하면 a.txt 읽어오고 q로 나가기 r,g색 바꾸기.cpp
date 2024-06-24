
// Timer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "윈시프 테스트용.h"
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

HDC hdc;

HANDLE hFile;
int count = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM
    lParam)//IParam은마우스의위치저장, wParam은키보드
{
    static char bfr;
    static char show[256];
    DWORD n = 256, n_out;
    static int flag;
    PAINTSTRUCT ps;
    static COLORREF ColorValue;

    switch (iMsg)
    {
    case WM_CREATE://프로그램시작할때한번만실행되는부분(초기화용)
        hFile = CreateFile("a.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, 0, 0);
        flag = 0;
        break;

    case WM_CHAR:
        if (wParam == 'q')
            PostQuitMessage(0);
        if (wParam == 'r') {
            ColorValue = RGB(255, 0, 0);
        }
        if (wParam == 'g') {
            ColorValue = RGB(0, 255, 0);
        }
        InvalidateRect(hwnd, NULL, TRUE);//화면을다시그려오라는메시지발생
        break;



    case WM_PAINT://화면에그리는부분
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

    //case WM_RBUTTONDOWN:
    //    count = 0;
    //    if (!flag) {
    //        while (ReadFile(hFile, &bfr, 1, &n_out, NULL) && n_out > 0 && count < 255) {
    //            show[count] = bfr;
    //            count++;
    //        }
    //        show[count] = '\0';
    //        flag = 1;
    //        InvalidateRect(hwnd, NULL, TRUE);
        //}
        //break;

    case WM_DESTROY://프로그램끝날때실행되는부분( 주로자원해제, 메모리할당받은거free)
        CloseHandle(hFile);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}