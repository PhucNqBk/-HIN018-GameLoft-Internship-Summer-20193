#pragma once
#include <vector> 
#include "GameObject/Sprite2D.h"
#include "Tile.h"
#include "GameObject/Constant.h"
#include "TileLayer.h"



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
	int		FindRoom(int d_row, int d_col);
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

	//std::shared_ptr<Room>m_DungeonRooms[10];
	std::shared_ptr<TileLayer> m_CurrentRoom;
	std::shared_ptr<TileLayer> m_NextRoom;
};