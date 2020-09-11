#pragma once
#include "Entity.h"
#include "EnemyData.h"
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(std::shared_ptr<EnemyData> eData, int tile_w = TILE_SIZE, int tile_h = TILE_SIZE);
	~Enemy();
	void		CreateEnemyFromData(std::shared_ptr<EnemyData> eData, int tile_w = TILE_SIZE, int tile_h = TILE_SIZE);
	void		Update(GLfloat deltaTime);
	void		ProcessAI();
};