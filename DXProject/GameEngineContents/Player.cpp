#include "Player.h"
#include <iostream>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	{
		GameEngineRenderer* RendererTest = CreateComponent<GameEngineRenderer>();
		RendererTest->GetTransform().SetLocalScale({ 100, 100, 100 });
	}
}

void Player::Update(float _DeltaTime)
{
	//std::string Text = std::to_string(_DeltaTime);
	//GameEngineDebug::OutPutString(Text);
	//std::cout << "hhhh" << std::endl;
}