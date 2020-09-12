#include "Switch.h"

Switch::Switch() :Item()
{
	m_ItemType = SWITCH;
	m_IsActivated = false;
}
Switch::Switch(std::shared_ptr<ItemData> iData, bool isEnable) : m_IsEnable(isEnable)
{
	m_ItemType = SWITCH;
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


void Switch::CreateItemFromData(std::shared_ptr<ItemData> iData)
{
	m_Duration = iData->GetDuration();
	std::shared_ptr<Models> model = iData->GetModel();
	std::shared_ptr<Shaders> shader = iData->GetShader();
	std::shared_ptr<Texture> texture = iData->GetTexture();
	std::vector<AnimationData> animData = iData->GetAnimationData();
	AnimationData anim = animData[0];
	m_AnimationOn = std::make_shared<Animation>(model, shader, texture, anim.m_RowCount, anim.m_ColCount, anim.m_FrameTime);
	m_AnimationOn->SetIDs(anim.m_IDs);
	m_AnimationOn->SetIsLoop(anim.m_IsLoop == 1);
	m_AnimationOn->SetSize(TILE_SIZE, TILE_SIZE);
	
	anim = animData[1];
	m_AnimationOff = std::make_shared<Animation>(model, shader, texture, anim.m_RowCount, anim.m_ColCount, anim.m_FrameTime);
	m_AnimationOff->SetIDs(anim.m_IDs);
	m_AnimationOff->SetIsLoop(anim.m_IsLoop == 1);
	m_AnimationOff->SetSize(TILE_SIZE, TILE_SIZE);

	m_Animation = m_AnimationOff;
	SetCollider(0, 0, TILE_SIZE/2, TILE_SIZE/2);
}
void Switch::SetIsActivated(bool isAct)
{
	m_IsActivated = isAct;
	m_Animation = (isAct == true) ? m_AnimationOn : m_AnimationOff;
}
bool Switch::GetIsActivated()
{
	return m_IsActivated;
}
void Switch::SetIsEnable(bool isRight)
{
	m_IsEnable = isRight;
}
bool Switch::GetIsEnable()
{
	return m_IsEnable;
}
void Switch::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
	m_Animation->Set2DPosition(x,y);
	m_AnimationOff->Set2DPosition(x, y);
	m_AnimationOn->Set2DPosition(x, y);
}