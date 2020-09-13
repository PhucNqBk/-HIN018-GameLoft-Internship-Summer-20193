#include "GSOption.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
GSOption::GSOption()
{

}
GSOption::~GSOption()
{

}
void GSOption::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Option Sprite
	texture = ResourceManagers::GetInstance()->GetTexture("Option");
	m_Option = std::make_shared<Sprite2D>(model1, shader, texture);
	m_Option->Set2DPosition(screenWidth / 2,  100);
	m_Option->SetSize(400, 50);

	//Button List
	//Button back
	texture = ResourceManagers::GetInstance()->GetTexture("Back");
	auto button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(100, screenHeight - 100);
	button->SetSize(300, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//button down
	//Music Down
	texture = ResourceManagers::GetInstance()->GetTexture("Turn_Down");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 100,screenHeight/2 - 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		int vol = Application::GetInstance()->Music_Volume;
		Application::GetInstance()->Music_Volume = vol > 0 ? vol - 1 : 0;
	});
	m_listButton.push_back(button);
	//SfX Down
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2 - 100, screenHeight / 2 + 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		int vol = Application::GetInstance()->SFX_Volume;
		Application::GetInstance()->SFX_Volume = vol > 0 ? vol - 1 : 0;
	});
	m_listButton.push_back(button);

	// MUsic Up
	texture = ResourceManagers::GetInstance()->GetTexture("Turn_Up");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 100, screenHeight / 2 -50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		int vol = Application::GetInstance()->Music_Volume;
		Application::GetInstance()->Music_Volume = vol < 10 ? vol + 1 : 10;
	});
	m_listButton.push_back(button);

	//SFX Up:
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2 + 100, screenHeight / 2 + 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		int vol = Application::GetInstance()->SFX_Volume;
		Application::GetInstance()->SFX_Volume = vol < 10 ? vol + 1 : 10;
	});
	m_listButton.push_back(button);
	//

	//Text 

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	m_TextMusic = std::make_shared< Text>(shader, font,"BGM: ", TEXT_COLOR::WHILE, 1.2);
	m_TextMusic->Set2DPosition(Vector2(screenWidth / 2 - 220, screenHeight / 2 - 40));

	m_TextSFX = std::make_shared< Text>(shader, font, "SFX: ", TEXT_COLOR::WHILE, 1.2);
	m_TextSFX->Set2DPosition(Vector2(screenWidth / 2 - 220, screenHeight / 2 + 60));

	m_MusicVolume = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::WHILE, 1.2);
	m_MusicVolume->Set2DPosition(Vector2(screenWidth / 2 - 10, screenHeight / 2 - 40));

	m_SFXVolume = std::make_shared< Text>(shader, font, "10", TEXT_COLOR::WHILE, 1.2);
	m_SFXVolume->Set2DPosition(Vector2(screenWidth / 2 - 10, screenHeight / 2 + 60));
}
void GSOption::Exit()
{

}
void GSOption::Pause()
{

}
void GSOption::Resume()
{

}

void GSOption::HandleEvents()
{

}
void GSOption::HandleKeyEvents(int key, bool bIsPressed)
{

}
void GSOption::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) {

			break;
		}
	}
}
void GSOption::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	m_Option->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	UpdateVolume();
	m_TextMusic->Update(deltaTime);
	m_TextSFX->Update(deltaTime);
	m_MusicVolume->Update(deltaTime);
	m_SFXVolume->Update(deltaTime);
}
void GSOption::Draw()
{
	m_BackGround->Draw();
	m_Option->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_TextMusic->Draw();
	m_TextSFX->Draw();
	m_MusicVolume->Draw();
	m_SFXVolume->Draw();
}
void GSOption::UpdateVolume()
{
	std::string volum = std::to_string(Application::GetInstance()->Music_Volume);
	m_MusicVolume->setText(volum);
	volum = std::to_string(Application::GetInstance()->SFX_Volume);
	m_SFXVolume->setText(volum);
}