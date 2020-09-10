#include "TileRoom.h"
#include "Sprite2D.h"
TileRoom::TileRoom()
{
	AddDoor(true, false, DoorDirection::DOWN);
	AddDoor(true, false, DoorDirection::RIGHT);
	AddDoor(true, false, DoorDirection::UP);
	AddDoor(true, false, DoorDirection::LEFT);
	//SetPosition(1280 / 2, 720 / 2);
}
TileRoom::~TileRoom()
{

}

void TileRoom::InitRoom(Room room, std::shared_ptr<Sprite2D> rSprite)
{
	//clear map
	m_RowCount = room.m_RowCount;
	m_ColCount = room.m_ColCount;
	m_DungRow = room.m_DungRow;
	m_DungCol = room.m_DungCol;
	
	InitializeCollisionMatrix();
	m_TileMap = rSprite;

	if (room.isCleared == false)
	{
		if (room.Door_Left)
		{
			m_Doors[DoorDirection::LEFT]->SetIsEnable(true);
			m_Doors[DoorDirection::LEFT]->SetIsOpen(false);
		}
		else
		{
			m_Doors[DoorDirection::LEFT]->SetIsEnable(false);
		}
		if (room.Door_Right)
		{
			m_Doors[DoorDirection::RIGHT]->SetIsEnable(true);
			m_Doors[DoorDirection::RIGHT]->SetIsOpen(false);
		}
		else
		{
			m_Doors[DoorDirection::RIGHT]->SetIsEnable(false);
		}
		if (room.Door_Up)
		{
			m_Doors[DoorDirection::UP]->SetIsEnable(true);
			m_Doors[DoorDirection::UP]->SetIsOpen(false);
		}
		else
		{
			m_Doors[DoorDirection::UP]->SetIsEnable(false);
		}
		if (room.Door_Down)
		{
			m_Doors[DoorDirection::DOWN]->SetIsEnable(true);
			m_Doors[DoorDirection::DOWN]->SetIsOpen(false);
		}
		else
		{
			m_Doors[DoorDirection::DOWN]->SetIsEnable(false);
		}
	}
	else
	{
		if (room.Door_Left)
		{
			m_Doors[DoorDirection::LEFT]->SetIsEnable(true);
			m_Doors[DoorDirection::LEFT]->SetIsOpen(true);
		}
		else
		{
			m_Doors[DoorDirection::LEFT]->SetIsEnable(false);
		}
		if (room.Door_Right)
		{
			m_Doors[DoorDirection::RIGHT]->SetIsEnable(true);
			m_Doors[DoorDirection::RIGHT]->SetIsOpen(true);
		}
		else
		{
			m_Doors[DoorDirection::RIGHT]->SetIsEnable(false);
		}
		if (room.Door_Up)
		{
			m_Doors[DoorDirection::UP]->SetIsEnable(true);
			m_Doors[DoorDirection::UP]->SetIsOpen(true);
		}
		else
		{
			m_Doors[DoorDirection::UP]->SetIsEnable(false);
		}
		if (room.Door_Down)
		{
			m_Doors[DoorDirection::DOWN]->SetIsEnable(true);
			m_Doors[DoorDirection::DOWN]->SetIsOpen(true);
		}
		else
		{
			m_Doors[DoorDirection::DOWN]->SetIsEnable(false);
		}
	}
	

	SetPosition(m_Position.x, m_Position.y);
}
void TileRoom::Init()
{

}
void TileRoom::Draw()
{
	m_TileMap->Draw();
	for (auto it : m_Doors)
	{
		it->Draw();
	}
	m_Player->Draw();
}
void TileRoom::Update(GLfloat deltatime)
{
	if (m_Player->MapCollision(m_Position.x, m_Position.y, m_ColCount, m_RowCount))
	{
		//std::cout << "Collison" << std::endl;
		m_Player->SetLastX();
		m_Player->SetLastY();
	}
	m_Player->Update(deltatime);
}
void TileRoom::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
	m_TileMap->Set2DPosition(x, y);
	m_Doors[DoorDirection::DOWN]->SetPosition(x, y + TILE_SIZE * m_RowCount / 2);
	m_Doors[DoorDirection::RIGHT]->SetPosition(x + TILE_SIZE * m_ColCount / 2, y);
	m_Doors[DoorDirection::UP]->SetPosition(x, y - TILE_SIZE * m_RowCount / 2);
	m_Doors[DoorDirection::LEFT]->SetPosition(x - TILE_SIZE * m_ColCount / 2, y);
}
Vector2	TileRoom::GetPosition()
{
	return m_Position;
}
std::shared_ptr<Sprite2D> TileRoom::GetTileMap()
{
	return m_TileMap;
}

int	TileRoom::GetDungRow()
{
	return m_DungRow;
}
int	TileRoom::GetDungCol()
{
	return m_DungCol;
}
void TileRoom::SetDungRow(int row)
{
	m_DungRow = row;
}
void TileRoom::SetDungCol(int col)
{
	m_DungCol = col;
}
int	TileRoom::GetRowCount()
{
	return m_RowCount;
}
int	TileRoom::GetColCount()
{
	return m_ColCount;
}
std::vector<std::shared_ptr<Door> > TileRoom::GetDoor()
{
	return m_Doors;
}
void TileRoom::InitializeCollisionMatrix()
{
	m_CollsionMap.clear();
	std::vector<std::vector<int> >().swap(m_CollsionMap);
	for (int y = 0; y < m_RowCount; ++y)
	{
		std::vector<int > row;
		for (int x = 0; x < m_ColCount; ++x)
		{
			if (x != 0 && x != m_RowCount - 1 && y != 0 && y != m_ColCount - 1)
			{
				row.push_back(0);
			}
			else {
				row.push_back(1);
			}
			
		}
		m_CollsionMap.push_back(row);
	}
}
void TileRoom::GeneratedObject()
{

}
void TileRoom::AddDoor(bool isEnable, bool isOpen, DoorDirection dir)
{
	auto door = std::make_shared<Door>(isEnable, isOpen, dir);
	m_Doors.push_back(door);
}
void TileRoom::SetPlayer(std::shared_ptr<Player> player)
{
	m_Player = player;
}
void TileRoom::SetPlayerPositionWithDoor(DoorDirection dir)
{
	Vector2 doorPos = m_Doors[dir]->GetPosition();
	if (dir == DoorDirection::DOWN)
	{
		Vector2 doorPos = m_Doors[DoorDirection::UP]->GetPosition();
		m_Player->SetPosition(doorPos.x, doorPos.y + 100);
	}
	else if (dir == DoorDirection::RIGHT)
	{
		Vector2 doorPos = m_Doors[DoorDirection::LEFT]->GetPosition();
		m_Player->SetPosition(doorPos.x + 100, doorPos.y);
	}
	else if (dir == DoorDirection::UP)
	{
		Vector2 doorPos = m_Doors[DoorDirection::DOWN]->GetPosition();
		m_Player->SetPosition(doorPos.x, doorPos.y - 100);
	}
	else
	{
		Vector2 doorPos = m_Doors[DoorDirection::RIGHT]->GetPosition();
		m_Player->SetPosition(doorPos.x - 100, doorPos.y);
	}
}