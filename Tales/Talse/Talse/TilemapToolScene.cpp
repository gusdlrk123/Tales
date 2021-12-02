#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

/*
    1. ���̺�, �ε� ��ư �߰�
    2. ���� Ÿ�� ���߼��� �����ϵ���
    3. Ž����(���ϼ���â)�� Ȱ���� ���̺�, �ε� 
*/

HRESULT TilemapToolScene::Init()
{
    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/maptiles.bmp",
        640, 288, 20, 9, true, RGB(255, 0, 255));
    if (sampleImage == nullptr)
    {
        cout << "Image/maptiles.bmp �ε� ����!!" << endl;
        return E_FAIL;
    }

    // ���� ��� ���� ���� �ʱ�ȭ
    for (int i = 0; i < TILE_COUNT_Y; i++)    // y��
    {
        for (int j = 0; j < TILE_COUNT_X; j++)    // x��
        {
            SetRect(&(tileInfo[i * TILE_COUNT_X + j].rc),
                j * TILE_SIZE, i * TILE_SIZE,
                j * TILE_SIZE + TILE_SIZE, i * TILE_SIZE + TILE_SIZE);

            tileInfo[i * TILE_COUNT_X + j].frameX = 3;
            tileInfo[i * TILE_COUNT_X + j].frameY = 0;

            tileInfo[i * TILE_COUNT_X + j].terrain = Terrain::Grass;
        }
    }

    // ������ ��� ���� ���� �ʱ�ȭ
    for (int i = 0; i < SAMPLE_TILE_COUNT_Y; i++)    // y��
    {
        for (int j = 0; j < SAMPLE_TILE_COUNT_X; j++)    // x��
        {
            SetRect(&(sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].rc),
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
                i * TILE_SIZE,
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
                i * TILE_SIZE + TILE_SIZE);

            sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_COUNT_X + j].frameY = i;
        }
    }

    // ���õ� Ÿ��
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;

    return S_OK;
}

void TilemapToolScene::Update()
{
    // ���ÿ������� ������ ����
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - sampleImage->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = sampleImage->GetHeight();

    if (PtInRect(&(sampleArea), g_ptMouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - sampleArea.left;
            int selectedIdX = posX / TILE_SIZE;

            int posY = g_ptMouse.y - sampleArea.top;
            int selectedIdY = posY / TILE_SIZE;

            selectedSampleTile.frameX = 
                sampleTileInfo[selectedIdY * SAMPLE_TILE_COUNT_X + selectedIdX].frameX;
            selectedSampleTile.frameY =
                sampleTileInfo[selectedIdY * SAMPLE_TILE_COUNT_X + selectedIdX].frameY;
        }
    }


    //for (int i = 0; i < SAMPLE_TILE_COUNT_X * SAMPLE_TILE_COUNT_Y; i++)
    //{
    //    if (PtInRect(&(sampleTileInfo[i].rc), g_ptMouse))
    //    {
    //        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    //        {
    //            selectedSampleTile.frameX = sampleTileInfo[i].frameX;
    //            selectedSampleTile.frameY = sampleTileInfo[i].frameY;
    //            break;
    //        }
    //    }
    //}

    // ���ο������� ���õ� ���� ������ ����
    for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; i++)
    {
        if (PtInRect(&(tileInfo[i].rc), g_ptMouse))
        {
            if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
            {
                tileInfo[i].frameX = selectedSampleTile.frameX;
                tileInfo[i].frameY = selectedSampleTile.frameY;
                break;
            }
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
    {
        Save();
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
    {
        Load();
    }
}

void TilemapToolScene::Render(HDC hdc)
{
    // ���� ����
    for (int i = 0; i < TILE_COUNT_Y; i++)
    {
        for (int j = 0; j < TILE_COUNT_X; j++)
        {
            sampleImage->Render(hdc,
                tileInfo[i * TILE_COUNT_X + j].rc.left + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].rc.top + TILE_SIZE / 2,
                tileInfo[i * TILE_COUNT_X + j].frameX,
                tileInfo[i * TILE_COUNT_X + j].frameY);

            //Rectangle(hdc, tileInfo[i * TILE_COUNT_X + j].rc.left,
            //    tileInfo[i * TILE_COUNT_X + j].rc.top,
            //    tileInfo[i * TILE_COUNT_X + j].rc.right,
            //    tileInfo[i * TILE_COUNT_X + j].rc.bottom);
        }
    }

    // ���� ����
    sampleImage->Render(hdc, 
        TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
        sampleImage->GetHeight() / 2);

    //for (int i = 0; i < SAMPLE_TILE_COUNT_X * SAMPLE_TILE_COUNT_Y; i++)
    //{
    //    Rectangle(hdc, sampleTileInfo[i].rc.left,
    //        sampleTileInfo[i].rc.top,
    //        sampleTileInfo[i].rc.right,
    //        sampleTileInfo[i].rc.bottom);
    //}

    // ���õ� Ÿ��
    sampleImage->Render(hdc, TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetFrameWidth() / 2,
        sampleImage->GetHeight() + sampleImage->GetFrameHeight() / 2 + 180,
        selectedSampleTile.frameX, selectedSampleTile.frameY, 2.5f);
}

void TilemapToolScene::Release()
{
}

void TilemapToolScene::Save(int saveIndex)
{
    string saveFileName = "Save/saveMapData_" + to_string(saveIndex);
    saveFileName += ".map";

    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // �б�, ����
        0, NULL,                // ����, ���� ���
        CREATE_ALWAYS,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // ����
    DWORD byteSize = sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y;

    DWORD writtenByte;
    if (WriteFile(hFile,    // ���� �ڵ�
        tileInfo,       // �޸� �����ּ�
        sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,  // �޸� ũ��
        &writtenByte,   // ���� ������ ���� �뷮
        NULL) == false)          // ???
    {
        MessageBox(g_hWnd, "�� ������ ���忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);

    //(parsing)  .ini, .json, html
}

void TilemapToolScene::Load(int loadIndex)
{
    string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
    loadFileName += ".map";

    HANDLE hFile = CreateFile(loadFileName.c_str(),
        GENERIC_READ,           // �б�, ����
        0, NULL,                // ����, ���� ���
        OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
        FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
        NULL);

    // �б�
    DWORD readByte;
    if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT_X * TILE_COUNT_Y,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
    }

    CloseHandle(hFile);
}
