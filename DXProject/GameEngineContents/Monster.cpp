#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>

Monster::Monster() 
	: Renderer_(nullptr)
	, JumpSpeed_(0.f)
	, FallSpeed_(270.f)
	, DeltaTime_(0.0f)
	, FrameAnimDelay_(0.06f)
	, ChaseFlg_(false)
	, ChaseRange_(20.0f)
{
}

Monster::~Monster() 
{
}

void Monster::Start()
{
	// 애니메이션 초기화
	AnimationInit();

	// 스테이트 초기화
	StateInit();
}

void Monster::Update(float _DeltaTime)
{
	DeltaTime_ = _DeltaTime;

	// 픽셀맵과의 충돌처리
	GroundFallCheck();

	ChaseFlgUpdate();

	JumpUpdate();

	// 스테이트 업데이트
	StateManager_.Update(_DeltaTime);

	// 좌우반전 체크
	CheckNegativeX();
}

void Monster::CheckNegativeX()
{
	if (MoveDir_.CompareInt3D(float4::LEFT))
	{
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	// TODO::애니메이션의 프레임에 따라서 피봇값을 조절할 필요 있음.
	Renderer_->SetPivot(PIVOTMODE::CENTER);
}

void Monster::JumpUpdate()
{
	if (true == IsJump_)
	{
		MonsterJump();
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

void Monster::ChaseFlgUpdate()
{
	// 둘 사이의 거리가 설정된 값보다 가까우면 chase상태로 전환
	// ChaseFlg는 false로 전환되지 않음
	if (false == ChaseFlg_)
	{
		// 몬스터와 플레이어 사이의 거리를 취득
		float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
							   , this->GetTransform().GetWorldPosition().y, 0.0f };
		float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
		float4 Length = MonsterLength - PlayerLength;

		if (Length.Length() <= ChaseRange_)
		{
			ChaseFlg_ = true;
		}
	}
}

void Monster::MonsterJump()
{
	// 땅에 닿아있는 경우에만 점프 가능
	if (true == IsGround_)
	{
		IsGround_ = false;
		JumpSpeed_ = -150.0f;
	}
}

#pragma region GroundCheck


void Monster::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
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

		for (;;)
		{
			// 위로 한칸 올림
			this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

			// 올린뒤의 픽셀 취득
			// 하단 중앙
			ColorDown = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 좌측
			ColorDownLeft = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 우측
			ColorDownRight = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

			// 가장 위로 올라왔으면 탈출
			if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
				)
			{
				// 다시 한칸 내림
				this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
				break;
			}
		}
	}
}

// TODO::캐릭터들의 피봇이 결정되면 충돌판정의 위치도 함께 수정될 것.
bool Monster::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 오른쪽 하단
	// 바닥이 없으면 못감
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// 오른쪽 중단
	// 벽에 막혀 있으면 못감
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	return false;
}

bool Monster::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 왼쪽 하단
	// 바닥이 없으면 못감
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// 왼쪽 중단
	// 벽에 막혀 있으면 못감
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	return false;
}

#pragma endregion

#pragma region Common FSM Function Start


void Monster::CommonIdleStart(std::string _AnimName)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonMoveStart(std::string _AnimName)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonAttackStart(std::string _AnimName)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonChaseStart(std::string _AnimName)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonDeathStart(std::string _AnimName)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

#pragma endregion


#pragma region Common FSM Function Update

void Monster::CommonIdleUpdate()
{
	if (true == ChaseFlg_)
	{
		StateManager_.ChangeState(MONSTER_FSM_CHASE);
	}

	ToMoveGauge_ += DeltaTime_;

	if (ToMoveGauge_ >= 1.0f)
	{
		// Idle에서 Move로 전환될때 방향을 지정해줌
		//MoveDirFlg_ = GameEngineRandom::MainRandom.RandomInt(0, 1);
		MoveDirFlg_ = 0;
		StateManager_.ChangeState(MONSTER_FSM_MOVE);
		ToMoveGauge_ = 0.0f;
	}
}

void Monster::CommonMoveUpdate()
{
	ToIdleGauge_ += DeltaTime_;

	if (ToIdleGauge_ >= 2.0f)
	{
		StateManager_.ChangeState(MONSTER_FSM_IDLE);
		ToIdleGauge_ = 0.0f;
	}

	switch (MoveDirFlg_)
	{
	case false:

		MoveDir_ = float4::LEFT;

		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);

		break;
	case true:

		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

		break;
	default:
		break;
	}
}

void Monster::CommonChaseUpdate()
{
	float4 MonsterPos = this->GetTransform().GetWorldPosition();

	// 오른쪽으로 
	if (MonsterPos.x <= PlayerPos_.x)
	{
		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

	}
	// 왼쪽으로
	else if (MonsterPos.x >= PlayerPos_.x)
	{
		MoveDir_ = float4::LEFT;

		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);
	}
}

#pragma endregion