// 윈시스프로그래밍 3주차 2차시.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "윈시프 테스트용.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("M찍기");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
	LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{																 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	HWND	hwnd;												 //iCmdShow : 윈도우가 화면에 출력될 형태
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass 라는 구조체 정의									 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;			 //출력스타일 : 수직/수평의 변화시 다시 그림
	WndClass.lpfnWndProc = WndProc;							 //프로시저 함수명
	WndClass.cbClsExtra = 0;								 //O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra = 0;								 //O/s 사용 여분 메모리 (Window)
	WndClass.hInstance = hInstance;						 //응용 프로그램 ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	 //아이콘 유형
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		 //커서 유형
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색   
	WndClass.lpszMenuName = NULL;								 //메뉴 이름
	WndClass.lpszClassName = lpszClass;						 //클래스 이름
	RegisterClass(&WndClass);									 //앞서 정의한 윈도우 클래스의 주소

	hwnd = CreateWindow(lpszClass,								 //윈도우가 생성되면 핸들(hwnd)이 반환
		lpszClass,												 //윈도우 클래스, 타이틀 이름
		WS_OVERLAPPEDWINDOW,									 //윈도우 스타일
		100,											 //윈도우 위치, x좌표
		50,											 //윈도우 위치, y좌표
		600,											 //윈도우 폭   
		400,											 //윈도우 높이   
		NULL,													 //부모 윈도우 핸들	 
		NULL,													 //메뉴 핸들
		hInstance,    											 //응용 프로그램 ID
		NULL     												 //생성된 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow);									 //윈도우의 화면 출력
	UpdateWindow(hwnd);											 //O/S 에 WM_PAINT 메시지 전송

	while (GetMessage(&msg, NULL, 0, 0))							 //WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;
//static POINT points[3];
//static int size = 30; // 삼각형의 한 변의 길이

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;

	static char linebfr[256] = { 0, };
	static int m_count, x, y, left_button = 0;

	switch (iMsg)
	{
		//case WM_CREATE:
		//	m_count = 0;
		//	break;

		//case WM_CHAR:
		//	InvalidateRect(hwnd, NULL, FALSE);
		//	break;

	case WM_MOUSEMOVE: // 마우스 이동시 좌표 저장
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		//InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam); // 여기를 안하면 클릭할 때 1픽셀이 안찍힌다 큰 차이는 없음
		y = HIWORD(lParam);
		left_button = TRUE;


		InvalidateRect(hwnd, NULL, TRUE); // TRUE로 바꾸면 전에 그려놨던게 사라짐
		break;

	case WM_LBUTTONUP:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		left_button = FALSE;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//TextOut(hdc, 100, 50, "        ",8 );
		//TextOut(hdc, 100, 50, linebfr,strlen(linebfr) );
		//points[0].x = x;
		//points[0].y = y - size; // 상단 꼭지점
		//points[1].x = x - size;
		//points[1].y = y + size; // 왼쪽 하단 꼭지점
		//points[2].x = x + size;
		//points[2].y = y + size; // 오른쪽 하단 꼭지점

		//// 삼각형 그리기
		//Polygon(hdc, points, 3);
		if (left_button == TRUE) // 좌클릭 하면 좌표에 M 출력
		{
			TextOut(hdc, x - 25, y - 10, "M M M", 5);
			TextOut(hdc, x - 25, y + 10, "M M M", 5);
			TextOut(hdc, x - 25, y - 30, "M M M", 5);
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
