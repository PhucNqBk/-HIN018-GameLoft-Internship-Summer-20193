#include "TileRoom.h"
#include "Sprite2D.h"
TileRoom::TileRoom()
{
	AddDoor(true, false, DoorDirection::DOWN);
	AddDoor(true, false, DoorDirection::RIGHT);
	AddDoor(true, false, DoorDirection::UP);
	AddDoor(true, false, DoorDirection::LEFT);
	coin_wav.load("../Data/Sound/Coin.wav");
	switch_wav.load("../Data/Sound/Secret.wav");
	heart_wav.load("../Data/Sound/GetKey.wav");
	eHit_wav.load("../Data/Sound/HitEnemy.wav");
	pHit_wav.load("../Data/Sound/Hurt.wav");
	//SetPosition(1280 / 2, 720 / 2);
}
TileRoom::~TileRoom()
{

}

void TileRoom::InitRoom(Room room, std::shared_ptr<Sprite2D> rSprite)
{
	//
	CleanUp();
	//clear map
	m_RowCount = room.m_RowCount;
	m_ColCount = room.m_ColCount;
	m_DungRow = room.m_DungRow;
	m_DungCol = room.m_DungCol;
	
	InitializeCollisionMatrix();
	m_TileMap = rSprite;

	m_Doors[DoorDirection::LEFT]->SetIsEnable(room.Door_Left);
	m_Doors[DoorDirection::LEFT]->SetIsOpen(room.isCleared);

	m_Doors[DoorDirection::RIGHT]->SetIsEnable(room.Door_Right);
	m_Doors[DoorDirection::RIGHT]->SetIsOpen(room.isCleared);

	m_Doors[DoorDirection::UP]->SetIsEnable(room.Door_Up);
	m_Doors[DoorDirection::UP]->SetIsOpen(room.isCleared);

	m_Doors[DoorDirection::DOWN]->SetIsEnable(room.Door_Down);
	m_Doors[DoorDirection::DOWN]->SetIsOpen(room.isCleared);
	
	if (room.m_RoomType == 2 && room.isCleared == false)
	{
		if (room.DoorDir == 0)
		{
			m_Doors[DoorDirection::RIGHT]->SetIsOpen(true);
			m_Doors[DoorDirection::UP]->SetIsOpen(true);
			m_Doors[DoorDirection::LEFT]->SetIsOpen(true);
		}
		else if (room.DoorDir == 1)
		{
			m_Doors[DoorDirection::DOWN]->SetIsOpen(true);
			m_Doors[DoorDirection::UP]->SetIsOpen(true);
			m_Doors[DoorDirection::LEFT]->SetIsOpen(true);
		}
		else if (room.DoorDir == 2)
		{
			m_Doors[DoorDirection::RIGHT]->SetIsOpen(true);
			m_Doors[DoorDirection::DOWN]->SetIsOpen(true);
			m_Doors[DoorDirection::LEFT]->SetIsOpen(true);
		}
		else
		{
			m_Doors[DoorDirection::RIGHT]->SetIsOpen(true);
			m_Doors[DoorDirection::UP]->SetIsOpen(true);
			m_Doors[DoorDirection::DOWN]->SetIsOpen(true);
		}
	}
	if (room.m_RoomType == 4 && room.isCleared == false)
	{
		m_Doors[DoorDirection::DOWN]->SetIsOpen(true);
		m_Doors[DoorDirection::RIGHT]->SetIsOpen(true);
		m_Doors[DoorDirection::UP]->SetIsOpen(true);
		m_Doors[DoorDirection::LEFT]->SetIsOpen(true);
		
	}
	GenerateSwitch(room.m_RoomType);
	GeneratePortal(room.m_RoomType);
	SetPosition(m_Position.x, m_Position.y);
	SetPosition(1280 / 2, 720 / 2);
	if (room.m_RoomType != 3)
	{
		GenerateEnemies(m_EnemyDataList);
		GenerateItems();
	}
	
//	std::cout << m_Switch->GetIsActivated() << " " << m_Switch->GetIsEnable()<<" "<<m_Switch->GetPosition().x<<" "<<m_Switch->GetPosition().y << std::endl;
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
	if (m_Switch->GetIsEnable() == true) m_Switch->Draw();
	for (auto it : m_Enemies) {
		if (it->GetIsDead() == false)
			it->Draw();
	}
	for (auto it : m_Items) {
		if (it->GetIsObtain() == false)
			it->Draw();
	}
	
	if (m_Portal->GetIsEnable() == true) m_Portal->Draw();
	if(m_Player->GetIsDead() == false) m_Player->Draw();
	
}
void TileRoom::Update(GLfloat deltatime)
{
	if (m_Player->MapCollision(m_Position.x, m_Position.y, m_ColCount, m_RowCount))
	{
		//std::cout << "Collison" << std::endl;
		m_Player->SetLastX();
		m_Player->SetLastY();
	}
	for (auto it : m_Enemies)
	{
		if (it->MapCollision(m_Position.x, m_Position.y, m_ColCount, m_RowCount))
		{
			//std::cout << "Collison" << std::endl;
			it->SetLastX();
			it->SetLastY();
		}
		Vector2 pos = it->GetPosition();
		if (m_Player->Collision(pos.x, pos.y, it->GetCollider()) && (it->GetIsDead() == false))
		{
			//std::cout << "Collison" << std::endl;
			m_Player->SetLastX();
			m_Player->SetLastY();
			if ((m_Player->GetInvunerable() == false))
			{
				m_Player->Damage(1);

				int c_handle = Application::GetInstance()->soloud.play(pHit_wav);
				Application::GetInstance()->soloud.setPause(c_handle, 1);
				Application::GetInstance()->soloud.setVolume(c_handle, ((float)(Application::GetInstance()->SFX_Volume)) / 10.0f);
				Application::GetInstance()->soloud.setPause(c_handle, 0);

			}
			it->SetLastX();
			it->SetLastY();

		}
		if (m_Player->HitBoxCollision(pos.x, pos.y, it->GetCollider()) && (it->GetIsDead() == false))
		{
			it->Damage(1);

			//Application::GetInstance()->soloud.play(eHit_wav);
			int c_handle = Application::GetInstance()->soloud.play(eHit_wav);
			Application::GetInstance()->soloud.setPause(c_handle, 1);
			Application::GetInstance()->soloud.setVolume(c_handle, ((float)(Application::GetInstance()->SFX_Volume)) / 10.0f);
			Application::GetInstance()->soloud.setPause(c_handle, 0);

			if (it->GetIsDead() == true || it->GetHealth() <= 0)
				m_Player->AddScore(100 + (int)(it->GetWalkSpeed()));
		}
		
	}
	for (auto it : m_Items)
	{
		Vector2 pos = it->GetPosition();
		if (m_Player->Collision(pos.x, pos.y, it->GetCollider()) && (it->GetIsObtain() == false))
		{
			if (it->GetItemType() == POTION)
			{
				m_Player->AddHeart(it->TriggerEffect());
				it->SetIsObtain(true);
				int c_handle = Application::GetInstance()->soloud.play(heart_wav);
				Application::GetInstance()->soloud.setPause(c_handle, 1);
				Application::GetInstance()->soloud.setVolume(c_handle, ((float)(Application::GetInstance()->SFX_Volume)) / 10.0f);
				Application::GetInstance()->soloud.setPause(c_handle, 0);
			}
			else
			{
				m_Player->AddScore(it->TriggerEffect());
				it->SetIsObtain(true);
				int c_handle = Application::GetInstance()->soloud.play(coin_wav);
				Application::GetInstance()->soloud.setPause(c_handle, 1);
				Application::GetInstance()->soloud.setVolume(c_handle, ((float)(Application::GetInstance()->SFX_Volume)) / 10.0f);
				Application::GetInstance()->soloud.setPause(c_handle, 0);
			}

		}
	}
	Vector2 pos = m_Switch->GetPosition();
	if (m_Player->Collision(pos.x, pos.y, m_Switch->GetCollider()) && (m_Switch->GetIsEnable() == true))
	{
		if (m_Player->GetHasKey() == false)
		{
			m_Player->SetHasKey(true);
			m_Switch->SetIsActivated(true);

			int c_handle = Application::GetInstance()->soloud.play(switch_wav);
			Application::GetInstance()->soloud.setPause(c_handle, 1);
			Application::GetInstance()->soloud.setVolume(c_handle, ((float)(Application::GetInstance()->SFX_Volume)) / 10.0f);
			Application::GetInstance()->soloud.setPause(c_handle, 0);
		}
	}
	
	m_Player->Update(deltatime);
	m_Switch->Update(deltatime);
	m_Portal->Update(deltatime);
	for (auto it : m_Enemies)
	{
		it->Update(deltatime);
	}
	for (auto it : m_Items)
	{
		it->Update(deltatime);
	}
}
void TileRoom::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
	m_TileMap->Set2DPosition(x, y);
	m_Doors[DoorDirection::DOWN]->SetPosition(x, y + TILE_SIZE * m_RowCount / 2);
	m_Doors[DoorDirection::RIGHT]->SetPosition(x + TILE_SIZE * m_ColCount / 2, y);
	m_Doors[DoorDirection::UP]->SetPosition(x, y - TILE_SIZE * m_RowCount / 2);
	m_Doors[DoorDirection::LEFT]->SetPosition(x - TILE_SIZE * m_ColCount / 2, y);
	m_Portal->SetPosition(1280 / 2, 720 / 2);
	int sX = -3 + rand() % 6;
		int sY = -3 + rand() % 6;
	int mX = x + ((2 * sX + 1)* TILE_SIZE / 2);
	int mY = y + ((2 * sY + 1)* TILE_SIZE / 2);
	m_Switch->SetPosition(mX, mY);
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

