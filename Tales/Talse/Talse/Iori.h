#pragma once
#include "GameObject.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Iori : public GameObject	// ��Ӱ���
{
private:
	Image* img;
	int frameX, frameY;
	int elapsedCount;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

