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
#include "Application.h"
#include"soloud.h"
#include "soloud_wav.h"

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
	void		AddDoor(bool isEnable, bool isOpen, DoorDirection dir);
	void		GenerateEnemies(std::map< std::string, std::shared_ptr<EnemyData>> eDataList);
	void		GenerateItems();
	void		GenerateSwitch(int RoomType);
	void		GeneratePortal(int RoomType);
	void		CreateSwitch(std::shared_ptr<ItemData> iData);
	void		CreatePortal(std::shared_ptr<ItemData> iData);
	void		SetEnemyCount(int count);
	int			GetEnemyCount();
	void		SetItemCount(int count);
	int			GetItemCount();

	void		SetEnemyDataList(std::map< std::string, std::shared_ptr<EnemyData>> eDatas);
	std::map< std::string, std::shared_ptr<EnemyData>>		GetEnemyDataList();

	void		SetItemDataList(std::map<std::string, std::shared_ptr<ItemData> > iDatas);
	std::map<std::string, std::shared_ptr<ItemData> >		GetItemDataList();
	void		CleanUp();
	std::shared_ptr<Portal> GetPortal();

private:
	std::shared_ptr<Sprite2D> m_TileMap;
	std::vector<std::vector<int> > m_CollsionMap;
	std::vector<std::shared_ptr<Door> > m_Doors;
	int m_RowCount, m_ColCount;
	int	m_DungRow, m_DungCol;
	Vector2 m_Position;
	std::shared_ptr<Player> m_Player;
	std::vector<std::shared_ptr<Enemy> > m_Enemies;
	std::shared_ptr<Switch> m_Switch;
	std::vector<std::shared_ptr<Item>> m_Items;
	std::shared_ptr<Portal> m_Portal;
	int m_EnemyCount;
	std::map< std::string, std::shared_ptr<EnemyData>> m_EnemyDataList;
	int m_ItemCount;
	std::map<std::string, std::shared_ptr<ItemData> > m_ItemDataList;
	
	SoLoud::Wav coin_wav;
	SoLoud::Wav switch_wav;
	SoLoud::Wav heart_wav;
	SoLoud::Wav eHit_wav;
	SoLoud::Wav pHit_wav;
};
