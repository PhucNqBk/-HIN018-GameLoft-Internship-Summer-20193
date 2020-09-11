#include "UIContainer.h"
#include "Models.h"
#include "Shaders.h"
#include "Texture.h"
#include "ResourceManagers.h"
UIContainer::UIContainer()
{

}
UIContainer::UIContainer(std::shared_ptr<Player> player ):m_Player(player)
{
	m_RowCount = 1;
	m_ColCount = 6;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("hearts",GL_NEAREST);
	for (int i = 0; i < 3; ++i)
	{
		auto tile = std::make_shared<Tile>(model, shader, texture, 5);
		tile->SetSize(32, 32);
		tile->Set2DPosition(48 + (2 * i + 1)*40 / 2 , 48);
		m_Hearts.push_back(tile);
	}
}
UIContainer::~UIContainer()
{

}

void UIContainer::Init()
{

}
void UIContainer::Draw()
{
	for (auto it : m_Hearts) 
	{
		it->Draw(m_RowCount, m_ColCount);
	}
}
void UIContainer::Update(GLfloat deltatime)
{
	int health = m_Player->GetHealth();
	for (int i = 0; i < health / 4; ++i)
	{
		m_Hearts[i]->SetTileID(5);
	}
	if (health / 4 < m_Hearts.size()) {
		m_Hearts[health / 4]->SetTileID(health % 4+ 1);
		for (int i = health / 4 + 1;i < m_Hearts.size();++i) {
			m_Hearts[i]->SetTileID(1);
		}
	}
		
	
}
