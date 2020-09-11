#pragma once
#include "Sprite2D.h"
#include <vector>
class Animation : public Sprite2D
{
public:
	Animation(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int row, int col,float frtime);
	~Animation();

	void		Init();
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
	void		Update(GLfloat deltatime, bool isInvunerable);
	void		SetIsLoop(bool loop);
	int		GetCurrentFrame();
	int		GetFrameCount();
	void		SetIDs(const int a[], int count);
	void		SetIDs(std::vector<int> a);
private:
	std::vector<int> m_IDs;
	bool m_IsLoop;
	int m_CurrentFrame;
	int m_RowCount;
	int m_ColCount;
	int m_FrameCount;
	float m_CurrentTime;
	float m_FrameTime;
};