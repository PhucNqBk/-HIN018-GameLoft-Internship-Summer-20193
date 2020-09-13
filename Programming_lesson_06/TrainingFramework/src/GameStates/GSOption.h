#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "soloud_wav.h"
#include "soloud_thread.h"
#include "Application.h"
#include <string>

class Sprite2D;
class Sprite3D;
class Text;

class GSOption : public GameStateBase
{
public :
	GSOption();
	~GSOption();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void UpdateVolume();
private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_Option;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::shared_ptr<Text>  m_TextMusic;
	std::shared_ptr<Text>  m_TextSFX;

	std::shared_ptr<Text>  m_MusicVolume;
	std::shared_ptr<Text>  m_SFXVolume;
	

};
