#pragma once
#include "Entity.h"
#include "EnemyData.h"
#include "Player.h"
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(std::shared_ptr<EnemyData> eData, int tile_w = TILE_SIZE, int tile_h = TILE_SIZE);
	~Enemy();
	void		CreateEnemyFromData(std::shared_ptr<EnemyData> eData, int tile_w = TILE_SIZE, int tile_h = TILE_SIZE);
	virtual void Update(GLfloat deltaTime) override;
	void		SetPlayer(std::shared_ptr<Player>player);
	void		SetLastX();
	void		SetLastY();
public:
	std::shared_ptr<Player> m_Player;
	Vector2		m_LastSafePos;
};