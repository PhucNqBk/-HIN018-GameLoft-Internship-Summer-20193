#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Player.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "Entity.h"
#include <time.h>
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	srand(time(NULL));
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shaderX = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	

	texture = ResourceManagers::GetInstance()->GetTexture("tilesheet_numbered", GL_NEAREST);
	testDungeon = std::make_shared<Dungeon>();
	m_Player = testDungeon->GetPlayer();
	m_Running = false;
	m_GuideEnable = true;
	//text game title
	Application::GetInstance()->soloud.stopAll();
	int song = rand() % 4;
	if (song == 0)
	{
		wav.load("../Data/Sound/BGM0.wav");
	}
	else if (song == 1)
	{
		wav.load("../Data/Sound/BGM1.wav");
	}
	else if (song == 2)
	{
		wav.load("../Data/Sound/BGM2.wav");
	}
	else
	{
		wav.load("../Data/Sound/BGM3.wav");
	}
	
	// Load a wave file
	// Play it
	//Application::GetInstance()->soloud.play(wav);
	//soloud.setLooping(soloud.play(wav), true);
	bg_handle = Application::GetInstance()->soloud.play(wav);
	Application::GetInstance()->soloud.setVolume(bg_handle, ((float)(Application::GetInstance()->Music_Volume)) / 10.0f);
	Application::GetInstance()->soloud.setLooping(bg_handle, true);

	//Application::GetInstance()->soloud.setLooping(Application::GetInstance()->soloud.play(wav), true);
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	//m_player->HandleKeyEvents(key, bIsPressed);
	testDungeon->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	
	/*
	if (testDungeon->GetIsRunning() == true) {
		testDungeon->Update(deltaTime);
		m_GuideEnable = false;
	}
	*/
	testDungeon->Update(deltaTime);
		
}

void GSPlay::Draw()
{
	//DWORD st = GetTickCount();
	//m_BackGround->Draw();
//	st = GetTickCount();
	testDungeon->Draw();
	/*
	if (testDungeon->GetIsRunning() == false)
	{
		m_Pause->Draw();
	}
	if (m_GuideEnable == true) 
	{
		m_Guide->Draw();
	}
	*/
	
}

void GSPlay::SetNewPostionForBullet()
{
}