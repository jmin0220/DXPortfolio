#include "PreCompile.h"
#include "Commando.h"

// ������Ʈ
void Commando::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsShootKeyDown())
	{
		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
		return;
	}


	// �̵�Ű�� ������ �̵�
	if (true == IsMoveKeyDown())
	{
		StateManager_.ChangeState(PLAYER_STATE_MOVE);
		return;
	}
}


void Commando::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	// Ű�� ����������� Idle���·� ��ȯ
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

		// TODO::�ȼ�üũ�Լ� ������ ������
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT))
	{
		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

		// TODO::�ȼ�üũ�Լ� ������ ������
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
	Renderer_->AnimationBindEnd(PLAYER_ANIM_SHOOT, &Commando::EndAnimation, this);
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

}

void Commando::DeathEnd(const StateInfo& _Info)
{

}
