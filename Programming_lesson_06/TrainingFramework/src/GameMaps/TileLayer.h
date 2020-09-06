#pragma once
#include <vector>
#include "GameObject/Sprite2D.h"
#include "Tile.h"
#include "GameObject/Constant.h"
#include "Door.h"
struct Tileset {
	int FirstID, LastID;
	int RowCount, ColCount;
};

using TileMap = std::vector< std::vector<std::shared_ptr<Tile> > >;

class TileLayer
{
public:
	TileLayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row , int col , int size = TILE_SIZE);
	TileLayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, Room room, int size = TILE_SIZE);
	~TileLayer();

	void		ReInitMap(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col);
	void		InitRoom(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, Room room);
	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);

	int			GetTileSize();
	void		SetTileSize(int size);
	TileMap		GetTileMap();
	void		SetTile(int i, int j, int id);
	void		SetTileSet(int fId, int lId, int row, int col);
	Vector2		GetPosition() { return m_Position; }
	void		SetPosition(float x, float y);
	int			GetDungRow();
	int			GetDungCol();
	void		SetDungRow(int row);
	void		SetDungCol(int col);
	void		GenerateTileLayer();

	void		AddDoor(bool isOpen, DoorDirection dir);
	void		SetDoorTile(bool isOpen, DoorDirection dir);
private:
	int m_TileSize;
	int m_ColCount, m_RowCount;
	TileMap m_TileMap;
	Tileset m_Tileset;
	Vector2 m_Position;
	
	int m_DungRow, m_DungCol;
	std::vector<std::shared_ptr<Door> > m_Doors;
	
};