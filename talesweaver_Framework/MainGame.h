#pragma once
#include "GameEntity.h"

//class Image;
class MainGame : public GameEntity
{
private:
	HANDLE hTimer;

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	HDC backBuffer;
	HBITMAP hBitmap;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	
	virtual ~MainGame() {};

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};