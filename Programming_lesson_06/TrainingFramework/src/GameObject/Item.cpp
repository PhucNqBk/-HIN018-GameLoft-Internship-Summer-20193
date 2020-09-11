#include "Item.h"

Item::Item(): m_Timer(0.0f)
{

}
Item::Item(std::shared_ptr<ItemData> iData):m_Timer(0.0f)
{

}
Item::~Item()
{

}

void Item::Init()
{

}
void Item::Update(GLfloat deltatime)
{

}
void Item::Draw()
{

}
void Item::TriggerEffect()
{

}
void Item::CreateItemFromData(std::shared_ptr<ItemData> iData)
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
void Item::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
}
void Item::SetCollider(float x, float y, int w, int h)
{
	m_Collider.OffsetX = x;
	m_Collider.OffsetY = y;
	m_Collider.w = w;
	m_Collider.h = h;
}
Vector2	Item::GetPosition()
{
	return m_Position;
}
Collider2D Item::GetCollider()
{
	return m_Collider;
}