void TileRoom::GenerateEnemies(std::map< std::string, std::shared_ptr<EnemyData>> eDataList)
{
	m_EnemyCount = MIN_ENEMY + rand() % (MAX_ENEMY - MIN_ENEMY);
	m_Enemies.clear();
	std::vector<std::shared_ptr<Enemy> >().swap(m_Enemies);
	for (int i = 0; i < m_EnemyCount; ++i) {
		int x = rand() % 5;
		std::string id;
		if (x == 0)
		{
			id = "slime";
		}
		else if (x == 1)
		{
			id = "bat";
		}
		else if (x == 2)
		{
			id = "ghost";
		}
		else if (x == 3)
		{
			id = "spider";
		}
		else
		{
			id = "skull";
		}
		std::shared_ptr<EnemyData> eData = eDataList[id];
		auto e = std::make_shared<Enemy>(eData);

		e->SetCollider(0, 0, 40, 24);
		e->SetEntity(e);
		e->ChangeState(EntityStateType::IDLE);
		e->SetPlayer(m_Player);
		
		//Set Pos
		int sX = 0 + rand() % 2;
		int sY = 0 + rand() % 2;
		int oX, oY, mX, mY;
		if (i % 4 == 0)
		{
			oX = m_Position.x - TILE_SIZE * m_ColCount / 2 + 2 * 36;
			oY = m_Position.y - TILE_SIZE * m_RowCount / 2 + 2 * 36;

			mX = oX + ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY + ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else if (i % 4 == 1)
		{
			oX = m_Position.x + TILE_SIZE * m_ColCount / 2 - 2 * 36;
			oY = m_Position.y - TILE_SIZE * m_RowCount / 2 + 2 * 36;
			mX = oX - ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY + ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else if(i%4 == 2)
		{
			oX = m_Position.x - TILE_SIZE * m_ColCount / 2 + 2 * 36;
			oY = m_Position.y + TILE_SIZE * m_RowCount / 2 - 2 * 36;
			mX = oX + ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY - ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else
		{
			oX = m_Position.x + TILE_SIZE * m_ColCount / 2 - 2 * 36;
			oY = m_Position.y + TILE_SIZE * m_RowCount / 2 - 2 * 36;
			mX = oX - ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY - ((2 * sY + 1)* TILE_SIZE / 2);
		}
		e->SetPosition(mX, mY);

		e->SetRange(100 + rand()% (250 - 100));
		e->SetWalkSpeed(50 + rand() % (150 - 50));
		m_Enemies.push_back(e);
	}
}
void TileRoom::GenerateItems()
{
	m_ItemCount = MIN_ITEM + rand() % (MAX_ITEM - MIN_ITEM);
	m_Items.clear();
	std::vector<std::shared_ptr<Item>>().swap(m_Items);
	for (int i = 0; i < m_ItemCount; ++i) {
		int x = rand() % 5;
		std::string id;
		std::shared_ptr<Item> itemObj;
		if (x == 1)
		{
			id = "fruit";
			auto iData = m_ItemDataList["fruit"];
			itemObj = std::make_shared<Potion>(iData);
			itemObj->SetCollider(0, 0, 32, 32);
		}
		else
		{
			id = "coin";
			auto iData = m_ItemDataList["coin"];
			itemObj = std::make_shared<Coin>(iData);
			itemObj->SetCollider(0, 0, 32, 32);
		}

		//itemObj->SetCollider(0, 0, 48, 48);	
		//Set Pos
		int sX = 0 + rand() % 5;
		int sY = 0 + rand() % 5;
		int oX, oY, mX, mY;
		if (i % 4 == 0)
		{
			oX = m_Position.x - TILE_SIZE * m_ColCount / 2 + 2 * 36;
			oY = m_Position.y - TILE_SIZE * m_RowCount / 2 + 2 * 36;

			mX = oX + ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY + ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else if (i % 4 == 1)
		{
			oX = m_Position.x + TILE_SIZE * m_ColCount / 2 - 2 * 36;
			oY = m_Position.y - TILE_SIZE * m_RowCount / 2 + 2 * 36;
			mX = oX - ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY + ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else if (i % 4 == 2)
		{
			oX = m_Position.x - TILE_SIZE * m_ColCount / 2 + 2 * 36;
			oY = m_Position.y + TILE_SIZE * m_RowCount / 2 - 2 * 36;
			mX = oX + ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY - ((2 * sY + 1)* TILE_SIZE / 2);
		}
		else
		{
			oX = m_Position.x + TILE_SIZE * m_ColCount / 2 - 2 * 36;
			oY = m_Position.y + TILE_SIZE * m_RowCount / 2 - 2 * 36;
			mX = oX - ((2 * sX + 1)* TILE_SIZE / 2);
			mY = oY - ((2 * sY + 1)* TILE_SIZE / 2);
		}
		itemObj->SetPosition(mX, mY);
		m_Items.push_back(itemObj);
	}
}
void TileRoom::GenerateSwitch(int RoomType)
{
	if (RoomType == 4)
	{
		m_Switch->SetIsEnable(true);
	}
	else {
		m_Switch->SetIsEnable(false);
	}
	if (m_Player->GetHasKey() == true)
	{
		m_Switch->SetIsActivated(true);
	}
	else
	{
		m_Switch->SetIsActivated(false);
	}
}
void TileRoom::GeneratePortal(int RoomType)
{
	if (RoomType == 3)
	{
		m_Portal->SetIsEnable(true);
	}
	else {
		m_Portal->SetIsEnable(false);
	}
	
}
void TileRoom::CreateSwitch(std::shared_ptr<ItemData> iData)
{
	m_Switch = std::make_shared<Switch>(iData, false);
}
void TileRoom::CreatePortal(std::shared_ptr<ItemData> iData)
{
	m_Portal = std::make_shared<Portal>(iData, false);
}
std::shared_ptr<Portal> TileRoom::GetPortal()
{
	return m_Portal;
}
void	TileRoom::SetEnemyCount(int count)
{
	m_EnemyCount = count;
}
int		TileRoom::GetEnemyCount()
{
	return m_EnemyCount;
}
void TileRoom::SetItemCount(int count)
{
	m_ItemCount = count;
}
int	TileRoom::GetItemCount()
{
	return m_ItemCount;
}
void TileRoom::SetEnemyDataList(std::map< std::string, std::shared_ptr<EnemyData>> eDatas)
{
	m_EnemyDataList = eDatas;
}
std::map< std::string, std::shared_ptr<EnemyData>> TileRoom::GetEnemyDataList()
{
	return m_EnemyDataList;
}
void TileRoom::SetItemDataList(std::map<std::string, std::shared_ptr<ItemData> > iDatas)
{
	m_ItemDataList = iDatas;
}
std::map<std::string, std::shared_ptr<ItemData> > TileRoom::GetItemDataList()
{
	return m_ItemDataList;
}
void TileRoom::CleanUp()
{
	m_Enemies.clear();
	std::vector<std::shared_ptr<Enemy> >().swap(m_Enemies);

	m_Items.clear();
	std::vector<std::shared_ptr<Item>>().swap(m_Items);
}