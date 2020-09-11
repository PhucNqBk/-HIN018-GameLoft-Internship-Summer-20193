#pragma once
#include "GameMaps/Tile.h"
#include "Player.h"
class UIContainer
{
public:
	UIContainer();
	UIContainer(std::shared_ptr<Player> player);
	~UIContainer();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

public:
	int m_MaxHeart;
	int m_Score;
	int m_RowCount, m_ColCount;
	std::vector< std::shared_ptr<Tile> > m_Hearts;
	std::shared_ptr<Player> m_Player;
};
