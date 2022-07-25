#include "PreCompile.h"
#include "Player.h"

// ������Ʈ
void Player::IdleUpdate()
{
	if (true == IsShootKeyDown())
	{
		StateChange(STATE::SHOOT);
		return;
	}


	// �̵�Ű�� ������ �̵�
	if (true == IsMoveKeyDown())
	{
		StateChange(STATE::Move);
		return;
	}
}


void Player::MoveUpdate()
{
	// Ű�� ����������� Idle���·� ��ȯ
	if (false == IsMoveKeyPress())
	{
		StateChange(STATE::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * DeltaTime_);

		// TODO::�ȼ�üũ�Լ� ������ ������
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

		// TODO::�ȼ�üũ�Լ� ������ ������
		MoveDir_ = float4::RIGHT;
	}
}


void Player::JumpUpdate()
{

}
void Player::ShootUpdate()
{

}
void Player::Skill1Update()
{

}
void Player::Skill2Update()
{

}
void Player::Skill3Update()
{

}
void Player::Skill4Update()
{

}
void Player::ClimbUpdate()
{

}
void Player::DeathUpdate()
{

}


// ��ŸƮ
void Player::IdleStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_IDLE);
}

void Player::MoveStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_WALK);
}

void Player::JumpStart()
{

}

void Player::ShootStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SHOOT);
	Renderer_->AnimationBindEnd(PLAYER_ANIM_BANDIT_SHOOT, &Player::EndAnimation, this);
}

void Player::Skill1Start()
{

}

void Player::Skill2Start()
{

}

void Player::Skill3Start()
{

}

void Player::Skill4Start()
{

}

void Player::ClimbStart()
{

}

void Player::DeathStart()
{

}


// ����
void Player::IdleEnd()
{

}
void Player::MoveEnd()
{

}
void Player::JumpEnd()
{

}
void Player::ShootEnd()
{

}
void Player::Skill1End()
{

}
void Player::Skill2End()
{

}
void Player::Skill3End()
{

}
void Player::Skill4End()
{

}
void Player::ClimbEnd()
{

}
void Player::DeathEnd()
{

}
