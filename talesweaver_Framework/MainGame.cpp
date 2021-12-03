#include "header.h"
#include "define.h"
#include "MainGame.h"
#include "TitleScene.h"
#include "variable_extern.h"

HRESULT MainGame::Init()
{
	KEY_MGR->Init();
	TIMER_MGR->Init();
	SCENE_MGR->Init(eSceneTag::Title, new TitleScene());

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	mousePosX = 0;
	mousePosY = 0;
	clickedMousePosX = 0; 
	clickedMousePosY = 0;
	
	HDC hdc = GetDC(g_hWnd); 
	backBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, WIN_SIZE_X, WIN_SIZE_Y);
	SelectObject(backBuffer, hBitmap);
	ReleaseDC(g_hWnd, hdc);

	SceneManager::GetSingleton()->ChangeScene(eSceneTag::Title);

	return S_OK;
}

void MainGame::Update()
{
	TIMER_MGR->Update();

	SCENE_MGR->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	// Clear
	PatBlt(backBuffer, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, WHITENESS);

	// Draw next frame
	SCENE_MGR->Render(backBuffer);

	TIMER_MGR->Render(backBuffer);

	// Copy next frame to hdc
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, backBuffer, 0, 0, SRCCOPY);
}

void MainGame::Release()
{
	//SAFE_RELEASE(backBuffer);
	/*
	IMG_MGR->Release();
	IMG_MGR->ReleaseSingleton();
	*/
	ReleaseDC(g_hWnd, backBuffer);
	DeleteObject(hBitmap);

	TIMER_MGR->Release();
	TIMER_MGR->ReleaseSingleton();

	KEY_MGR->Release();
	KEY_MGR->ReleaseSingleton();

	SCENE_MGR->Release();
	SCENE_MGR->ReleaseSingleton();

	KillTimer(g_hWnd, 0);

}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		clickedMousePosX = LOWORD(lParam);
		clickedMousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
