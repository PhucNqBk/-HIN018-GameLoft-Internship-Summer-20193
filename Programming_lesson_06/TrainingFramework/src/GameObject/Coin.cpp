#include "Coin.h"

Coin::Coin() :Item()
{
	m_ItemType = COIN;
}
Coin::Coin(std::shared_ptr<ItemData> iData) : Item()
{
	m_ItemType = COIN;
	Coin::CreateItemFromData(iData);
}
Coin::~Coin()
{

}
void	Coin::Init()
{

}
void	Coin::Update(GLfloat deltatime)
{

}

int	Coin::TriggerEffect()
{
	return m_Score;
}
void	Coin::CreateItemFromData(std::shared_ptr<ItemData> iData)
{
	m_Duration = iData->GetDuration();
	std::shared_ptr<Models> model = iData->GetModel();
	std::shared_ptr<Shaders> shader = iData->GetShader();
	std::shared_ptr<Texture> texture = iData->GetTexture();
	std::vector<AnimationData> animData = iData->GetAnimationData();
	int index = rand() % animData.size();
	m_Score = (index + 1) * 10;
	AnimationData anim = animData[index];
	m_Animation = std::make_shared<Animation>(model, shader, texture, anim.m_RowCount, anim.m_ColCount, anim.m_FrameTime);
	m_Animation->SetIDs(anim.m_IDs);
	m_Animation->SetIsLoop(anim.m_IsLoop == 1);
	m_Animation->SetSize(TILE_SIZE, TILE_SIZE);
	SetCollider(0, 0, TILE_SIZE, TILE_SIZE);
}