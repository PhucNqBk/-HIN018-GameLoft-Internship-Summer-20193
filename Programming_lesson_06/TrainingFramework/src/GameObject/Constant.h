#pragma once

#define DUNGEON_WIDTH 6
#define DUNGEON_HEIGHT 6
#define ROOMS_NUMBER 10
#define ROOM_WIDTH 1280
#define ROOM_HEIGHT 720

#define TILE_SIZE 48

const float PLAYER_WALK_SPEED =100;

#define MAP_MAX_WIDTH 10
#define MAP_MAX_HEIGHT 6
#define MAP_MIN_WIDTH 4
#define MAP_MIN_HEIGHT 4

//Tile IDs
#define TILE_TOP_LEFT_CORNER  4
#define TILE_TOP_RIGHT_CORNER  5
#define TILE_BOTTOM_LEFT_CORNER  23
#define TILE_BOTTOM_RIGHT_CORNER  24

#define TILE_EMPTY  19

#define TILE_FLOORS_LENGHT 32
#define TILE_TOP_WALL_LENGHT 3
#define TILE_BOTTOM_WALL_LENGHT 3
#define TILE_LEFT_WALL_LENGHT 3
#define TILE_RIGHT_WALL_LENGHT 3

const int TILE_FLOORS[] = {
	7, 8, 9, 10, 11, 12, 13,
	26, 27, 28, 29, 30, 31, 32,
	45, 46, 47, 48, 49, 50, 51,
	64, 65, 66, 67, 68, 69, 70,
	88, 89, 107, 108
};

const int TILE_TOP_WALLS[] = { 58, 59, 60 };
const int TILE_BOTTOM_WALLS[] = { 79, 80, 81 };
const int TILE_LEFT_WALLS[] = { 77, 96, 115 };
const int TILE_RIGHT_WALLS[] = { 78, 97, 116 };

struct Room {
	int m_RowCount, m_ColCount;
	int m_DungRow, m_DungCol;
	bool Door_Left = false, Door_Right = false, Door_Up = false, Door_Down = false;
	bool isCleared = false;
	int m_RoomType = 1;
};
struct Collider2D {
	float OffsetX;
	float OffsetY;
	float w;
	float h;
};
#define MFORWARD 1
#define MBACKWARD 2
#define MUPWARD 4
#define MDOWNWARD 8
#define P_SWORD 16
#define P_DASH 32

enum Direction {
	DIR_DOWN = 0,
	DIR_RIGHT,
	DIR_UP,
	DIR_LEFT
};

#define DOOR_TILE_ROW 3
#define DOOR_TILE_COL 4
#define DOOR_DOWN 1
#define DOOR_RIGHT 2
#define DOOR_UP 3
#define DOOR_LEFT 4
