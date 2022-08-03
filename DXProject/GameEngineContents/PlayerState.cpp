#include "PreCompile.h"
#include "Player.h"

#pragma region FSM Start

void Player::CommonIdleStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->ScaleToTexture();
}


void Player::CommonMoveStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_WALK);
	Renderer_->ScaleToTexture();
}


void Player::CommonSkill1Start()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SKILL1);
	Renderer_->ScaleToTexture();
}


void Player::CommonSkill2Start()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SKILL2);
	Renderer_->ScaleToTexture();
}


void Player::CommonSkill3Start()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SKILL3);
	Renderer_->ScaleToTexture();
}


void Player::CommonSkill4Start()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SKILL4);
	Renderer_->ScaleToTexture();
}


void Player::CommonClimbStart()
{
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_CLIMB);
	Renderer_->ScaleToTexture();
	IsClimb_ = true;
}


void Player::CommonDeathStart()
{
}

#pragma endregion

#pragma region FSM Update

void Player::CommonIdleUpdate()
{
	if (true == IsSkill1KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL1);
		return;
	}

	if (true == IsSkill2KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL2);
		return;
	}
	if (true == IsSkill3KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL3);
		return;
	}
	if (true == IsSkill4KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL4);
		return;
	}

	// �̵�Ű�� ������ �̵�
	if (true == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_MOVE);
	}

	// Climb
	if (true == IsUpKeyPress())
	{
		if (true == CanClimb(1))
		{
			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
	}
	else if (true == IsDownKeyPress())
	{
		if (true == CanClimb(2))
		{
			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
	}
}


void Player::CommonMoveUpdate()
{
	// ����Ű�� ������ ������Ʈ ��ȯ
	if (true == IsSkill1KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL1);
		return;
	}

	if (true == IsSkill2KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL2);
		return;
	}
	if (true == IsSkill3KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL3);
		return;
	}
	if (true == IsSkill4KeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SKILL4);
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

	// Climb
	if (true == IsUpKeyPress())
	{
		if (true == CanClimb(1))
		{
			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
	}
	else if (true == IsDownKeyPress())
	{
		if (true == CanClimb(2))
		{
			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
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

void Player::CommonSkill1Update()
{
}


void Player::CommonSkill2Update()
{
}


void Player::CommonSkill3Update()
{
}


void Player::CommonSkill4Update()
{
}


void Player::CommonClimbUpdate()
{
	// climb���¿��� ���Ʒ� ����
	if (true == IsUpKeyPress())
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * DeltaTime_);
	}
	if (true == IsDownKeyPress())
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);
	}

	// ���� ������ ����� Climb���� -> Idle�� ��ȯ
	if (false == CanClimb(0) && false == CanClimb(2))
	{
		StateManager_.ChangeState(PLAYER_STATE_IDLE);

		return;
	}
}


void Player::CommonDeathUpdate()
{
}
#pragma endregion

#pragma region FSM End

void Player::CommonIdleEnd()
{
}


void Player::CommonMoveEnd()
{
}


void Player::CommonSkill1End()
{
}


void Player::CommonSkill2End()
{
}


void Player::CommonSkill3End()
{
}


void Player::CommonSkill4End()
{
}


void Player::CommonClimbEnd()
{
}


void Player::CommonDeathEnd()
{
}

#pragma endregion