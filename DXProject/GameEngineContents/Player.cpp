#include "PreCompile.h"
#include "Player.h"
#include "Stage1Level.h"
#include "HUD.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(100.0f)
	, JumpSpeed_(0.f)
	, FallSpeed_(270.f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
	, IsGround_(false)
	, IsClimb_(false)
	, FrameAnimDelay_(0.1f)
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

	// 픽셀맵과의 충돌처리
	GroundFallCheck();

	// 점프입력
	JumpUpdate();

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
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DOWN, VK_DOWN);

		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_SHOOT, 'Z');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL1, 'X');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL2, 'C');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL3, 'V');


		// TODO::디버그용 상하이동
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_DOWN, 'S');
	}
}


#pragma region KeyInputFunctions

// 이동키 판정
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_RIGHT) 
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT) 
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_RIGHT) 
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

bool Player::IsUpKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

bool Player::IsUpKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

bool Player::IsUpKeyUp()
{

	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

bool Player::IsDownKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}

bool Player::IsDownKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}

bool Player::IsDownKeyUp()
{

	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}
#pragma endregion


void Player::CheckNegativeX()
{
	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
		//Renderer_->SetPivot(PIVOTMODE::RIGHT);
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	// TODO::애니메이션의 프레임에 따라서 피봇값을 조절할 필요 있음.
	Renderer_->SetPivot(PIVOTMODE::LEFT);
}

// 카메라 이동 업데이트
void Player::CameraUpdate()
{
	float4 PlayerPos = this->GetTransform().GetLocalPosition();

	// 카메라 추적
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ PlayerPos.x, PlayerPos.y });
}

// 시간에 따른 점프 스피드 값 조정
void Player::JumpUpdate()
{
	if (true == IsJumpKeyDown())
	{
		PlayerJump();
	}

	if (false == IsGround_)
	{
		JumpSpeed_ += GameEngineTime::GetDeltaTime() * FallSpeed_;

		if (JumpSpeed_ >= FallSpeed_)
		{
			JumpSpeed_ = FallSpeed_;
		}
	}
	else
	{
		JumpSpeed_ = 0.0f;
	}
}

// 점프 스피드 입력
void Player::PlayerJump()
{
	// 땅에 닿아있는 경우에만 점프 가능
	if (true == IsGround_)
	{
		IsGround_ = false;
		JumpSpeed_ = -150.0f;
	}
}

// 하단 충돌 체크 후 중력처리
void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 줄에 타고 있으면 중력을 받지 않음
	if (true == IsClimb_)
	{
		return;
	}

	// 하단 중앙
	float4 ColorDown = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 좌측
	float4 ColorDownLeft = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 우측
	float4 ColorDownRight = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	// 하단 3점이 모두 땅에 닿지 않아야 바닥으로
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
		)
	{
		IsGround_ = false;

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * JumpSpeed_ * DeltaTime_);
	}
	else
	{
		IsGround_ = true;
	}

	// 디버그용 RGB값 추출
	//std::string r = std::to_string(ColorDown.r);
	//std::string g = std::to_string(ColorDown.g);
	//std::string b = std::to_string(ColorDown.b);

	//GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);

}

// 캐릭터 오른쪽 맵 충돌 체크
bool Player::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 오른쪽 중단
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// 오른쪽 하단
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	return true;
}

// 캐릭터 왼쪽 맵 충돌 체크
bool Player::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 왼쪽 중단
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// 왼쪽 하단
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	return true;
}