#pragma once
#include "Sprite2D.h"
#include "Constant.h"
#include "Animation.h"
#include "ItemData.h"


class Item
{
public:
	Item();
	Item(std::shared_ptr<ItemData> iData);
	~Item();

	
	virtual void	Init();
	virtual void	Update(GLfloat deltatime);
	virtual void	Draw();
	virtual int		TriggerEffect();
	virtual void	CreateItemFromData(std::shared_ptr<ItemData> iData);

	virtual void	SetPosition(float x, float y);
	void			SetCollider(float x, float y, int w, int h);
	Vector2			GetPosition();
	Collider2D		GetCollider();
	void			SetIsObtain(bool isOb);
	bool			GetIsObtain();
	int				GetItemType();
protected:
	Vector2 m_Position;
	Collider2D m_Collider;
	float m_Duration;
	float m_Timer;
	int m_ItemType;
	bool m_IsObtained;
	std::shared_ptr<Animation> m_Animation;
};
