#include "Portal.h"

Portal::Portal() :Item()
{
	m_ItemType = PORTAL;
}
Portal::Portal(std::shared_ptr<ItemData> iData, bool isEnable): m_IsEnable(isEnable)
{
	m_ItemType = PORTAL;
	Portal::CreateItemFromData(iData);
}
Portal::~Portal()
{

}
void Portal::Init()
{

}
void Portal::Update(GLfloat deltatime)
{
	m_Animation->Update(deltatime);
}

void Portal::CreateItemFromData(std::shared_ptr<ItemData> iData)
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
	m_Animation->SetSize(128, 128);
	SetCollider(0, 0, TILE_SIZE, TILE_SIZE);
}
void Portal::SetIsEnable(bool isEnable)
{
	m_IsEnable = isEnable;
}
bool Portal::GetIsEnable()
{
	return m_IsEnable;
}
