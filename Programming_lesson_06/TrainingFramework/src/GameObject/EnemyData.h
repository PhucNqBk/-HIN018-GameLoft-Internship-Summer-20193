#pragma once
#include "Models.h"
#include "Shaders.h"
#include "Texture.h"
#include "Constant.h"
#include <map>
#include <vector>
#include <string>
class EnemyData
{
public:
	EnemyData();
	EnemyData(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~EnemyData();
	
	std::shared_ptr<Models> GetModel();
	std::shared_ptr<Shaders> GetShader();
	std::shared_ptr<Texture> GetTexture();

	void			SetHealth(int amount);
	int				GetHealth();
	void			SetAnimationData(std::map<std::string, AnimationData> m_data);
	std::map<std::string, AnimationData> GetAnimationDatas();

protected:
	std::shared_ptr<Models> m_Model;
	std::shared_ptr<Shaders> m_Shader;
	std::shared_ptr<Texture> m_Texture;

	std::map<std::string, AnimationData> m_AnimData;
	int m_Health;
};
