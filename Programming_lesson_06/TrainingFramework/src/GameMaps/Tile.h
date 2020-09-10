#pragma once
#include "Sprite2D.h"

class Tile : public Sprite2D
{
public:
	Tile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int id);
	Tile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Tile();

	int			GetTileID();
	void		SetTileID(int id);

	void		Init();
	void		Draw(int rcount, int ccount);
	void		Update(GLfloat deltatime) override;
	

protected:
	int m_TileID;

};