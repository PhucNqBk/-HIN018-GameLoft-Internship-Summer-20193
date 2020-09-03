#include "GSCredit.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSCredit::GSCredit()
{

}
GSCredit::~GSCredit()
{

}
void GSCredit::Init() 
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Background = std::make_shared<Sprite2D>(model, shader, texture);
	m_Background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Background->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_game");
	m_Button = std::make_shared<GameButton>(model1, shader, texture);
	m_Button->Set2DPosition(screenWidth -100, 30);
	m_Button->SetSize(200, 50);
	m_Button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text = std::make_shared< Text>(shader, font, " This is an intern project", TEXT_COLOR::RED, 1.0);
	m_Text->Set2DPosition(Vector2(5, 25));
}
void GSCredit::Exit() 
{

}

void GSCredit::Pause()
{

}
void GSCredit::Resume()
{

}

void GSCredit::HandleEvents()
{

}
void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{

}
void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	
		m_Button->HandleTouchEvents(x, y, bIsPressed);
	//	if (m_Button->IsHandle()) break;
}
void GSCredit::Update(float deltaTime)
{
	m_Button->Update(deltaTime);
}
void GSCredit::Draw()
{
	m_Background->Draw();
	m_Button->Draw();
	m_Text->Draw();
}