// const
#define WIN_START_POS_X		50
#define WIN_START_POS_Y		50
#define WIN_SIZE_X			1024
#define WIN_SIZE_Y			768
#define PI					3.14159265357989

#define TIMER_MGR TimerManager::GetSingleton()
#define KEY_MGR KeyManager::GetSingleton()
#define SCENE_MGR SceneManager::GetSingleton()
#define DELTA_TIME TIME_MGR->GetDeltaTime()

// mecro
#define DEGREE_TO_RADIAN(x)		{ x * PI / 180.0f }
#define SAFE_RELEASE(p)			{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_DELETE(p)			{ if (p) { delete p; p = nullptr; } }

//#define RANDOM(min, max)		{ rand() % ((max) - (min) + 1) + (min) }







