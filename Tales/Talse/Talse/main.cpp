// main.cpp
/*
	��ǥ.
	 1. ������� ���� ū �׸� �·� �̵� (�ӵ� : 10)
	 2. ���� ū �׸� ���� ���� �ε����� ������ �ٲ� (�� -> ��)
	 3. ���� ���� �ε����� ������ �ٲ� (�� -> ��)
	 4. �����̽� �� �Է� �� ���� �׸� �̻���ó�� �߻�ȴ�. (���� ��������)
	 5. ���� �׸�� �ڵ����� �����̴� ū �׸� �ε����� �� �� �������.
	 6. ���� �׸�� ȭ���� ����� �ٽ� �߻� �����ϴ�.
	 7. ������ �����̴� ū �׸�� �����ð����� �̻����� �߻��Ѵ�.
	 8. �ؿ��� �����̴� ū �׸�(�÷��̾�)�� ���� �̻����� ������ ȭ�鿡�� �������.
	 9. ���� HP 3���� �־�����.
	 10. �ڵ� �����丵 

	 Q1. ������ ���� �� ȭ���� ���ŵǰ� �ϴ� ��� ( Timer��ü�� ���� �ذ� )
	 Q2. �¿��� ���� �ε������� Ȯ���ϴ� ��� ( üũ�ؾ� �ϴ� ������ �˰� �����Ƿ� �� �� �ִ� )

*/

/*
	�ǽ�1. 210906 ������ �ٿ�ε� �޴´�.
	�ǽ�2. config.h / GameEntity Ŭ���� / MainGame Ŭ������ �����
	��� ������ �����Ѵ�.
	�ǽ�3. main.cpp �� �ִ� �ڵ带 g_mainGame ��ü�� ���� �ű��.
	������ ���� �����ϴ��� Ȯ���Ѵ�.
*/

#include <Windows.h>
#include "CommonFunction.h"
#include "MainGame.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// ��������
POINT		g_ptMouse;
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");
MainGame	g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
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

	return message.wParam;
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
			isUpdate = !isUpdate;
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

		g_mainGame.Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:	// �ݱ� ��ư �޽���ó�� (���α׷� ����)
		PostQuitMessage(0);
		break;
	}

	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
