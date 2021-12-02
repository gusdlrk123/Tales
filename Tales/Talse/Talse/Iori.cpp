#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

HRESULT Iori::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Iori_walk.bmp", 612, 104, 9, 1, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/Iori_walk.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	frameX = frameY = 0;
	elapsedCount = 0;
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10.0f;

	return S_OK;
}

void Iori::Update()
{
	// ������ �����̱�
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			frameX++;
			pos.x += moveSpeed;
			if (frameX >= 9)
			{
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			frameX--;
			pos.x -= moveSpeed;
			if (frameX < 0)
			{
				frameX = 8;
			}
			elapsedCount = 0;
		}
	}

	// �ǽ�1. �ڷ� �����̱� + ���� ��ġ �̵�
	// ����. ���۾� �� �� ���ҽ� ã�ƺ���
	// (���ڸ� ���ֱ�, ������ �̵�, �ڷ� �̵�, ���� ��/��, ū ��/��
	// , �ǰ�(�¾��� ��)

}

void Iori::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, pos.x, pos.y, frameX, frameY);
	}
}

void Iori::Release()
{
}
