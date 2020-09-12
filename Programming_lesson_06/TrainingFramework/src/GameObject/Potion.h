#pragma once
#include"ItemData.h"
#include "Item.h"

class Potion : public Item
{
public:
	Potion();
	Potion(std::shared_ptr<ItemData> iData);
	~Potion();

	virtual void	Init() override;
	virtual void	Update(GLfloat deltatime) override;
	//virtual void	Draw() override;
	virtual int	TriggerEffect() override;
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData) override;
private:
	int m_Heart;
};
