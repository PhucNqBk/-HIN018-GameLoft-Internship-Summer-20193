#pragma once
#include "Enemy.h"
Enemy::Enemy() : Entity(1)
{
	SetCollider(0, 0, 48, 48);
}
Enemy::~Enemy()
{

}

void Enemy::Update(GLfloat deltaTime)
{

}
void Enemy::ProcessAI()
{

}
