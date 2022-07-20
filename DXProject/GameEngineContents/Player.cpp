#include "PreCompile.h"
#include "Player.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(50.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("PlayerRight", 'D');
		GameEngineInput::GetInst()->CreateKey("PlayerUp", 'W');
		GameEngineInput::GetInst()->CreateKey("PlayerDown", 'S');
	}

	GetTransform().SetLocalScale({ 1, 1, 1 });
		
	{
		Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		Renderer_->GetTransform().SetLocalScale({ 32, 15, 100 });
		Renderer_->SetTexture("sCowboyIdle_0.png");

		Renderer_->CreateFrameAnimationFolder("BanditShoot1", FrameAnimation_DESC("BanditShoot1", 0.1f, false));
		//Renderer_->CreateFrameAnimationFolder("BanditShoot2", FrameAnimation_DESC("BanditShoot2", 0.1f));

		Renderer_->ChangeFrameAnimation("BanditShoot1");
		//Renderer_->AnimationBindEnd("BanditShoot1", std::bind(FrameAnimation_DESC&, Shoot2));
	}
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);

		// ÁÂ¿ì¹ÝÀü
		Renderer_->GetTransform().PixLocalNegativeX();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
		Renderer_->GetTransform().PixLocalPositiveX();
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}
}

void Player::End()
{

}