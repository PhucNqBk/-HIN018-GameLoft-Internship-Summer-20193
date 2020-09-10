#include "Entity.h"
#include <sstream>
#include "tinyxml/tinyxml.h"
#include <string>
#include <map>
#include "ResourceManagers.h"
Entity::Entity(int eType)
{
	m_Direction = Direction::DIR_UP;
	m_Position = Vector2(1280 / 2, 720 / 2);
	m_StateMachine = std::make_shared<EntityStateMachine>(eType);
	m_CheckKeyPress = 0;
}
Entity::~Entity()
{

}

void Entity::Init()
{

}
void Entity::Draw()
{
	m_CurrentAnimation->Draw();
}
void Entity::Update(GLfloat deltaTime)
{
	m_CurrentAnimation->Update(deltaTime);
	m_StateMachine->Update(deltaTime);
}

Direction Entity::GetDirection()
{
	return m_Direction;
}
void Entity::SetDirection(Direction dir)
{
	m_Direction = dir;
}
void Entity::SetPosition(float x, float y)
{
	m_Position = Vector2(x, y);
	m_CurrentAnimation->Set2DPosition(x, y);
}
Vector2 Entity::GetPosition()
{
	return m_Position;
}
void Entity::SetEntity(std::shared_ptr<Entity> e)
{
	m_StateMachine->SetEntity(e);
}
int		Entity::GetKeyPress()
{
	return m_CheckKeyPress;
}
void Entity::CreatAnimation(std::string filename)
{
	std::map<std::string, std::shared_ptr<Animation>> m_Anim;
	TiXmlDocument xml;
	xml.LoadFile(filename);

	if (xml.Error()) {
		std::cerr << "Failed to load: " << filename << std::endl;
		return;
	}
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
		
		if (e->Value() == std::string("sequence")) {
			std::string modelname = e->Attribute("model");
			std::string shadername = e->Attribute("shader");
			std::string texturename = e->Attribute("texture");
			int RowCount, ColCount, tile_w, tile_h;
			e->Attribute("RowCount", &RowCount);
			e->Attribute("FrameCount", &ColCount);
			e->Attribute("width", &tile_w);
			e->Attribute("height", &tile_h);

			auto model = ResourceManagers::GetInstance()->GetModel(modelname);
			auto texture = ResourceManagers::GetInstance()->GetTexture(texturename, GL_NEAREST);
			auto shader = ResourceManagers::GetInstance()->GetShader(shadername);
			
			for (TiXmlElement* fr = e->FirstChildElement(); fr != nullptr; fr = fr->NextSiblingElement())
			{
				if (fr->Value() == std::string("frame"))
				{
					std::string id = fr->Attribute("id");
					int isLoop;
					fr->Attribute("loop", &isLoop);
					int Count;
					fr->Attribute("count", &Count);
					
					//std::cout << model << " " << shader << " " << texture << " " << id << "" << std::endl;
					auto s = fr->GetText();
					std::string val;
					std::istringstream iss(s);
					int tId;
					std::vector<int> tIds;
					for (int i = 0; i < Count; i++)
					{
						std::getline(iss, val, ',');
						std::stringstream conv(val);
						conv >> tId;
						tIds.push_back(tId);
					}
					std::shared_ptr<Animation> anim = std::make_shared<Animation>(model, shader, texture, RowCount, ColCount, 0.1f);
					anim->SetIDs(tIds);
					anim->SetIsLoop(isLoop == 1);
					anim->SetSize(tile_w, tile_h);
					m_Anim[id] = anim;
				}
			}
		}
	}
	m_Animations = m_Anim;
	m_CurrentAnimation = m_Animations["player-idle-0"];
	return ;
}
void Entity::GetHealth()
{

}
void Entity::ChangeState(EntityStateType stt)
{
	m_StateMachine->ChangeState(stt);
	m_CurrentAnimation->Set2DPosition(GetPosition());

}
void Entity::ChangeAnimation(std::string id)
{
	m_CurrentAnimation = m_Animations[id];
}
std::shared_ptr<Animation> Entity::GetCurrentAnimation()
{
	return m_CurrentAnimation;
}
void Entity::SetCollider(float x, float y, float w, float h)
{
	m_Collider.OffsetX = x;
	m_Collider.OffsetY = y;
	m_Collider.w = w;
	m_Collider.h = h;
}
bool Entity::MapCollision(float posX, float posY, float col, float row)
{
	
	
	bool overlap_x = ((m_Position.x + m_Collider.OffsetX - m_Collider.w / 2) > posX - TILE_SIZE * col / 2 + TILE_SIZE) && ((m_Position.x + m_Collider.OffsetX + m_Collider.w / 2) < posX + TILE_SIZE * col / 2 - TILE_SIZE);
	bool overlap_y = ((m_Position.y + m_Collider.OffsetY - m_Collider.h / 2) > posY - TILE_SIZE * row / 2 + TILE_SIZE/2) && ((m_Position.y + m_Collider.OffsetY + m_Collider.h / 2) < posY + TILE_SIZE * row / 2 - TILE_SIZE);
	return !(overlap_x && overlap_y);
}
bool Entity::Collision(float posX, float posY,Collider2D other)
{
	bool overlap_x = ((m_Position.x + m_Collider.OffsetX - m_Collider.w / 2) < (posX + other.OffsetX + other.w/2)) && ((m_Position.x + m_Collider.OffsetX + m_Collider.w / 2) > (posX + other.OffsetX - other.w/2));
	bool overlap_y = ((m_Position.y + m_Collider.OffsetX - m_Collider.h / 2) < (posY + other.OffsetY + other.h/2)) && ((m_Position.y + m_Collider.OffsetY + m_Collider.h / 2) > (posY + other.OffsetY - other.h / 2));
	return (overlap_x && overlap_y);
}
