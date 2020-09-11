#include "Switch.h"

Switch::Switch() :Item()
{
	m_ItemType = PORTAL;
	m_IsActivated = false;
}
Switch::Switch(std::shared_ptr<ItemData> iData, bool isRight)
{
	m_ItemType = PORTAL;
	m_IsActivated = false;
	
	Switch::CreateItemFromData(iData);
}
Switch::~Switch()
{

}
void Switch::Init()
{

}
void Switch::Update(GLfloat deltatime)
{

}

void Switch::TriggerEffect()
{

}
void Switch::CreateItemFromData(std::shared_ptr<ItemData> iData)
{
	m_Duration = iData->GetDuration();
	std::shared_ptr<Models> model = iData->GetModel();
	std::shared_ptr<Shaders> shader = iData->GetShader();
	std::shared_ptr<Texture> texture = iData->GetTexture();
	std::vector<AnimationData> animData = iData->GetAnimationData();
	int index = rand() % animData.size();
	AnimationData anim = animData[index];
	m_Animation = std::make_shared<Animation>(model, shader, texture, anim.m_RowCount, anim.m_ColCount, anim.m_FrameTime);
	m_Animation->SetIDs(anim.m_IDs);
	m_Animation->SetIsLoop(anim.m_IsLoop == 1);
	m_Animation->SetSize(TILE_SIZE, TILE_SIZE);
	SetCollider(0, 0, TILE_SIZE, TILE_SIZE);
}
void Switch::SetIsActivated(bool isAct)
{
	m_IsActivated = isAct;
}
bool Switch::GetIsActivated()
{
	return m_IsActivated;
}
void Switch::SetIsRight(bool isRight)
{
	m_IsRight = isRight;
}
bool Switch::GetIsRight()
{
	return m_IsRight;
}