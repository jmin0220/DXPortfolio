#include "PreCompile.h"
#include "Player.h"
#include "Stage1Level.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(200.0f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	//this->GetTransform().SetWorldPosition(float4::ZERO);

	KeyInit();
	AnimationInit();
}

void Player::Update(float _DeltaTime)
{
	// 델타타임 초기화
	DeltaTime_ = _DeltaTime;

	// 낙하 체크
	GroundFallCheck();

	// 스테이트 업데이트
	StateUpdate();

	// 좌우반전 체크
	CheckNegativeX();

	// 카메라 업데이트
	CameraUpdate();

	// 픽셀맵과의 충돌처리
	GroundFallCheck();
}

void Player::KeyInit()
{
	if (false == GameEngineInput::GetInst()->IsKey(PLAYER_KEY_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_RIGHT, VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_SHOOT, 'Z');


		// TODO::디버그용 상하이동
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DOWN, VK_DOWN);
	}
}


void Player::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_IDLE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_IDLE, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SHOOT, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SHOOT, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_WALK, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_WALK, 0.1f, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_JUMP, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_JUMP, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_CLIMB, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_CLIMB, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_DEATH, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_DEATH, 0.1f, false));

	//Renderer_->GetTransform().SetLocalScale({ 66, 30 });
	//Renderer_->CreateFrameAnimationFolder("BanditShoot2", FrameAnimation_DESC("BanditShoot2", 0.1f));
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFT);
}

void Player::StateChange(STATE _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case STATE::Idle:
			IdleStart();
			break;
		case STATE::Move:
			MoveStart();
			break;
		case STATE::SHOOT:
			ShootStart();
			break;
		case STATE::SKILL1:
			Skill1Start();
			break;
		case STATE::SKILL2:
			Skill2Start();
			break;
		case STATE::SKILL3:
			Skill3Start();
			break;
		case STATE::SKILL4:
			Skill4Start();
			break;
		case STATE::CLIMB:
			ClimbStart();
			break;
		case STATE::Death:
			DeathStart();
			break;
		case STATE::None:
			CurrentState_ = _State;
			return;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void Player::StateUpdate()
{
	switch (CurrentState_)
	{
	case STATE::Idle:
		IdleUpdate();
		break;
	case STATE::Move:
		MoveUpdate();
		break;
	case STATE::SHOOT:
		ShootUpdate();
		break;
	case STATE::SKILL1:
		Skill1Update();
		break;
	case STATE::SKILL2:
		Skill2Update();
		break;
	case STATE::SKILL3:
		Skill3Update();
		break;
	case STATE::SKILL4:
		Skill4Update();
		break;
	case STATE::CLIMB:
		ClimbUpdate();
		break;
	case STATE::Death:
		DeathUpdate();
		break;
	case STATE::None:
		return;
	default:
		break;
	}
}

// 이동키 판정
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

// 발사키 판정
bool Player::IsShootKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

bool Player::IsShootKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

bool Player::IsShootKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

void Player::CheckNegativeX()
{
	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
		Renderer_->SetPivot(PIVOTMODE::RIGHT);
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
		Renderer_->SetPivot(PIVOTMODE::LEFT);
	}
}

void Player::CameraUpdate()
{
	// 카메라 추적
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(this->GetTransform().GetLocalPosition());
}

void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
		                          , -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1.0f);

	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);
	}
	else if (false == Color.CompareInt4D(float4::ZERO))
	{
		int a = 0;
	}
}

bool Player::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy());


	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		return false;
	}

	return true;
}

bool Player::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() - Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy());


	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		return false;
	}

	return true;
}

void Player::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateChange(STATE::Idle);
}
