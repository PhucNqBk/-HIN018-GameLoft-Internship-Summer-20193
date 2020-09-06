#include "TileLayer.h"

TileLayer::TileLayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col, int size):
	m_TileSize(size), m_ColCount(col), m_RowCount(row), m_Position(Vector2(0,0))
{
	std::shared_ptr<Tile> tile;
	for (int i = 0; i < m_RowCount; i++)
	{
		std::vector<std::shared_ptr<Tile> > tilesRow;
		for (int j = 0; j < m_ColCount; ++j)
		{
			tile = std::make_shared<Tile>(model, shader, texture);
			tile->SetSize(size, size);
			tilesRow.push_back(tile);
		}
		m_TileMap.push_back(tilesRow);
	}
	SetTileSet(1, 247, 13, 19);
}
TileLayer::TileLayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, Room room, int size):
	m_TileSize(size), m_ColCount(room.m_ColCount), m_RowCount(room.m_RowCount), m_Position(Vector2(0, 0))
{
	SetTileSet(1, 247, 13, 19);
	InitRoom(model, shader, texture, room);
	
}
TileLayer::~TileLayer()
{

}
void TileLayer::ReInitMap(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col)
{
	m_TileMap.clear();
	TileMap().swap(m_TileMap);
	m_RowCount = row;
	m_ColCount = col;
	std::shared_ptr<Tile> tile;
	for (int i = 0; i < m_RowCount; i++)
	{
		std::vector<std::shared_ptr<Tile> > tilesRow;
		for (int j = 0; j < m_ColCount; ++j)
		{
			tile = std::make_shared<Tile>(model, shader, texture);
			tile->SetSize(m_TileSize, m_TileSize);
			tilesRow.push_back(tile);
		}
		m_TileMap.push_back(tilesRow);
	}
	SetPosition(m_Position.x, m_Position.y);
	GenerateTileLayer();
}
void TileLayer::InitRoom(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, Room room)
{
	//clear map
	m_TileMap.clear();
	m_Doors.clear();
	std::vector<std::shared_ptr<Door> >().swap(m_Doors);
	TileMap().swap(m_TileMap);

	m_RowCount = room.m_RowCount;
	m_ColCount = room.m_ColCount;
	m_DungRow =	 room.m_DungRow;
	m_DungCol =  room.m_DungCol;
	std::shared_ptr<Tile> tile;
	for (int i = 0; i < m_RowCount; i++)
	{
		std::vector<std::shared_ptr<Tile> > tilesRow;
		for (int j = 0; j < m_ColCount; ++j)
		{
			tile = std::make_shared<Tile>(model, shader, texture);
			tile->SetSize(m_TileSize, m_TileSize);
			tilesRow.push_back(tile);
		}
		m_TileMap.push_back(tilesRow);
	}
	if (room.isCleared == false)
	{
		if (room.Door_Left)
		{
			AddDoor(false, DoorDirection::LEFT);
		}
		if (room.Door_Right)
		{
			AddDoor(false, DoorDirection::RIGHT);
		}
		if (room.Door_Up)
		{
			AddDoor(false, DoorDirection::UP);

		}
		if (room.Door_Down)
		{
			AddDoor(false, DoorDirection::DOWN);
		}
	}
	else
	{
		if (room.Door_Left)
		{
			AddDoor(true, DoorDirection::LEFT);
		}
		if (room.Door_Right)
		{
			AddDoor(true, DoorDirection::RIGHT);
		}
		if (room.Door_Up)
		{
			AddDoor(true, DoorDirection::UP);

		}
		if (room.Door_Down)
		{
			AddDoor(true, DoorDirection::DOWN);
		}
	}
	GenerateTileLayer();
	SetPosition(m_Position.x, m_Position.y);
	
}
void TileLayer::Init()
{

}
void TileLayer::Draw()
{
	for (int i = 0; i < m_RowCount; ++i) {
		for (int j = 0; j < m_ColCount; ++j)
		{
			m_TileMap[i][j]->Draw(m_Tileset.RowCount, m_Tileset.ColCount);
			Vector2 pos = m_TileMap[i][j]->Get2DPosition();
			//std::cout << pos.x << " " << pos.y << ". ";
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;
}
void TileLayer::Update(GLfloat deltatime)
{

}

int TileLayer::GetTileSize()
{
	return m_TileSize;
}
void	TileLayer::SetTileSize(int size)
{
	m_TileSize = size;
}
TileMap	TileLayer::GetTileMap()
{
	return m_TileMap;
}
void TileLayer::SetTile(int i, int j, int id)
{
	m_TileMap[i][j]->SetTileID(id);

}
void TileLayer::SetTileSet(int fId, int lId, int row, int col)
{
	m_Tileset.FirstID = fId;
	m_Tileset.LastID = lId;
	m_Tileset.RowCount = row;
	m_Tileset.ColCount = col;
}
void TileLayer::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
	float x1, y1;
	for (int i = 0; i < m_RowCount; i++)
		for (int j = 0; j < m_ColCount; ++j)
		{
			x1 = (x - m_ColCount * m_TileSize/2) + (2 * j + 1) * m_TileSize / 2;
			y1 = (y - m_RowCount * m_TileSize/2) + (2 * i + 1) * m_TileSize / 2;
			m_TileMap[i][j]->Set2DPosition(x1, y1);
		}
}
int	TileLayer::GetDungRow()
{
	return m_DungRow;
}
int	TileLayer::GetDungCol()
{
	return m_DungCol;
}
void TileLayer::SetDungRow(int row)
{
	m_DungRow = row;
}
void TileLayer::SetDungCol(int col)
{
	m_DungCol = col;
}
void TileLayer::GenerateTileLayer()
{
	for (int y = 0; y < m_RowCount; ++y)
		for (int x = 0; x < m_ColCount; ++x)
		{
			//4 courner
			if (x == 0 && y == 0)
			{
				SetTile(y, x, TILE_TOP_LEFT_CORNER);
			}
			else if (x == 0 && (y == m_RowCount - 1))
			{
				SetTile(y, x, TILE_BOTTOM_LEFT_CORNER);
			}
			else if ((x == m_ColCount - 1) && y == 0)
			{
				SetTile(y, x, TILE_TOP_RIGHT_CORNER);
			}
			else if ((x == m_ColCount - 1) && (y == m_RowCount - 1))
			{
				SetTile(y, x, TILE_BOTTOM_RIGHT_CORNER);
			}
			//walll
			else if (x == 0)
			{
				SetTile(y, x, TILE_LEFT_WALLS[rand() % TILE_LEFT_WALL_LENGHT]);
			}
			else if (x == m_ColCount -1)
			{
				SetTile(y, x, TILE_RIGHT_WALLS[rand() % TILE_RIGHT_WALL_LENGHT]);
			}
			else if (y == 0)
			{
				SetTile(y, x, TILE_TOP_WALLS[rand() % TILE_TOP_WALL_LENGHT]);
			}
			else if (y == m_RowCount - 1)
			{
				SetTile(y, x, TILE_BOTTOM_WALLS[rand() % TILE_BOTTOM_WALL_LENGHT]);
			}
			//floor
			else
			{
				SetTile(y, x, TILE_FLOORS[rand() % TILE_FLOORS_LENGHT]);
			}
				
		}
	for (int i = 0; i < m_Doors.size(); ++i)
	{
		SetDoorTile(m_Doors[i]->GetIsOpen(), m_Doors[i]->GetDoorDirection());
	}
}
void TileLayer::AddDoor(bool isOpen, DoorDirection dir)
{
	auto tur = std::make_shared<Door>(isOpen, dir);
	m_Doors.push_back(tur);
}
void TileLayer::SetDoorTile(bool isOpen, DoorDirection dir)
{
	
	if (dir == DoorDirection::LEFT)
	{
		if (isOpen)
		{
			SetTile(m_RowCount / 2-1, 0, 182);
			SetTile(m_RowCount / 2, 0, 201);
		}
		else
		{
			SetTile(m_RowCount / 2 -1, 0, 220);
			SetTile(m_RowCount / 2, 0, 239);
		}
	}	
	else if (dir == DoorDirection::RIGHT) 
	{
		if (isOpen)
		{
			SetTile(m_RowCount / 2 -1, m_ColCount -1, 172);
			SetTile(m_RowCount / 2, m_ColCount -1, 191);
		}
		else
		{
			SetTile(m_RowCount / 2 -1, m_ColCount - 1, 174);
			SetTile(m_RowCount / 2, m_ColCount - 1, 193);
		}
	}
		
	else if (dir == DoorDirection::UP)
	{
		if (isOpen)
		{
			SetTile(0, m_ColCount/2 -1, 117);
			SetTile(0, m_ColCount/2, 118);
		}
		else
		{
			SetTile(0, m_ColCount / 2 - 1, 153);
			SetTile(0, m_ColCount / 2, 154);
		}
	}
	else 
	{
		if (isOpen)
		{
			SetTile(m_RowCount -1, m_ColCount/2 -1, 141);
			SetTile(m_RowCount -1, m_ColCount/2, 142);
		}
		else
		{
			SetTile(m_RowCount - 1, m_ColCount / 2 -1, 216);
			SetTile(m_RowCount - 1, m_ColCount / 2, 217);
		}
	}
		
}