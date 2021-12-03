#pragma once
#include "GameEntity.h"


class TitleScene : public GameEntity
{
private:
	struct tagBtnInfo
	{
		RECT rc;
		POINT pos;
	};
private:
	tagBtnInfo mStartBtn;
	tagBtnInfo mQuitBtn;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	TitleScene();
	virtual ~TitleScene();

};

