#pragma once
#include <vector> 
#include "GameObject/Sprite2D.h"
#include "Tile.h"
#include "GameObject/Constant.h"
#include "TileLayer.h"
#include <map>
#include <utility>
#include "GameMaps/TileRoom.h"
#include "Player.h"
class Dungeon
{
public:

	Dungeon();
	Dungeon(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Dungeon();

	void		Init();
	void		Draw();
	void		Update(GLfloat deltatime);
	void		HandleKeyEvents(int key, bool bIsPressed);
	void		SetRoomsPosition(float x, float y);

	void		CreateRooms();
	Vector2		NewPosition();
	int			NumberOfNeighbor(Vector2 Pos);
	Vector2		SelectNewPostion();
	bool		IsContains(Vector2 pos);
	int			FindRoom(int d_row, int d_col);
	std::shared_ptr<Sprite2D> FindTileRoom(int w, int h);
	void		ParseSprite(std::string filename);
	void		ParseAnimation(std::string filename);
	void		ChangeRoom(DoorDirection dir);
protected:
	std::shared_ptr<Models>		m_pModel;
	std::shared_ptr<Shaders>	m_pShader;
//	std::shared_ptr<Camera>		m_pCamera;
	std::shared_ptr<Texture>	m_pTexture;
private:
	int m_Dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH];
	std::vector<Room>m_DungeonRooms;
	std::vector<Vector2> TakenList;
	int gridSizeX, gridSizeY;

	std::map< std::pair<int, int>, std::shared_ptr<Sprite2D> > m_RoomSprites;
	//std::shared_ptr<Room>m_DungeonRooms[10];
	std::shared_ptr<TileLayer> m_CurrentRoom;
	std::shared_ptr<TileLayer> m_NextRoom;
	std::shared_ptr<TileRoom> m_CurrentTileRoom;
	std::shared_ptr<TileRoom> m_NexttileRoom;
	std::shared_ptr<Player> m_Player;
	std::map< std::string, std::shared_ptr<Animation> > m_EnemyAnimations;
};