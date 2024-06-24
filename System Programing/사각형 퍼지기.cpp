// ���ý����α׷��� 3���� 2����.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#include "framework.h"
#include "������ �׽�Ʈ��.h"
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
	WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("M���");

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

	while (GetMessage(&msg, NULL, 0, 0))							 //WinProc()���� PostQuitMessage() ȣ�� ������ ó��
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
		x = LOWORD(lParam); // Ŭ�� ��ǥ ����
		y = HIWORD(lParam);
		level = -1; // M ���� �ʱ�ȭ
		left_button = 1;
		SetTimer(hwnd, 1, 500, TimerProc1); // M Ȯ�� Ÿ�̸� ����
		break;


	case WM_PAINT:
		sideM = 20; //�ڳʿ� �߾� ���̿� �ִ� M�� ������ ���� ����
		hdc = BeginPaint(hwnd, &ps);
		if (left_button) {
			if (level == 0) {
				TextOut(hdc, x, y, "M", 1);
			}
			else {
				TextOut(hdc, x - (level * Mwider), y - (level * Mwider), "M", 1); //���� ��
				TextOut(hdc, x + (level * Mwider), y - (level * Mwider), "M", 1); //������ ��
				TextOut(hdc, x - (level * Mwider), y + (level * Mwider), "M", 1); //���� �Ʒ�
				TextOut(hdc, x + (level * Mwider), y + (level * Mwider), "M", 1); //������ �Ʒ�
				TextOut(hdc, x, y - (level * Mwider), "M", 1); //��
				TextOut(hdc, x, y + (level * Mwider), "M", 1); //�Ʒ�
				TextOut(hdc, x - (level * Mwider), y, "M", 1); //��
				TextOut(hdc, x + (level * Mwider), y, "M", 1); //��
				for (int _ = 1; _ < level; _++) { //�߾Ӱ� �𼭸� ������ M ���
					TextOut(hdc, x - sideM, y - (level * Mwider), "M", 1); //�� ����
					TextOut(hdc, x + sideM, y - (level * Mwider), "M", 1); //�� ������
					TextOut(hdc, x - (level * Mwider), y - sideM, "M", 1); //���� ��
					TextOut(hdc, x - (level * Mwider), y + sideM, "M", 1); //���� �Ʒ�
					TextOut(hdc, x + (level * Mwider), y - sideM, "M", 1); //������ ��
					TextOut(hdc, x + (level * Mwider), y + sideM, "M", 1); //������ �Ʒ�
					TextOut(hdc, x - sideM, y + (level * Mwider), "M", 1); //�Ʒ� ����
					TextOut(hdc, x + sideM, y + (level * Mwider), "M", 1); //�Ʒ� ������
					sideM += 20;
				}
			}
		}


		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hwnd, 1); // Ÿ�̸� ����
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}
