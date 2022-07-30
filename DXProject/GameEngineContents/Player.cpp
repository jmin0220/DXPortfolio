#include "PreCompile.h"
#include "Player.h"
#include "Stage1Level.h"
#include "HUD.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(100.0f)
	, JumpSpeed_(0.f)
	, FallSpeed_(150.f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
	, IsGround_(false)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// 키조작 초기화
	KeyInit();
	// 애니메이션 초기화
	AnimationInit();
	// 스테이트 초기화
	StateInit();

	HUD_ = GetLevel()->CreateActor<HUD>(ObjectGroup::UI);
}

void Player::Update(float _DeltaTime)
{
	// 델타타임 초기화
	DeltaTime_ = _DeltaTime;

	// 점프입력
	JumpUpdate();

	// 픽셀맵과의 충돌처리
	GroundFallCheck();

	// 스테이트 업데이트
	StateManager_.Update(DeltaTime_);

	// 좌우반전 체크
	CheckNegativeX();

	// 카메라 업데이트
	CameraUpdate();

}

void Player::KeyInit()
{
	if (false == GameEngineInput::GetInst()->IsKey(PLAYER_KEY_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_RIGHT, VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_JUMP, VK_SPACE);

		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_SHOOT, 'Z');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL1, 'X');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL2, 'C');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL3, 'V');


		// TODO::디버그용 상하이동
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DOWN, VK_DOWN);
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

bool Player::IsJumpKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_JUMP))
	{
		return false;
	}

	return true;
}

bool Player::IsJumpKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_JUMP))
	{
		return false;
	}

	return true;
}

bool Player::IsJumpKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_JUMP))
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


void Player::JumpUpdate()
{
	if (true == IsJumpKeyDown())
	{
		PlayerJump();
	}

	if (JumpSpeed_ != 0.0f)
	{
		JumpSpeed_ += GameEngineTime::GetDeltaTime() * FallSpeed_;

		//if (JumpSpeed_ <= FallSpeed_)
		//{
		//	JumpSpeed_ = FallSpeed_;
		//}
	}
	else
	{
		JumpSpeed_ = FallSpeed_;
	}
}


void Player::PlayerJump()
{
	if (true == IsGround_)
	{
		JumpSpeed_ = -150.0f;
	}
}


void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
		                          , -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * JumpSpeed_ * DeltaTime_);
		IsGround_ = false;
	}
	else if (false == Color.CompareInt4D(float4::ZERO))
	{
		// 땅에 닿았을경우 점프 값 초기화
		JumpSpeed_ = 0.0f;
		IsGround_ = true;
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