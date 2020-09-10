#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Animation.h"
#include "GameMaps/TileLayer.h"
#include "GameMaps/Dungeon.h"
#include "ObjectDefs.h"
#include "GameMaps/TileRoom.h"
class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_gameName;
	std::shared_ptr<Animation> testAnim;
	std::shared_ptr<TileLayer> testTile;
	std::shared_ptr<Dungeon> testDungeon;
	std::shared_ptr<TileRoom> tRoom;

};

