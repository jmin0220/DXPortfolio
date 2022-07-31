#include "PreCompile.h"
#include "Commando.h"

// ������Ʈ
void Commando::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsShootKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
		return;
	}

	// �̵�Ű�� ������ �̵�
	if (true == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_MOVE);
		return;
	}

	if (true == IsUpKeyPress())
	{
		float4 ColorCenter = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (ColorCenter.CompareInt4D({0.0f, 1.0f, 0.0f}))
		{
			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
	}
}


void Commando::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// ����Ű�� ������ ������Ʈ ��ȯ
	if (true == IsShootKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
		return;
	}

	// Ű�� ����������� Idle���·� ��ȯ
	if (false == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_IDLE);
		return;
	}

	// �¿� �̵� ����
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT))
	{
		MoveDir_ = float4::LEFT;

		if (true == GroundLeftCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);
	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT))
	{
		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);
	}


	// ����׿� Ű
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DEBUG_UP))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * DeltaTime_ * 10);

	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DEBUG_DOWN))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_ * 10);
	}
}


void Commando::ShootUpdate(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill1Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill2Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill3Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::Skill4Update(float _DeltaTime, const StateInfo& _Info)
{

}

void Commando::ClimbUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// TODO::���� ������ ����� Climb���� -> Idle�� ��ȯ

	// climb���¿��� ���Ʒ� ����
	if (true == IsUpKeyPress())
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * DeltaTime_);
	}
	if (true == IsDownKeyPress())
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);
	}
}

void Commando::DeathUpdate(float _DeltaTime, const StateInfo& _Info)
{

}


// ��ŸƮ
void Commando::IdleStart(const StateInfo& _Info)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
}

void Commando::MoveStart(const StateInfo& _Info)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_WALK);
}

void Commando::ShootStart(const StateInfo& _Info)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SHOOT);
}

void Commando::Skill1Start(const StateInfo& _Info)
{

}

void Commando::Skill2Start(const StateInfo& _Info)
{

}

void Commando::Skill3Start(const StateInfo& _Info)
{

}

void Commando::Skill4Start(const StateInfo& _Info)
{

}

void Commando::ClimbStart(const StateInfo& _Info)
{
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_CLIMB);
	IsClimb_ = true;
}

void Commando::DeathStart(const StateInfo& _Info)
{

}


// ����
void Commando::IdleEnd(const StateInfo& _Info)
{

}

void Commando::MoveEnd(const StateInfo& _Info)
{

}

void Commando::ShootEnd(const StateInfo& _Info)
{

}

void Commando::Skill1End(const StateInfo& _Info)
{

}

void Commando::Skill2End(const StateInfo& _Info)
{

}

void Commando::Skill3End(const StateInfo& _Info)
{

}

void Commando::Skill4End(const StateInfo& _Info)
{

}

void Commando::ClimbEnd(const StateInfo& _Info)
{
	IsClimb_ = false;
}

void Commando::DeathEnd(const StateInfo& _Info)
{

}
