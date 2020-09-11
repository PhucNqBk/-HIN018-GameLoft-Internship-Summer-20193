#include "EnemyData.h"

EnemyData::EnemyData()
{

}
EnemyData::EnemyData(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :
	m_Model(model), m_Shader(shader), m_Texture(texture)
{

}
EnemyData::~EnemyData()
{

}
std::shared_ptr<Models> EnemyData::GetModel()
{
	return m_Model;
}
std::shared_ptr<Shaders> EnemyData::GetShader()
{
	return m_Shader;
}
std::shared_ptr<Texture> EnemyData::GetTexture()
{
	return m_Texture;
}

void EnemyData::SetHealth(int amount)
{
	m_Health = amount;
}
int	EnemyData::GetHealth()
{
	return m_Health;
}
void EnemyData::SetAnimationData(std::map<std::string, AnimationData> m_data)
{
	m_AnimData = m_data;
}
std::map<std::string, AnimationData> EnemyData::GetAnimationDatas()
{
	return m_AnimData;
}