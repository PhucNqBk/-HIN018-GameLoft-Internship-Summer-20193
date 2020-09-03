#pragma once
#include "Sprite2D.h"

class Animation : public Sprite2D
{
public:
	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col,int rcount ,float frtime);
	~Animation();

	void		Init();
	void		Draw() override;
	void		Update(GLfloat deltatime) override;

private:
	int m_rowCount;
	int m_colCount;
	int m_currentRow;
	int m_currentCol;
	float m_currentTime;
	float m_frameTime;
};