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
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_game");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 200);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//option button
	texture = ResourceManagers::GetInstance()->GetTexture("button_option");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);

	//credit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_credit");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 400);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
	});
	m_listButton.push_back(button);


	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_exit");
	button = std::make_shared<GameButton>(model1, shader, texture);
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);
	
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "BRAVE ADVENTURER", TEXT_COLOR::RED, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 120, 120));

	
	// Declare some variables
	// Initialize SoLoud (automatic back-end selection)
	
	//isPlay = false;
	wav.load("../Data/Sound/overworld1.wav");// Load a wave file
	wav0.load("../Data/Sound/Dash.wav");
	wav1.load("../Data/Sound/Sword1.wav");
	wav2.load("../Data/Sound/Sword2.wav");
	wav3.load("../Data/Sound/Sword3.wav");
	     // Play it
	//Application::GetInstance()->soloud.play(wav);
	Application::GetInstance()->soloud.setLooping(Application::GetInstance()->soloud.play(wav), true);
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
	Application::GetInstance()->soloud.setLooping(Application::GetInstance()->soloud.play(wav), true);
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
	
}
