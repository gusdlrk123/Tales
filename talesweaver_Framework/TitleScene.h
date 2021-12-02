#pragma once
#include "GameEntity.h"
#include "Config.h"

class TitleScene : public GameEntity
{
private:

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	TitleScene();
	virtual ~TitleScene();

};

