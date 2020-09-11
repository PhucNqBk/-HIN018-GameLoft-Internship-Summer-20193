#pragma once
#include"ItemData.h"
#include "Item.h"

class Switch : public Item
{
public:
	Switch();
	Switch(std::shared_ptr<ItemData> iData, bool isRight);
	~Switch();

	virtual void	Init() override;
	virtual void	Update(GLfloat deltatime) override;
	//virtual void	Draw() override;
	virtual void	TriggerEffect() override;
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData) override;

	void			SetIsActivated(bool isAct);
	bool			GetIsActivated();
	void			SetIsRight(bool isRight);
	bool			GetIsRight();
private:
	bool m_IsActivated;
	bool m_IsRight;
};
