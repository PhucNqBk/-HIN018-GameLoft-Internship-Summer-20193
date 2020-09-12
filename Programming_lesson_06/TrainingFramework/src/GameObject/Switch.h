#pragma once
#include"ItemData.h"
#include "Item.h"

class Switch : public Item
{
public:
	Switch();
	Switch(std::shared_ptr<ItemData> iData, bool isEnable);
	~Switch();

	virtual void	Init() override;
	virtual void	Update(GLfloat deltatime) override;
	//virtual void	Draw() override;
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData) override;
	virtual void	SetPosition(float x, float y)override;
	void			SetIsActivated(bool isAct);
	bool			GetIsActivated();
	void			SetIsEnable(bool isEnable);
	bool			GetIsEnable();
private:
	bool m_IsActivated;
	bool m_IsEnable;
	std::shared_ptr<Animation> m_AnimationOn;
	std::shared_ptr<Animation> m_AnimationOff;
};
