// 윈시프 중간.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "윈시프 중간.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("메모장");

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

	while (GetMessage(&msg, NULL, 0, 0))							 //WinProc()에서 PostQuitMessage() 호출 때까지 처리하는 메시지 루프
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;

	static char linebfr[10][256] = { 0, }; // 문자열 저장
	static int i, row, col, linechase[256], colmax[256]; // 각 줄 추적

	switch (iMsg)
	{
	case WM_CREATE: // 배열 초기화
		row = 0;
		col = 0;
		break;

	case WM_KEYDOWN:
		if (wParam == VK_BACK) { // 백스페이스
			if (col == 0) { // 열에 글자가 없을 떄 윗 열의 마지막 글자로 간다
				linebfr[row][0] = ' ';
				linechase[row] = col;
				colmax[row] = col;
				row--;
				col = linechase[row];
			}
			linebfr[row][col] = ' '; // linebfr[i]를 공란으로 만들고
			col--; // i값을 하나 내린다
			InvalidateRect(hwnd, NULL, FALSE); // WM_PAINT를 발생시키는 함수, 지우고 난 후의 linebfr을 출력해서 보여준다
			break;
		}
		if (wParam == VK_RETURN) {  // 엔터
			linechase[row] = col; //linechase에 현재 행값을 저장하고 다음 열로
			row++;
			col = 0;
		}
		else if (wParam == VK_UP) { //위로
			linechase[row] = col; //linechase에 현재 행값 저장하고 위로
			row--;
			if (linechase[row + 1] <= colmax[row]) { // 윗 행의 끝이 현재 행의 현재 위치보다 클 때
				col = linechase[row + 1]; //현재 행의 위치 그래도 올라가기
			}
			else {
				col = colmax[row]; // 윗 열의 끝으로 이동
			}
		}
		/*하*/
		else if (wParam == VK_DOWN) {
			linechase[row] = col;
			row++;
			if (linechase[row - 1] <= colmax[row]) { // 아래 행의 끝이 현재 행의 현재 위치보다 클 때
				col = linechase[row - 1]; //현재 행의 위치 그래도 올라가기
			}
			else {
				col = colmax[row];// 아래 열의 끝으로 이동
			}
		}
		/*좌*/
		else if (wParam == VK_LEFT) {
			col--;
			linebfr[row][col] = '\0';
		}
		/*우*/
		else if (wParam == VK_RIGHT) {
			linebfr[row][col] = ' ';
			col++;
		}
		else if (col == 255) {
			col = 0;
			row = 0;
		}
		else if (row == 9) {
			row = 0;
			col = 0;
		}
		/*그외 입력 및 출력*/
		else {
			linebfr[row][col++] = wParam;
			linebfr[row][col] = '\0';
			colmax[row] = col; //행의 크기 최신화

			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		break;

		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		for (i = 0; i < 10; i++)
			TextOut(hdc, 100, 100 + 20 * i, linebfr[i], strlen(linebfr[i]));

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}