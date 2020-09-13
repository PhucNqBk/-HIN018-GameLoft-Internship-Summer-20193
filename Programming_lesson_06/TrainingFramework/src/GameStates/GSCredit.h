#pragma once
#include "GameStates/GameStatebase.h"
#include "GameButton.h"
#include"soloud.h"
#include "soloud_wav.h"
#include "Application.h"
class Sprite2D;
class Sprite3D;
class Text;

class GSCredit :
	public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_Background;
	std::shared_ptr<GameButton> m_Button;
	std::shared_ptr<Text> m_Text;
	std::shared_ptr<Text> m_Name;
	std::shared_ptr<Text> m_Mentor;
	std::shared_ptr<Text> m_Thanks;
};

