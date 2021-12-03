#include "header.h"
#include "define.h"
#include "TitleScene.h"
#include "variable_extern.h"

HRESULT TitleScene::Init()
{
	mStartBtn.pos = { 941, 729 };
	mStartBtn.rc.left =		mStartBtn.pos.x - 74;
	mStartBtn.rc.right =	mStartBtn.pos.x + 74;
	mStartBtn.rc.top =		mStartBtn.pos.y - 22;
	mStartBtn.rc.bottom =	mStartBtn.pos.y + 22;

	mQuitBtn.pos = { 64, 729 };
	mQuitBtn.rc.left = mQuitBtn.pos.x - 53;
	mQuitBtn.rc.right = mQuitBtn.pos.x + 53;
	mQuitBtn.rc.top = mQuitBtn.pos.y - 15;
	mQuitBtn.rc.bottom = mQuitBtn.pos.y + 16;

	return S_OK;
}

void TitleScene::Update()
{
}

void TitleScene::Render(HDC hdc)
{
	Graphics G(hdc);

	Image titleImage(L"./Image/Title/Title.png");
	if (titleImage.GetLastStatus() != Ok)
	{
		MessageBox(g_hWnd, "오류다", "오류다", NULL);
	}
	G.DrawImage(&titleImage, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);

	if (PtInRect(&mStartBtn.rc, g_ptMouse))
	{
		Image startImg(L"./Image/Title/Start_btn.png");
		G.DrawImage(&startImg, (INT)mStartBtn.rc.left, (INT)mStartBtn.rc.top, 145, 41);
		if (KEY_MGR->IsStayKeyDown(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}

	if (PtInRect(&mQuitBtn.rc, g_ptMouse))
	{
		Image quitImg(L"./Image/Title/Quit_btn.png");
		G.DrawImage(&quitImg, (INT)mQuitBtn.rc.left, (INT)mQuitBtn.rc.top, 106, 31);
		if (KEY_MGR->IsStayKeyDown(VK_LBUTTON))
		{
			Image quitImg(L"./Image/Title/Quit_btn_click.png");
			G.DrawImage(&quitImg, (INT)mQuitBtn.rc.left, (INT)mQuitBtn.rc.top, 106, 31);
		}
		if (KEY_MGR->IsOnceKeyUp(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}

}

void TitleScene::Release()
{

}

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}
