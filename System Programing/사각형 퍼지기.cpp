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
static int level = -1, Mwider = 20;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT_PTR idevent, DWORD dwTime)
{
		level += 1;
		InvalidateRect(hwnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;

	static char linebfr[256] = { 0, };
	static int x, y, left_button = 0, sideM;

	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam); // 클릭 좌표 저장
		y = HIWORD(lParam);
		level = -1; // M 개수 초기화
		left_button = 1;
		SetTimer(hwnd, 1, 500, TimerProc1); // M 확장 타이머 설정
		break;


	case WM_PAINT:
		sideM = 20; //코너와 중앙 사이에 있는 M의 간격을 위한 변수
		hdc = BeginPaint(hwnd, &ps);
		if (left_button) {
			if (level == 0) {
				TextOut(hdc, x, y, "M", 1);
			}
			else {
				TextOut(hdc, x - (level * Mwider), y - (level * Mwider), "M", 1); //왼쪽 위
				TextOut(hdc, x + (level * Mwider), y - (level * Mwider), "M", 1); //오른쪽 위
				TextOut(hdc, x - (level * Mwider), y + (level * Mwider), "M", 1); //왼쪽 아래
				TextOut(hdc, x + (level * Mwider), y + (level * Mwider), "M", 1); //오른쪽 아래
				TextOut(hdc, x, y - (level * Mwider), "M", 1); //위
				TextOut(hdc, x, y + (level * Mwider), "M", 1); //아래
				TextOut(hdc, x - (level * Mwider), y, "M", 1); //왼
				TextOut(hdc, x + (level * Mwider), y, "M", 1); //오
				for (int _ = 1; _ < level; _++) { //중앙과 모서리 사이의 M 출력
					TextOut(hdc, x - sideM, y - (level * Mwider), "M", 1); //위 왼쪽
					TextOut(hdc, x + sideM, y - (level * Mwider), "M", 1); //위 오른쪽
					TextOut(hdc, x - (level * Mwider), y - sideM, "M", 1); //왼쪽 위
					TextOut(hdc, x - (level * Mwider), y + sideM, "M", 1); //왼쪽 아래
					TextOut(hdc, x + (level * Mwider), y - sideM, "M", 1); //오른쪽 위
					TextOut(hdc, x + (level * Mwider), y + sideM, "M", 1); //오른쪽 아래
					TextOut(hdc, x - sideM, y + (level * Mwider), "M", 1); //아래 왼쪽
					TextOut(hdc, x + sideM, y + (level * Mwider), "M", 1); //아래 오른쪽
					sideM += 20;
				}
			}
		}


		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1); // 타이머 종료
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}
