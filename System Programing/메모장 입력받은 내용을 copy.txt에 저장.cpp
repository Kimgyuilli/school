// ������ �߰�.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "������ �׽�Ʈ��.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("�޸���");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : ������ ���α׷��̶�� �ǹ�
	LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																 //szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	HWND	hwnd;												 //iCmdShow : �����찡 ȭ�鿡 ��µ� ����
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass ��� ����ü ����									 
	WndClass.style = CS_HREDRAW | CS_VREDRAW;			 //��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
	WndClass.lpfnWndProc = WndProc;							 //���ν��� �Լ���
	WndClass.cbClsExtra = 0;								 //O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra = 0;								 //O/s ��� ���� �޸� (Window)
	WndClass.hInstance = hInstance;						 //���� ���α׷� ID
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	 //������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		 //Ŀ�� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����   
	WndClass.lpszMenuName = NULL;								 //�޴� �̸�
	WndClass.lpszClassName = lpszClass;						 //Ŭ���� �̸�
	RegisterClass(&WndClass);									 //�ռ� ������ ������ Ŭ������ �ּ�

	hwnd = CreateWindow(lpszClass,								 //�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
		lpszClass,												 //������ Ŭ����, Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,									 //������ ��Ÿ��
		100,											 //������ ��ġ, x��ǥ
		50,											 //������ ��ġ, y��ǥ
		600,											 //������ ��   
		400,											 //������ ����   
		NULL,													 //�θ� ������ �ڵ�	 
		NULL,													 //�޴� �ڵ�
		hInstance,    											 //���� ���α׷� ID
		NULL     												 //������ ������ ����
	);
	ShowWindow(hwnd, nCmdShow);									 //�������� ȭ�� ���
	UpdateWindow(hwnd);											 //O/S �� WM_PAINT �޽��� ����

	while (GetMessage(&msg, NULL, 0, 0))							 //WinProc()���� PostQuitMessage() ȣ�� ������ ó���ϴ� �޽��� ����
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;
HANDLE hout;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	static char bfr;
	DWORD  n_out;
	static char linebfr[10][256] = { 0, }; // ���ڿ� ����
	static int i, row, col, linechase[256], colmax[256]; // �� �� ����

	switch (iMsg)
	{
	case WM_CREATE: // �迭 �ʱ�ȭ
		row = 0;
		col = 0;
		break;

	case WM_LBUTTONDOWN:
		hout = CreateFile("copy.txt", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hout != INVALID_HANDLE_VALUE) {
			// ���Ͽ� linebfr �ȿ� �ִ� ���ڿ� ����
			for (int i = 0; i < 10; i++) {
				WriteFile(hout, linebfr[i], strlen(linebfr[i]), &n_out, NULL);
				WriteFile(hout, "\r\n", 2, &n_out, NULL); // �� �ٲ� �߰�
			}
			CloseHandle(hout);
		}
		else {
			MessageBox(hwnd, "Failed to create file for copying.", "Error", MB_OK | MB_ICONERROR);
		}
		break;

	case WM_KEYDOWN:
		if (wParam == VK_BACK) { // �齺���̽�
			if (col == 0) { // ���� ���ڰ� ���� �� �� ���� ������ ���ڷ� ����
				linebfr[row][0] = ' ';
				linechase[row] = col;
				colmax[row] = col;
				row--;
				col = linechase[row];
			}
			linebfr[row][col] = ' '; // linebfr[i]�� �������� �����
			col--; // i���� �ϳ� ������
			InvalidateRect(hwnd, NULL, FALSE); // WM_PAINT�� �߻���Ű�� �Լ�, ����� �� ���� linebfr�� ����ؼ� �����ش�
			break;
		}
		if (wParam == VK_RETURN) {  // ����
			linechase[row] = col; //linechase�� ���� �ప�� �����ϰ� ���� ����
			row++;
			col = 0;
		}
		else if (wParam == VK_UP) { //����
			linechase[row] = col; //linechase�� ���� �ప �����ϰ� ����
			row--;
			if (linechase[row + 1] <= colmax[row]) { // �� ���� ���� ���� ���� ���� ��ġ���� Ŭ ��
				col = linechase[row + 1]; //���� ���� ��ġ �׷��� �ö󰡱�
			}
			else {
				col = colmax[row]; // �� ���� ������ �̵�
			}
		}
		/*��*/
		else if (wParam == VK_DOWN) {
			linechase[row] = col;
			row++;
			if (linechase[row - 1] <= colmax[row]) { // �Ʒ� ���� ���� ���� ���� ���� ��ġ���� Ŭ ��
				col = linechase[row - 1]; //���� ���� ��ġ �׷��� �ö󰡱�
			}
			else {
				col = colmax[row];// �Ʒ� ���� ������ �̵�
			}
		}
		/*��*/
		else if (wParam == VK_LEFT) {
			col--;
			linebfr[row][col] = '\0';
		}
		/*��*/
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
		/*�׿� �Է� �� ���*/
		else {
			linebfr[row][col++] = wParam;
			linebfr[row][col] = '\0';
			colmax[row] = col; //���� ũ�� �ֽ�ȭ

			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
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
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}