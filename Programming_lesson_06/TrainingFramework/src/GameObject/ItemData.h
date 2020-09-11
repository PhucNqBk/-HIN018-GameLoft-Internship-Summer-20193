#pragma once
#include "Models.h"
#include "Shaders.h"
#include "Texture.h"
#include "Constant.h"
#include <map>
#include <vector>
#include <string>

class ItemData
{
public:
	ItemData();
	ItemData(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~ItemData();

	std::shared_ptr<Models> GetModel();
	std::shared_ptr<Shaders> GetShader();
	std::shared_ptr<Texture> GetTexture();

	std::vector<AnimationData> GetAnimationData();
	void		SetAnimationData(std::vector<AnimationData> aData);
	void		SetDuration(float dur);
	float		GetDuration();

private:
	std::shared_ptr<Models> m_Model;
	std::shared_ptr<Shaders> m_Shader;
	std::shared_ptr<Texture> m_Texture;

	std::vector<AnimationData> m_AnimationData;
	float m_Duration;
};