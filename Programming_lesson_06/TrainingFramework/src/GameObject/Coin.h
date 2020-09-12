#pragma once
#include "Item.h"
#include "ItemData.h"

class Coin : public Item
{
public:
	Coin();
	Coin(std::shared_ptr<ItemData> iData);
	~Coin();

	virtual void	Init() override;
	virtual void	Update(GLfloat deltatime) override;
	//virtual void	Draw() override;
	virtual int		TriggerEffect() override;
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData) override;
private:
	int m_Score;
};