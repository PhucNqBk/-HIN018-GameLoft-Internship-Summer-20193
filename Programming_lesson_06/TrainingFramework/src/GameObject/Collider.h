#pragma once
#include "Sprite2D.h"
class Collider
{
public:
	Collider(float x, float y, int w, int h);
	~Collider();

	void		SetCollider(float x, float y, int w, int h);
	float		GetX();
	float		GetY();
	int			GetW();
	int			GetH();
private:
	float x, y;
	int w, h;
};