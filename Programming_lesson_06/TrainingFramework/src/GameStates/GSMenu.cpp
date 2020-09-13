#include "GSMenu.h"
#include"soloud.h"
#include "soloud_wav.h"
#include "soloud_thread.h"
#include "Application.h"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");
	auto shaderX = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model1, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("New_Game");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 400);
	button->SetSize(450, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//option button
	//Button back
	texture = ResourceManagers::GetInstance()->GetTexture("Option");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 470);
	button->SetSize(400, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Option);
	});
	m_listButton.push_back(button);

	
	//credit button
	texture = ResourceManagers::GetInstance()->GetTexture("Credit");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 540);
	button->SetSize(450, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
	});
	m_listButton.push_back(button);


	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Exit_Game");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 610);
	button->SetSize(500, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
	
	texture = ResourceManagers::GetInstance()->GetTexture("GameTitle", GL_NEAREST);
	m_GameTitle = std::make_shared<Sprite2D>(model1, shader, texture);
	m_GameTitle->Set2DPosition(screenWidth / 2, 250);
	m_GameTitle->SetSize(640, 360);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "", TEXT_COLOR::RED, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 120, 120));

	
	// Declare some variables
	// Initialize SoLoud (automatic back-end selection)
	
	//isPlay = false;
	
	wav.load("../Data/Sound/Menu.wav");// Load a wave file
	     // Play it
	//Application::GetInstance()->soloud.play(wav);
	bg_handle = Application::GetInstance()->soloud.play(wav);
	Application::GetInstance()->soloud.setVolume(bg_handle,((float)(Application::GetInstance()->Music_Volume))/10.0f);
	Application::GetInstance()->soloud.setLooping(bg_handle, true);
//	soloud.setLooping(soloud.play(wav), true);
}

void GSMenu::Exit()
{

}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{
	Application::GetInstance()->soloud.stopAll();
	bg_handle = Application::GetInstance()->soloud.play(wav);
	Application::GetInstance()->soloud.setVolume(bg_handle,((float)(Application::GetInstance()->Music_Volume)) / 10.0f);
	Application::GetInstance()->soloud.setVolume(bg_handle, ((float)(Application::GetInstance()->Music_Volume)) / 10.0f);
	Application::GetInstance()->soloud.setLooping(bg_handle, true);
}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) {
			
			break;
		}
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
	m_GameTitle->Draw();
}
