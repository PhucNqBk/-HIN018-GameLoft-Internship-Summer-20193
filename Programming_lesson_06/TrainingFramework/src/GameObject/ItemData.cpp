#include "ItemData.h"

ItemData::ItemData()
{

}
ItemData::ItemData(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :
	m_Model(model), m_Shader(shader), m_Texture(texture)
{

}
ItemData::~ItemData()
{

}

std::shared_ptr<Models> ItemData::GetModel()
{
	return m_Model;
}
std::shared_ptr<Shaders>ItemData::GetShader()
{
	return m_Shader;
}
std::shared_ptr<Texture> ItemData::GetTexture()
{
	return m_Texture;
}

std::vector<AnimationData> ItemData::GetAnimationData()
{
	return m_AnimationData;
}
void ItemData::SetAnimationData(std::vector<AnimationData> aData )
{
	m_AnimationData = aData;
}
void ItemData::SetDuration(float dur)
{
	m_Duration = dur;
}
float ItemData::GetDuration()
{
	return m_Duration;
}