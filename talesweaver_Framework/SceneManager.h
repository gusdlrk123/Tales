#pragma once
#include "header.h"
#include "define.h"
#include "Singleton.h"

using namespace std;

enum class eSceneTag
{
	Title,
};

class GameEntity;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<eSceneTag, GameEntity*>	mapScenes;
	map<eSceneTag, GameEntity*>	mapLoadingScenes;

public:
	static GameEntity* currScene;		// 현재 출력 중인 씬
	static GameEntity* readyScene;		// 준비 중인 씬
	static GameEntity* loadingScene;	// 로딩 씬

	void Init(eSceneTag tag, GameEntity* scene);
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddLoadingScene(eSceneTag tag, GameEntity* scene);

	HRESULT ChangeScene(eSceneTag tag);
	HRESULT ChangeScene(eSceneTag tag, eSceneTag loadingSceneName);
};

