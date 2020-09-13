#pragma once
#include "gamestatebase.h"
#include "GameMaps/TileLayer.h"
#include "GameMaps/Dungeon.h"
#include "ObjectDefs.h"
#include"soloud.h"
#include "soloud_wav.h"
#include "Application.h"
class Sprite2D;
class Player;
class Sprite3D;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_Pause;
	std::shared_ptr<Sprite2D> m_Guide;
	std::shared_ptr<Player> m_Player;
	bool m_Running;
	bool m_GuideEnable;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Dungeon> testDungeon;
	std::shared_ptr<Sprite2D> dung;
	SoLoud::Wav wav;
	int bg_handle;
};

