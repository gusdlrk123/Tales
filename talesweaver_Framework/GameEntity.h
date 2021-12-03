#pragma once
#include "header.h"
#include "define.h"

class GameEntity
{
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};