#pragma once
#include "Enemy.h"
Enemy::Enemy() : Entity(1)
{
	SetCollider(0, 0, 48, 48);
}
Enemy::Enemy(std::shared_ptr<EnemyData> eData, int tile_w, int tile_h) : Entity(1)
{
	CreateEnemyFromData(eData, tile_w, tile_h);
}
Enemy::~Enemy()
{

}
void Enemy::CreateEnemyFromData(std::shared_ptr<EnemyData> eData, int tile_w, int tile_h)
{
	SetHealth(eData->GetHealth());
	std::shared_ptr<Models> model = eData->GetModel();
	std::shared_ptr<Shaders> shader = eData->GetShader();
	std::shared_ptr<Texture> texture = eData->GetTexture();
	std::map<std::string, AnimationData> animData = eData->GetAnimationDatas();
	for (auto it : animData)
	{
		std::string id = it.first;
		AnimationData anim = it.second;
		std::shared_ptr<Animation> eAnim = std::make_shared<Animation>(model, shader, texture, anim.m_RowCount, anim.m_ColCount, anim.m_FrameTime);
		eAnim->SetIDs(anim.m_IDs);
		eAnim->SetIsLoop(anim.m_IsLoop == 1);
		eAnim->SetSize(tile_w, tile_h);
		m_Animations[id] = eAnim;
	}
	SetCollider(0, 0, tile_w, tile_h);
	m_CurrentAnimation = m_Animations["idle-0"];
}
void Enemy::Update(GLfloat deltaTime)
{
	//std::cout << m_Health << std::endl;
}
void Enemy::ProcessAI()
{

}
