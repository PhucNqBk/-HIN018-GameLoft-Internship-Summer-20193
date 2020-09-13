#pragma once
#include "GameMaps/Tile.h"
#include "Player.h"
#include "Text.h"
class UIContainer
{
public:
	UIContainer();
	UIContainer(std::shared_ptr<Player> player);
	~UIContainer();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);
	void		DrawResult();

	std::shared_ptr<Text> GetDungeonText();
	std::shared_ptr<Text> GetResulDungeonText();
public:
	int m_MaxHeart;
	int m_RowCount, m_ColCount;
	std::vector< std::shared_ptr<Tile> > m_Hearts;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Text>  m_Score;
	std::shared_ptr<Text>  m_Dungeon;

	std::shared_ptr<Text>  m_ResultScore;
	std::shared_ptr<Text>  m_ResultDungeon;
};
