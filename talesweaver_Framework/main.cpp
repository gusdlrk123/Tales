
#include "Config.h"
#include "CommonFunction.h"
#include "MainGame.h"
#include <GdiPlus.h>
#pragma comment(lib,"gdiplus")

using namespace Gdiplus;

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// ��������
POINT		g_ptMouse;
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)L"�������� ����";
MainGame	g_mainGame;
ULONG_PTR	g_gdiPlusToken;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&g_gdiPlusToken, &gpsi, NULL);

	// �����츦 �����ϱ� ���� �⺻ ����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �ڵ�����ȯ
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// �Լ�������(�ݹ��Լ�)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit����

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 
		WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y,
		NULL, NULL, _hInstance, NULL);

	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y,
		WIN_SIZE_X, WIN_SIZE_Y);

	// ���ΰ��� �ʱ�ȭ
	
	g_mainGame.Init();


	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);


	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// ���ΰ��� ����
	g_mainGame.Release();
	GdiplusShutdown(g_gdiPlusToken);
	return message.wParam;
}

void OnPaint(HDC hdc)
{
	Graphics G(hdc);
	Pen p(Color(255, 0, 0, 100), 5);

	G.DrawEllipse(&p, 10, 10, 300, 300);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static bool isUpdate = true;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			//isUpdate = !isUpdate;
			break;
		}
		break;
	case WM_TIMER:
		if (isUpdate)
		{
			g_mainGame.Update();		
		}

		break;
	case WM_PAINT:		// ������ ȭ���� �ٽ� �׷����� ��� �߻��ϴ� �޽���
		hdc = BeginPaint(g_hWnd, &ps);
		
		OnPaint(hdc);

		g_mainGame.Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:	// �ݱ� ��ư �޽���ó�� (���α׷� ����)
		PostQuitMessage(0);
		break;
	}

	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}