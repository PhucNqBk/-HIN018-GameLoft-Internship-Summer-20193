#pragma once
#include"ItemData.h"
#include "Item.h"

class Portal : public Item
{
public:
	Portal();
	Portal(std::shared_ptr<ItemData> iData , bool isEnable);
	~Portal();

	virtual void	Init() override;
	virtual void	Update(GLfloat deltatime) override;
	//virtual void	Draw() override;
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData) override;

	void			SetIsEnable(bool isEnable);
	bool			GetIsEnable();

private:
	bool m_IsEnable;
};
