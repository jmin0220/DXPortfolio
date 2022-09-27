#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <math.h>

Monster::Monster() 
	: Renderer_(nullptr)
	, JumpSpeed_(0.f)
	, FallSpeed_(270.f)
	, DeltaTime_(0.0f)
	, FrameAnimDelay_(ANIMATION_FRAME_DELAY)
	, ChaseFlg_(false)
	, ChaseRange_(120.0f)
	, IsMonsterDeath_(false)
	, IsFallCheck_(true)
	, IsHitted_(true)
{
}

Monster::~Monster() 
{
}

void Monster::Start()
{
	// 애니메이션 초기화
	AnimationInit();

	// 콜리전 초기화
	CollisionInit();

	// 스테이트 초기화
	StateInit();

	// 몬스터 개체마다 다른 골드, 경험치를 생성
	GameEngineRandom* tmpRandom = new GameEngineRandom();
	Gold_ = tmpRandom->RandomInt(4 * Lv_, 5 * Lv_);
	Exp_ = tmpRandom->RandomInt(10 * Lv_, 13 * Lv_);

	delete tmpRandom;
	tmpRandom = nullptr;
}

void Monster::Update(float _DeltaTime)
{
	DeathSwitch();

	DeltaTime_ = _DeltaTime;
	AtkTimer_ += DeltaTime_;

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
	if (Renderer_ == nullptr)
	{
		return;
	}

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

void Monster::DeathSwitch()
{
	if (MonsterHp_ <= 0)
	{
		IsMonsterDeath_ = true;

		Collision_->Off();
		StateManager_.ChangeState(MONSTER_FSM_DEATH);
	}
}

#pragma region GroundCheck

void Monster::GroundFallCheck()
{
	if (false == IsFallCheck_)
	{
		return;
	}

	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 하단 중앙
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 좌측
	float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 우측
	float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	// 하단 3점이 모두 땅에 닿지 않아야 바닥으로
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
		)
	{
		IsJump_ = true;
		IsGround_ = false;

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * JumpSpeed_ * DeltaTime_);
	}
	else
	{
		IsJump_ = false;
		IsGround_ = true;

		// TODO:: 삭제헤도 되는 코드?
		//for (int i = 0; i < 3; i++)
		//{
		//	// 위로 한칸 올림
		//	this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

		//	// 올린뒤의 픽셀 취득
		//	// 하단 중앙
		//	ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		//		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		//	// 하단 좌측
		//	ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
		//		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		//	// 하단 우측
		//	ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
		//		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

		//	// 가장 위로 올라왔으면 탈출
		//	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		//		false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		//		false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
		//		)
		//	{
		//		// 다시 한칸 내림
		//		this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
		//		break;
		//	}
		//}
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
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// 오른쪽 중단
	// 벽에 막혀 있으면 못감
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
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
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// 왼쪽 중단
	// 벽에 막혀 있으면 못감
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
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
	float4 MonsterPos = this->GetTransform().GetWorldPosition();

	// 몬스터와 플레이어 사이의 거리를 취득
	float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
						   , this->GetTransform().GetWorldPosition().y, 0.0f };
	float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
	float4 Length = MonsterLength - PlayerLength;

	// 몬스터가 충분히 멀리 있을경우에만 이동 애니메이션으로 변경
	if (Length.Length() > 160.0f)
	{
		// 애니메이션 전환
		Renderer_->ChangeFrameAnimation(_AnimName);
		Renderer_->ScaleToTexture();
	}
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
		MoveDirFlg_ = GameEngineRandom::MainRandom.RandomInt(0, 1);
		StateManager_.ChangeState(MONSTER_FSM_MOVE);
		ToMoveGauge_ = 0.0f;
	}
}

void Monster::CommonMoveUpdate()
{
	if (true == ChaseFlg_)
	{
		StateManager_.ChangeState(MONSTER_FSM_CHASE);

		return;
	}

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

		if (true == GroundLeftCheck() && false == IsJump_)
		{
			return;
		}

		if (true == IsJump_)
		{
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ / 2 * DeltaTime_);
		}
		else
		{
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);
		}


		break;
	case true:

		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck() && false == IsJump_)
		{
			return;
		}

		if (true == IsJump_)
		{
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ / 2 * DeltaTime_);
		}
		else
		{
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);
		}

		break;
	}
}

void Monster::CommonChaseUpdate(float _ChaseLength /* = 0.0f*/)
{
	float4 MonsterPos = this->GetTransform().GetWorldPosition();

	// 몬스터와 플레이어 사이의 거리를 취득
	float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
						   , this->GetTransform().GetWorldPosition().y, 0.0f };
	float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
	float4 Length = MonsterLength - PlayerLength;

	// 거리가 몬스터와 가까워졌을경우 이동 중지
	if (Length.Length() <= abs(Renderer_->GetCurTexture()->GetScale().hix() + _ChaseLength) )
	{
		//공격으로 전환
		if (AtkTimer_ >= AtkSpeed_)
		{
			AtkTimer_ = 0.0f;
			StateManager_.ChangeState(MONSTER_FSM_ATTACK);
		}

		return;
	}

	// 오른쪽으로 
	if (MonsterPos.x <= PlayerPos_.x)
	{
		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck() && false == IsJump_)
		{
			return;
		}

		if (true == IsJump_)
		{
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ / 2 * DeltaTime_);
		}
		else
		{
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);
		}

	}
	// 왼쪽으로
	else if (MonsterPos.x >= PlayerPos_.x)
	{
		MoveDir_ = float4::LEFT;

		if (true == GroundLeftCheck() && false == IsJump_)
		{
			return;
		}

		if (true == IsJump_)
		{
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ / 2 * DeltaTime_);
		}
		else
		{
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);
		}
	}
}

void Monster::CommonHitted()
{
	float4 MonsterPos = this->GetTransform().GetWorldPosition();

	// 몬스터와 플레이어 사이의 거리를 취득
	float4 MonsterLength = { this->GetTransform().GetWorldPosition().x
							, this->GetTransform().GetWorldPosition().y, 0.0f };
	float4 PlayerLength = { PlayerPos_.x, PlayerPos_.y, 0.0f };
	float4 Length = MonsterLength - PlayerLength;

	// 오른쪽으로 
	if (MonsterPos.x <= PlayerPos_.x)
	{
		MoveDir_ = float4::RIGHT;

		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ / 2 * DeltaTime_);

	}
	// 왼쪽으로
	else if (MonsterPos.x >= PlayerPos_.x)
	{
		MoveDir_ = float4::LEFT;

		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ / 2 * DeltaTime_);
	}
}

#pragma endregion