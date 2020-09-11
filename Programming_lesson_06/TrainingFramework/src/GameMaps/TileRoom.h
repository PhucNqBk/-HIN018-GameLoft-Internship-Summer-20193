#pragma once
#include <vector>
#include "GameObject/Sprite2D.h"
#include "Tile.h"
#include "GameObject/Constant.h"
#include "Door.h"
#include "Player.h"
#include "Entity.h"
#include "EnemyData.h"
#include "Enemy.h"
#include "Item.h"
#include "Item.h"
#include "Coin.h"
#include "Potion.h"
#include "Portal.h"
#include "Switch.h"
class TileRoom
{
public:
	TileRoom();
	~TileRoom();

	void		InitRoom(Room room, std::shared_ptr<Sprite2D> rSprite);
	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

	std::shared_ptr<Sprite2D>		GetTileMap();
	void		SetPosition(float x, float y);
	Vector2		GetPosition();
	int			GetDungRow();
	int			GetDungCol();
	void		SetDungRow(int row);
	void		SetDungCol(int col);
	int			GetRowCount();
	int			GetColCount();
	void		SetPlayer(std::shared_ptr<Player> player);
	void		SetPlayerPositionWithDoor(DoorDirection dir);
	std::vector<std::shared_ptr<Door> >		GetDoor();

	void		InitializeCollisionMatrix();
	void		GeneratedObject();
	void		AddDoor(bool isEnable, bool isOpen, DoorDirection dir);
	void		GenerateEnemy(std::shared_ptr<EnemyData> eData);
private:
	std::shared_ptr<Sprite2D> m_TileMap;
	std::vector<std::vector<int> > m_CollsionMap;
	std::vector<std::shared_ptr<Door> > m_Doors;
	int m_RowCount, m_ColCount;
	int	m_DungRow, m_DungCol;
	Vector2 m_Position;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Enemy> slime;
	std::vector<std::shared_ptr<Enemy> > m_Enemies;
	std::vector<std::shared_ptr<Switch> > m_Switches;
	std::vector<std::shared_ptr<Item>> m_Items;
};
