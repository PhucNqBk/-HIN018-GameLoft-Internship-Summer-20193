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
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Background = std::make_shared<Sprite2D>(model, shader, texture);
	m_Background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Background->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("Back");
	m_Button = std::make_shared<GameButton>(model1, shader, texture);
	m_Button->Set2DPosition(100, screenHeight - 100);
	m_Button->SetSize(300, 50);
	m_Button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	m_Text = std::make_shared< Text>(shader, font, " This is an intern project made for HIN018 GameLoft Intership in Semester 20193", TEXT_COLOR::WHILE, 1.0);
	m_Text->Set2DPosition(Vector2(5,120 ));
	
	m_Name = std::make_shared< Text>(shader, font, " Made by : Nguyen Quang Phuc, Hanoi University Of Science And Technology", TEXT_COLOR::WHILE, 1.0);
	m_Name->Set2DPosition(Vector2(5, 240));

	m_Mentor = std::make_shared< Text>(shader, font, " Mentor: Hoang Manh Hung, GameLoft HAN Studio ", TEXT_COLOR::WHILE, 1.0);
	m_Mentor->Set2DPosition(Vector2(5, 360));

	m_Thanks = std::make_shared< Text>(shader, font, " THANKS FOR PLAYING! ", TEXT_COLOR::WHILE, 1.0);
	m_Thanks->Set2DPosition(Vector2(5, 480));
	//Application::GetInstance()->soloud.stopAll();
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
	m_Name->Draw();
	m_Mentor->Draw();
	m_Thanks->Draw();
}