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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto model1 = ResourceManagers::GetInstance()->GetModel("Sprite2Dv1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shaderX = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//load player
//	texture = ResourceManagers::GetInstance()->GetTexture("Player");
//	m_player = std::make_shared<Player>(model1, shader, texture);
//	m_player->Set2DPosition(screenWidth / 2, screenHeight / 2);
//	m_player->SetSize(16, 16);
	//m_player = std::make_shared<Player>();
	//m_player->SetPosition(screenWidth / 2, screenHeight / 2);
	//m_player->CreatAnimation("../Data/Asset/animations.aml");
	//m_player->SetEntity(m_player);
	//m_player->ChangeState(EntityStateType::IDLE);

	texture = ResourceManagers::GetInstance()->GetTexture("tilesheet_numbered", GL_NEAREST);
	testDungeon = std::make_shared<Dungeon>();

	
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	
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
	//m_player->Update(deltaTime);
	testDungeon->Update(deltaTime);
}

void GSPlay::Draw()
{
	//DWORD st = GetTickCount();
	m_BackGround->Draw();
//	st = GetTickCount();
	testDungeon->Draw();
//	std::cout << "Dung:" << GetTickCount() - st << std::endl;
	m_score->Draw();
	//m_player->Draw();

}

void GSPlay::SetNewPostionForBullet()
{
}