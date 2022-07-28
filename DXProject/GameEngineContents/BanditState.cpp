#include "PreCompile.h"
#include "Bandit.h"

// 업데이트
void Bandit::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsShootKeyDown())
	{
		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
		return;
	}


	// 이동키가 눌리면 이동
	if (true == IsMoveKeyDown())
	{
		StateManager_.ChangeState(PLAYER_STATE_MOVE);
		return;
	}
}


void Bandit::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// 키가 떨어졌을경우 Idle상태로 전환
	if (false == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_IDLE);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT))
	{
		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);

		// TODO::픽셀체크함수 생성시 수정요
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT))
	{
		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

		// TODO::픽셀체크함수 생성시 수정요
		MoveDir_ = float4::RIGHT;
	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * DeltaTime_);

	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);

	}
}


void Bandit::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill1Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill2Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill3Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::Skill4Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Bandit::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


// 스타트
void Bandit::IdleStart(const StateInfo& _Info)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
}

void Bandit::MoveStart(const StateInfo& _Info)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_WALK);
}

void Bandit::ShootStart(const StateInfo& _Info)
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SHOOT);
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SHOOT, &Bandit::EndAnimation, this);
}

void Bandit::Skill1Start(const StateInfo& _Info)
{

}

void Bandit::Skill2Start(const StateInfo& _Info)
{

}

void Bandit::Skill3Start(const StateInfo& _Info)
{

}

void Bandit::Skill4Start(const StateInfo& _Info)
{

}

void Bandit::ClimbStart(const StateInfo& _Info)
{

}

void Bandit::DeathStart(const StateInfo& _Info)
{

}


// 엔드
void Bandit::IdleEnd(const StateInfo& _Info)
{

}

void Bandit::MoveEnd(const StateInfo& _Info)
{

}

void Bandit::ShootEnd(const StateInfo& _Info)
{

}

void Bandit::Skill1End(const StateInfo& _Info)
{

}

void Bandit::Skill2End(const StateInfo& _Info)
{

}

void Bandit::Skill3End(const StateInfo& _Info)
{

}

void Bandit::Skill4End(const StateInfo& _Info)
{

}

void Bandit::ClimbEnd(const StateInfo& _Info)
{

}

void Bandit::DeathEnd(const StateInfo& _Info)
{

}
