#include "Dungeon.h"
#include <cmath>
#include "tinyxml/tinyxml.h"
#include "ResourceManagers.h"
Dungeon::Dungeon()
{
	m_IsRunning = true;
	m_DungeonCount = 0;
	ParseSprite("../Data/Asset/maps.mml");
	ParseEnemyData("../Data/Asset/enemies.aml");
	ParseItemData("../Data/Asset/items.aml");
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	std::vector<std::pair<int, int>> endRoom;
	for (int i = 0; i < TakenList.size(); i++)
	{
		Room room;
		int DoorNum = 0;
		int dir = 0;
		room.m_RowCount = 2 * (MAP_MIN_HEIGHT + std::rand() % (MAP_MAX_HEIGHT - MAP_MIN_HEIGHT + 1));
		room.m_ColCount = 2 * (MAP_MIN_WIDTH + std::rand() % (MAP_MAX_WIDTH - MAP_MIN_WIDTH + 1));
		int x = gridSizeX + (int)TakenList[i].x;
		int y = gridSizeY + (int)TakenList[i].y;
		room.m_DungCol = x; room.m_DungRow = y;
		if (x <= DUNGEON_WIDTH - 2)
		{
			if (m_Dungeon[y][x + 1] == 1)
			{
				room.Door_Right = true;
				DoorNum++;
				dir = 1;
			}
				
		}
		if (x - 1 >= 0)
		{
			if (m_Dungeon[y][x - 1] == 1)
			{
				room.Door_Left = true;
				DoorNum++;
				dir = 3;
			}
				
		}
		if (y <= DUNGEON_HEIGHT - 2)
		{
			if (m_Dungeon[y + 1][x] == 1)
			{
				room.Door_Down = true;
				DoorNum++;
				dir = 0;

			}
				
		}
		if (y - 1 >= 0)
		{
			if (m_Dungeon[y - 1][x] == 1)
			{
				room.Door_Up = true;
				DoorNum++;
				dir = 2;
			}
				
		}
		if (DoorNum == 1)
		{
			auto it = std::make_pair(i, dir);
			endRoom.push_back(it);
		}
		room.isCleared = true;
		m_DungeonRooms.push_back(room);
		//std::cout << m_DungeonRooms.size() << std::endl;
	}
	
	// Create endRoom

	int rIndex = rand() % endRoom.size();
	auto it = endRoom[rIndex];
	m_DungeonRooms[it.first].m_RoomType = 3;
	m_DungeonRooms[it.first].DoorDir = it.second;

	//Create pre-end room
	int rI;
	int x = gridSizeX + (int)TakenList[it.first].x;
	int y = gridSizeY + (int)TakenList[it.first].y;
	if (it.second == 0)
	{
		 rI = FindRoom(y+1, x);
		m_DungeonRooms[rI].DoorDir = 2;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else if(it.second == 1)
	{
		rI = FindRoom(y, x+1);
		m_DungeonRooms[rI].DoorDir = 3;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else if(it.second == 2)
	{
		rI = FindRoom(y -1, x);
		m_DungeonRooms[rI].DoorDir = 0;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else
	{
		rI = FindRoom(y, x -1);
		m_DungeonRooms[rI].DoorDir = 1;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	// Make Switch Room
	int sR = rand() % m_DungeonRooms.size();
	while (sR == it.first || sR == rI)
	{
		sR = rand() % m_DungeonRooms.size();
	}
	m_DungeonRooms[sR].m_RoomType = 4;
	m_DungeonRooms[sR].isCleared = false;
	// Make player
	m_Player = std::make_shared<Player>();
	m_Player->CreatAnimation("../Data/Asset/animations.aml");
	m_Player->SetEntity(m_Player);
	m_Player->ChangeState(EntityStateType::IDLE);

	//Make UI;
	m_UI = std::make_shared<UIContainer>(m_Player);

	//make first room
	int jR = rand() % m_DungeonRooms.size();
	while (jR == it.first || jR == rI)
	{
		jR = rand() % m_DungeonRooms.size();
	}
	auto rSpr = FindTileRoom(m_DungeonRooms[jR].m_ColCount, m_DungeonRooms[jR].m_RowCount);
	m_CurrentTileRoom = std::make_shared<TileRoom>();
	m_CurrentTileRoom->SetPlayer(m_Player);
	m_Player->SetHasKey(false);
	m_CurrentTileRoom->CreatePortal(m_ItemDataList["portal"]);
	m_CurrentTileRoom->CreateSwitch(m_ItemDataList["switch"]);
	m_CurrentTileRoom->SetEnemyDataList(m_EnemyDataList);
	m_CurrentTileRoom->SetItemDataList(m_ItemDataList);
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[0]);
	m_CurrentTileRoom->InitRoom(m_DungeonRooms[jR], rSpr);
	//m_CurrentTileRoom->SetPosition(1280 / 2, 720 / 2);
//	m_CurrentTileRoom->InitRoom(m_DungeonRooms[jR], rSpr);
	m_Portal = m_CurrentTileRoom->GetPortal();
	//m_CurrentTileRoom->GenerateEnemies(m_EnemyDataList);
}
Dungeon::Dungeon(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture):
	m_pModel(model), m_pShader(shader), m_pTexture(texture)
{
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	for (int i = 0; i < TakenList.size(); i++)
	{
		Room room;
		room.m_RowCount = 2 * (MAP_MIN_HEIGHT + std::rand() % (MAP_MAX_HEIGHT - MAP_MIN_HEIGHT + 1));
		room.m_ColCount = 2 * (MAP_MIN_WIDTH + std::rand() %  (MAP_MAX_WIDTH - MAP_MIN_WIDTH + 1));
		int x = gridSizeX + (int)TakenList[i].x;
		int y = gridSizeY + (int)TakenList[i].y;
		room.m_DungCol = x; room.m_DungRow = y;
		if (x <= ROOM_WIDTH -2)
		{
			if (m_Dungeon[y][x + 1] == 1)
				room.Door_Right = true;
		}
		if (x - 1 >= 0)
		{
			if (m_Dungeon[y][x - 1] == 1)
				room.Door_Left = true;
		}
		if (y <= ROOM_HEIGHT -2)
		{
			if (m_Dungeon[y + 1][x] == 1)
				room.Door_Down = true;
		}
		if (y - 1 >= 0)
		{
			if (m_Dungeon[y - 1][x] == 1)
			room.Door_Up = true;
		}
		m_DungeonRooms.push_back(room);
		//std::cout << m_DungeonRooms.size() << std::endl;;
	}
	m_CurrentRoom = std::make_shared<TileLayer>(model, shader, texture, 10, 20);
	m_CurrentRoom->InitRoom(m_pModel, m_pShader, m_pTexture, m_DungeonRooms[1]);
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[0]);
	m_CurrentRoom->SetPosition(1280 / 2, 720 / 2);
	
	

}
Dungeon::~Dungeon()
{

}

void Dungeon::Init()
{
	m_DungeonCount++;
	m_DungeonRooms.clear();
	std::vector<Room>().swap(m_DungeonRooms);
	TakenList.clear();
	std::vector<Vector2>().swap(TakenList);
	for (int i = 0; i < DUNGEON_HEIGHT; i++)
	{
		for (int j = 0; j < DUNGEON_WIDTH; j++)
		{
			m_Dungeon[i][j] = 0;
		}
	}
	CreateRooms();
	
	std::vector<std::pair<int, int>> endRoom;
	for (int i = 0; i < TakenList.size(); i++)
	{
		Room room;
		int DoorNum = 0;
		int dir = 0;
		room.m_RowCount = 2 * (MAP_MIN_HEIGHT + std::rand() % (MAP_MAX_HEIGHT - MAP_MIN_HEIGHT + 1));
		room.m_ColCount = 2 * (MAP_MIN_WIDTH + std::rand() % (MAP_MAX_WIDTH - MAP_MIN_WIDTH + 1));
		int x = gridSizeX + (int)TakenList[i].x;
		int y = gridSizeY + (int)TakenList[i].y;
		room.m_DungCol = x; room.m_DungRow = y;
		if (x <= DUNGEON_WIDTH - 2)
		{
			if (m_Dungeon[y][x + 1] == 1)
			{
				room.Door_Right = true;
				DoorNum++;
				dir = 1;
			}

		}
		if (x - 1 >= 0)
		{
			if (m_Dungeon[y][x - 1] == 1)
			{
				room.Door_Left = true;
				DoorNum++;
				dir = 3;
			}

		}
		if (y <= DUNGEON_HEIGHT - 2)
		{
			if (m_Dungeon[y + 1][x] == 1)
			{
				room.Door_Down = true;
				DoorNum++;
				dir = 0;

			}

		}
		if (y - 1 >= 0)
		{
			if (m_Dungeon[y - 1][x] == 1)
			{
				room.Door_Up = true;
				DoorNum++;
				dir = 2;
			}

		}
		if (DoorNum == 1)
		{
			auto it = std::make_pair(i, dir);
			endRoom.push_back(it);
		}
		room.isCleared = true;
		m_DungeonRooms.push_back(room);
		//std::cout << m_DungeonRooms.size() << std::endl;
	}
	
	// Create endRoom

	int rIndex = rand() % endRoom.size();
	auto it = endRoom[rIndex];
	m_DungeonRooms[it.first].m_RoomType = 3;
	m_DungeonRooms[it.first].DoorDir = it.second;

	//Create pre-end room
	int rI;
	int x = gridSizeX + (int)TakenList[it.first].x;
	int y = gridSizeY + (int)TakenList[it.first].y;
	if (it.second == 0)
	{
		rI = FindRoom(y + 1, x);
		m_DungeonRooms[rI].DoorDir = 2;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else if (it.second == 1)
	{
		rI = FindRoom(y, x + 1);
		m_DungeonRooms[rI].DoorDir = 3;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else if (it.second == 2)
	{
		rI = FindRoom(y - 1, x);
		m_DungeonRooms[rI].DoorDir = 0;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	else
	{
		rI = FindRoom(y, x - 1);
		m_DungeonRooms[rI].DoorDir = 1;
		m_DungeonRooms[rI].m_RoomType = 2;
		m_DungeonRooms[rI].isCleared = false;
	}
	//make switch room
	int sR = rand() % m_DungeonRooms.size();
	while (sR == it.first || sR == rI)
	{
		sR = rand() % m_DungeonRooms.size();
	}
	m_DungeonRooms[sR].m_RoomType = 4;
	m_DungeonRooms[sR].isCleared = false;

	//make first room
	int jR = rand() % m_DungeonRooms.size();
	while (jR == it.first || jR == rI)
	{
		jR = rand() % m_DungeonRooms.size();
	}
	auto rSpr = FindTileRoom(m_DungeonRooms[jR].m_ColCount, m_DungeonRooms[jR].m_RowCount);
	m_Player->SetHasKey(false);
	m_CurrentTileRoom->InitRoom(m_DungeonRooms[jR], rSpr);
	m_CurrentTileRoom->SetPosition(1280 / 2, 720 / 2);
}
void Dungeon::Draw()
{
	m_CurrentTileRoom->Draw();
	m_UI->Draw();
}
void Dungeon::Update(GLfloat deltatime)
{
	//m_CurrentRoom->InitRoom(model, shader, texture, m_DungeonRooms[]);
	m_CurrentTileRoom->Update(deltatime);
	std::vector<std::shared_ptr<Door> > Doorway = m_CurrentTileRoom->GetDoor();
	for (auto it : Doorway)
	{
		if (it->GetIsEnable() && it->GetIsOpen()) {
			Vector2 pos = it->GetPosition();
				if (m_Player->Collision(pos.x, pos.y, it->GetCollider()))
				{
					//std::cout << " Collider with :" << it->GetDoorDirection() << std::endl;
					ChangeRoom(it->GetDoorDirection());

				}
		}
		
	}
	Vector2 pos = m_Portal->GetPosition();
	if (m_Player->Collision(pos.x, pos.y, m_Portal->GetCollider()) && m_Portal->GetIsEnable() == true)
	{
		Init();
	}
	if (m_Player->GetIsDead() == true)
	{
		//GameStateMachine::GetInstance()->PopState();
	}
	m_UI->Update(deltatime);
	
}
void Dungeon::HandleKeyEvents(int key, bool bIsPressed)
{
	/*
	int row = m_CurrentTileRoom->GetDungRow();
	int col = m_CurrentTileRoom->GetDungCol();
	std::cout << row << " " << col << std::endl;
	int keyX = -1;
	std::shared_ptr<Sprite2D> sprite;
	if (bIsPressed) {
		switch (key)
		{
		case VK_UP:
			keyX = FindRoom(row - 1, col);
			if (keyX != -1)
			{
				sprite = FindTileRoom(m_DungeonRooms[keyX].m_ColCount, m_DungeonRooms[keyX].m_RowCount);
				m_CurrentTileRoom->InitRoom(m_DungeonRooms[keyX], sprite);
			}
				
			break;
		case VK_DOWN:
			keyX = FindRoom(row +1, col);
			if (keyX != -1)
			{
				sprite = FindTileRoom(m_DungeonRooms[keyX].m_ColCount, m_DungeonRooms[keyX].m_RowCount);
				m_CurrentTileRoom->InitRoom(m_DungeonRooms[keyX], sprite);
			}
			break;
		case VK_LEFT:
		    keyX = FindRoom(row, col -1);
			if (keyX != -1)
			{
				sprite = FindTileRoom(m_DungeonRooms[keyX].m_ColCount, m_DungeonRooms[keyX].m_RowCount);
				m_CurrentTileRoom->InitRoom(m_DungeonRooms[keyX], sprite);
			}
			break;
		case VK_RIGHT:
			keyX = FindRoom(row, col + 1);
			if (keyX != -1)
			{
				sprite = FindTileRoom(m_DungeonRooms[keyX].m_ColCount, m_DungeonRooms[keyX].m_RowCount);
				m_CurrentTileRoom->InitRoom(m_DungeonRooms[keyX], sprite);
			}
			break;
		case 'C':
			Init();
		default:
			break;
		}
	}
	*/
	if (bIsPressed) {
		switch (key)
		{
		case VK_RETURN:
			m_IsRunning = (m_IsRunning == true) ? false : true;
			break;
		case VK_ESCAPE:
			if (m_IsRunning == false)
			{
				GameStateMachine::GetInstance()->PopState();
			}
				break;
		default:
			break;
		}
	}
	m_Player->HandleKeyEvents(key, bIsPressed);
}
void Dungeon::CreateRooms()
{
	gridSizeX = DUNGEON_WIDTH/2;
	gridSizeY = DUNGEON_HEIGHT/2;
	m_Dungeon[gridSizeY][gridSizeX] = 1;
	TakenList.insert(TakenList.begin(),Vector2(0, 0));

	Vector2 checkPos = Vector2(gridSizeX, gridSizeY);

	float randomCompare = 0.2f, randomCompareStart = 0.2f, randomCompareEnd = 0.01f;

	for (int i = 0; i < ROOMS_NUMBER - 1; i++)
	{
		float randomPerc = ((float)i) / (((float)ROOMS_NUMBER-1));
		//lerp (a, b ,t ) = a + t * (b -a)
		randomCompare = randomCompareStart + randomPerc * (randomCompareEnd - randomCompareStart);

		checkPos = NewPosition();
		if (NumberOfNeighbor(checkPos) > 1 && ((float)rand() / (RAND_MAX)) > randomCompare )
		{
			int iterations = 0;
			do
			{
				checkPos = SelectNewPostion();
				iterations++;
			} while (NumberOfNeighbor(checkPos) > 1 && iterations < 100);
			if (iterations >= 50)
			{
				std::cout << "Cannot creat room with fewer neighbors than :  " << NumberOfNeighbor(checkPos) << std::endl;
			}
		}
		m_Dungeon[gridSizeY + (int)checkPos.y][gridSizeX + (int)checkPos.x] = 1;
		TakenList.insert(TakenList.begin(),checkPos);
	}
}
Vector2	Dungeon::NewPosition()
{
	int x = 0, y = 0;
	Vector2 checkingPos = Vector2(0, 0);
	do 
	{
		int index = (int)(((float)rand() / (RAND_MAX)) * (TakenList.size() - 1) + 0.5f);
		x = TakenList[index].x;
		y = TakenList[index].y;
		bool UpDown = (((float)rand() / (RAND_MAX)) < 0.5f);
		bool Positive = (((float)rand() / (RAND_MAX)) < 0.5f);
		if (UpDown)
		{
			if (Positive)
			{
				y += 1;
			}
			else
			{
				y -= 1;
			}

		}else
		{
			if (Positive)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
		}
		checkingPos = Vector2(x, y);
	} while (IsContains(checkingPos) || x >= gridSizeX || x <= -gridSizeX || y >= gridSizeY || y <= -gridSizeY);
	return checkingPos;
}
int	Dungeon::NumberOfNeighbor(Vector2 Pos)
{
	int ret = 0;
	if (IsContains(Vector2(Pos.x+1, Pos.y)))
	{
		ret ++;
	}
	if (IsContains(Vector2(Pos.x -1, Pos.y)))
	{
		ret++;
	}
	if (IsContains(Vector2(Pos.x, Pos.y +1)))
	{
		ret++;
	}
	if (IsContains(Vector2(Pos.x, Pos.y -1)))
	{
		ret++;
	}
	return ret;
}
Vector2	Dungeon::SelectNewPostion()
{
	int index = 0, inc = 0;
	int x = 0, y = 0;
	Vector2 checkingPos = Vector2(0, 0);
	do
	{
		inc = 0;
		do
		{
			index = (int)(((float)rand() / (RAND_MAX)) * (TakenList.size() - 1) + 0.5f);
			inc++;
		} while (NumberOfNeighbor(TakenList[index]) > 1 && inc < 100);
		x = (int)TakenList[index].x;
		y = (int)TakenList[index].y;
		bool UpDown = (((float)rand() / (RAND_MAX)) < 0.5f);
		bool Positive = (((float)rand() / (RAND_MAX)) < 0.5f);
		if (UpDown)
		{
			if (Positive)
			{
				y += 1;
			}
			else
			{
				y -= 1;
			}

		}
		else
		{
			if (Positive)
			{
				x += 1;
			}
			else
			{
				x -= 1;
			}
		}
		checkingPos = Vector2(x, y);
	} while (IsContains(checkingPos) || x >= gridSizeX || x <= -gridSizeX || y >= gridSizeY || y <= -gridSizeY);
	if (inc >= 100)
	{
		std::cout << "Error: Could not find pos with only one neigbor"<<std::endl;
	}
	return checkingPos;
}
bool Dungeon::IsContains(Vector2 pos)
{
	for (int i = 0; i < TakenList.size(); i++)
		if (TakenList[i].x == pos.x &&TakenList[i].y == pos.y)
			return true;
	return false;
}
int Dungeon::FindRoom(int d_row, int d_col)
{
	for (int i = 0; i < m_DungeonRooms.size(); ++i) {
		if (m_DungeonRooms[i].m_DungRow == d_row && m_DungeonRooms[i].m_DungCol == d_col)
			return i;
	}
	return -1;
}

void Dungeon::ParseSprite(std::string filename)
{
	
		std::map<std::pair<int, int>, std::shared_ptr<Sprite2D>> m_Texts;
		TiXmlDocument xml;
		xml.LoadFile(filename);

		if (xml.Error()) {
			std::cerr << "Failed to load: " << filename << std::endl;
			return;
		}
	
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			std::string modelname = e->Attribute("model");
			std::string shadername = e->Attribute("shader");
			for (TiXmlElement* fr = e->FirstChildElement(); fr != nullptr; fr = fr->NextSiblingElement())
			{
				if (fr->Value() == std::string("map"))
				{
					int w, h;
					fr->Attribute("width", &w);
					fr->Attribute("height", &h);

					std::string txtfile = fr->Attribute("texture");

					auto model = ResourceManagers::GetInstance()->GetModel(modelname);
					auto shader = ResourceManagers::GetInstance()->GetShader(shadername);
					auto texture = ResourceManagers::GetInstance()->GetTexture(txtfile, GL_NEAREST);
					
					auto sprite = std::make_shared<Sprite2D>(model, shader, texture);
					sprite->SetSize(TILE_SIZE*w, TILE_SIZE*h);
					std::pair<int, int> pos = std::make_pair(w, h);
					m_Texts[pos] = sprite;
					//std::cout << w << " " << h << " " << txtfile << std::endl;
				}
			}
			
		}
	}
	m_RoomSprites = m_Texts;

}
void Dungeon::ParseEnemyData(std::string filename)
{

	std::map<std::string, std::shared_ptr<EnemyData>> m_EnemyData;
	TiXmlDocument xml;
	xml.LoadFile(filename);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << filename << std::endl;
		return;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			std::string modelname = e->Attribute("model");
			std::string shadername = e->Attribute("shader");
			std::string texturename = e->Attribute("texture");

			int RowCount, ColCount, tile_w, tile_h;
			e->Attribute("RowCount", &RowCount);
			e->Attribute("FrameCount", &ColCount);
			e->Attribute("width", &tile_w);
			e->Attribute("height", &tile_h);

			auto model = ResourceManagers::GetInstance()->GetModel(modelname);
			auto texture = ResourceManagers::GetInstance()->GetTexture(texturename, GL_NEAREST);
			auto shader = ResourceManagers::GetInstance()->GetShader(shadername);

			for (TiXmlElement* fr = e->FirstChildElement(); fr != nullptr; fr = fr->NextSiblingElement())
			{
				if (fr->Value() == std::string("enemy"))
				{
					std::shared_ptr<EnemyData> eData = std::make_shared<EnemyData>(model, shader, texture);
					std::string eId = fr->Attribute("id");
					eData->SetHealth(2);
					std::map<std::string, AnimationData> m_AnimData;
					for (TiXmlElement* er = fr->FirstChildElement(); er != nullptr; er = er->NextSiblingElement())
					{
						if (er->Value() == std::string("frame"))
						{
							std::string animId = er->Attribute("id");
							int isLoop;
							er->Attribute("loop", &isLoop);
							int Count;
							er->Attribute("count", &Count);

							//std::cout << model << " " << shader << " " << texture << " " << id << "" << std::endl;
							auto s = er->GetText();
							std::string val;
							std::istringstream iss(s);
							int tId;
							std::vector<int> tIds;
							for (int i = 0; i < Count; i++)
							{
								std::getline(iss, val, ',');
								std::stringstream conv(val);
								conv >> tId;
								tIds.push_back(tId);
							}
							AnimationData anim;
							anim.m_IDs = tIds;
							anim.m_IsLoop = (isLoop == 1);
							anim.m_ColCount = ColCount;
							anim.m_RowCount = RowCount;
							anim.m_FrameCount = tIds.size();
							anim.m_FrameTime = 0.1f;

							m_AnimData[animId] = anim;
						}
					}
					eData->SetAnimationData(m_AnimData);
					m_EnemyData[eId] = eData;
				}
			}

		}
	}
	m_EnemyDataList = m_EnemyData;

}
void Dungeon::ParseItemData(std::string filename)
{
	std::map<std::string, std::shared_ptr<ItemData>> m_ItemData;
	TiXmlDocument xml;
	xml.LoadFile(filename);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << filename << std::endl;
		return;
	}

	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("sequence"))
		{
			std::string modelname = e->Attribute("model");
			std::string shadername = e->Attribute("shader");
			std::string texturename = e->Attribute("texture");

			int RowCount, ColCount, tile_w, tile_h;
			e->Attribute("RowCount", &RowCount);
			e->Attribute("FrameCount", &ColCount);
			e->Attribute("width", &tile_w);
			e->Attribute("height", &tile_h);

			auto model = ResourceManagers::GetInstance()->GetModel(modelname);
			auto texture = ResourceManagers::GetInstance()->GetTexture(texturename, GL_NEAREST);
			auto shader = ResourceManagers::GetInstance()->GetShader(shadername);

			for (TiXmlElement* fr = e->FirstChildElement(); fr != nullptr; fr = fr->NextSiblingElement())
			{
				if (fr->Value() == std::string("items"))
				{
					std::shared_ptr<ItemData> iData = std::make_shared<ItemData>(model, shader, texture);
					std::string iId = fr->Attribute("type");
					iData->SetDuration(3.0f);
					std::vector<AnimationData> m_AnimData;
					for (TiXmlElement* er = fr->FirstChildElement(); er != nullptr; er = er->NextSiblingElement())
					{
						if (er->Value() == std::string("frame"))
						{
							int animId;
							er->Attribute("id", &animId);
							int isLoop;
							er->Attribute("loop", &isLoop);
							int Count;
							er->Attribute("count", &Count);

							//std::cout << model << " " << shader << " " << texture << " " << id << "" << std::endl;
							auto s = er->GetText();
							std::string val;
							std::istringstream iss(s);
							int tId;
							std::vector<int> tIds;
							for (int i = 0; i < Count; i++)
							{
								std::getline(iss, val, ',');
								std::stringstream conv(val);
								conv >> tId;
								tIds.push_back(tId);
							}
							AnimationData anim;
							anim.m_IDs = tIds;
							anim.m_IsLoop = (isLoop == 1);
							anim.m_ColCount = ColCount;
							anim.m_RowCount = RowCount;
							anim.m_FrameCount = tIds.size();
							anim.m_FrameTime = 0.1f;

							m_AnimData.push_back(anim);
						}
					}
					iData->SetAnimationData(m_AnimData);
					m_ItemData[iId] = iData;
				}
			}

		}
	}
	m_ItemDataList = m_ItemData;
}
std::shared_ptr<Sprite2D> Dungeon::FindTileRoom(int w, int h)
{
	auto val = std::make_pair(w, h);
	return m_RoomSprites[val];
}
void Dungeon::ChangeRoom(DoorDirection dir)
{
	int row = m_CurrentTileRoom->GetDungRow();
	int col = m_CurrentTileRoom->GetDungCol();
	int keyX = -1;

	std::shared_ptr<Sprite2D> sprite;
	if (dir == DoorDirection::DOWN)
	{
		keyX = FindRoom(row + 1, col);
		
	}
	else if (dir == DoorDirection::RIGHT)
	{
		keyX = FindRoom(row, col + 1);
		
	}
	else if (dir == DoorDirection::UP)
	{
		keyX = FindRoom(row - 1, col);
		
	}
	else
	{
		keyX = FindRoom(row, col - 1);
		
	}
	if (keyX != -1)
	{
		if (m_DungeonRooms[keyX].m_RoomType == 2 && m_Player->GetHasKey() == true)
		{
			m_DungeonRooms[keyX].isCleared = true;
		}
		if (m_DungeonRooms[keyX].m_RoomType == 3 && m_Player->GetHasKey() == true)
		{
			m_DungeonRooms[keyX].isCleared = true;
		}
		sprite = FindTileRoom(m_DungeonRooms[keyX].m_ColCount, m_DungeonRooms[keyX].m_RowCount);
		m_CurrentTileRoom->InitRoom(m_DungeonRooms[keyX], sprite);
		m_CurrentTileRoom->SetPlayerPositionWithDoor(dir);
	}
}
void Dungeon::SetDungeonMaxCount(int count)
{
	m_DungeonMaxCount = count;
}
int	Dungeon::GetDungeonMaxCount()
{
	return m_DungeonMaxCount;
}
int	Dungeon::GetDungeonCount()
{
	return m_DungeonCount;
}
std::shared_ptr<Player> Dungeon::GetPlayer()
{
	return m_Player;
}
void Dungeon::SetIsRunning(bool isRun)
{
	m_IsRunning = isRun;
}
bool Dungeon::GetIsRunning()
{
	return m_IsRunning;
}