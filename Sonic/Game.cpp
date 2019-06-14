#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Scene/TitleScene.h"



Game::Game(): screenSize(Vector2(1024, 576))
{
}


Game::~Game()
{
}

void Game::Initialize()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(screenSize.x, screenSize.y, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}

	DxLib::SetMainWindowText("Sonic The Hedgehog");		// タイトル
	//DxLib::SetWindowIconID(IDI_ICON1);	// アイコン
	DxLib::SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に描画

	p.reset(new Peripheral());

	InitPeripheral();

	ChangeScene(new TitleScene());
}

void Game::InitPeripheral()
{
	p->SetPlayerCount(2);

	p->AddCommand(0, "right",	0, KEY_INPUT_RIGHT);
	p->AddCommand(0, "left",	0, KEY_INPUT_LEFT);
	p->AddCommand(0, "up",		0, KEY_INPUT_UP);
	p->AddCommand(0, "down",	0, KEY_INPUT_DOWN);
	p->AddCommand(0, "attack",	0, KEY_INPUT_Z);
	p->AddCommand(0, "jump",	0, KEY_INPUT_X);

	for (int i = 0; i < p->GetPadCount(); ++i)
	{
		p->AddCommand(i, "right",	1 + i, PAD_INPUT_RIGHT);
		p->AddCommand(i, "left",	1 + i, PAD_INPUT_LEFT);
		p->AddCommand(i, "up",		1 + i, PAD_INPUT_UP);
		p->AddCommand(i, "down",	1 + i, PAD_INPUT_DOWN);
		p->AddCommand(i, "attack",	1 + i, PAD_INPUT_1);
		p->AddCommand(i, "jump",	1 + i, PAD_INPUT_2);
	}
}

void Game::Run()
{
	while (DxLib::ProcessMessage() == 0)
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		DxLib::ClearDrawScreen();

		p->Update();

		
		scene->Update(*p.get());

		DxLib::ScreenFlip();
	}
}

void Game::Terminate()
{
	DxLib::DxLib_End();
}

void Game::ChangeScene(Scene * s)
{
	scene.reset(s);
}

Vector2 Game::GetScreenSize() const
{
	return screenSize;
}
