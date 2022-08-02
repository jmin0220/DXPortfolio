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


void Player::CommonShootStart()
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_SHOOT);
	Renderer_->ScaleToTexture();
}


void Player::CommonSkill1Start()
{
}


void Player::CommonSkill2Start()
{
}


void Player::CommonSkill3Start()
{
}


void Player::CommonSkill4Start()
{
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
		float4 ColorCenter = ColMap_->GetPixel(ColorCheckPos_.ix(), ColorCheckPos_.iy());

		if (true == ColorCenter.CompareInt4D({ 0.0f, 1.0f, 0.0f }))
		{

			std::string r = std::to_string(ColorCenter.r);
			std::string g = std::to_string(ColorCenter.g);
			std::string b = std::to_string(ColorCenter.b);
			std::string x = std::to_string(this->GetTransform().GetWorldPosition().ix());
			std::string y = std::to_string(-this->GetTransform().GetWorldPosition().iy());

			GameEngineDebug::OutPutString("ChangeClimb----------------------------------------------");
			GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);
			GameEngineDebug::OutPutString("POS > " + x + ", " + y);

			StateManager_.ChangeState(PLAYER_STATE_CLIMB);
		}

		return;
	}
}


void Player::CommonMoveUpdate()
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

	// Climb
	if (true == IsUpKeyPress())
	{
		float4 ColorCenter = ColMap_->GetPixel(ColorCheckPos_.ix(), ColorCheckPos_.iy());

		if (true == ColorCenter.CompareInt4D({ 0.0f, 1.0f, 0.0f }))
		{
			//std::string r = std::to_string(ColorCenter.r);
			//std::string g = std::to_string(ColorCenter.g);
			//std::string b = std::to_string(ColorCenter.b);
			//std::string x = std::to_string(this->GetTransform().GetWorldPosition().x);
			//std::string y = std::to_string(-this->GetTransform().GetWorldPosition().y);

			//GameEngineDebug::OutPutString("ChangeClimb###############################################");
			//GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);
			//GameEngineDebug::OutPutString("POS > " + x + ", " + y);

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


void Player::CommonShootUpdate()
{
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
	// TODO::���� ������ ����� Climb���� -> Idle�� ��ȯ

	float4 ColorCenter = ColMap_->GetPixel(ColorCheckPos_.ix(), ColorCheckPos_.iy());

	if (false == ColorCenter.CompareInt4D({ 0.0f, 1.0f, 0.0f }))
	{

		//std::string r = std::to_string(ColorCenter.r);
		//std::string g = std::to_string(ColorCenter.g);
		//std::string b = std::to_string(ColorCenter.b);
		//std::string x = std::to_string(this->GetTransform().GetWorldPosition().x);
		//std::string y = std::to_string(-this->GetTransform().GetWorldPosition().y);

		//GameEngineDebug::OutPutString("ChangeIdle----------------------------------------------");
		//GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);
		//GameEngineDebug::OutPutString("POS > " + x + ", " + y);

		StateManager_.ChangeState(PLAYER_STATE_IDLE);

		return;
	}

	//std::string r = std::to_string(ColorCenter.r);
	//std::string g = std::to_string(ColorCenter.g);
	//std::string b = std::to_string(ColorCenter.b);
	//std::string x = std::to_string(this->GetTransform().GetWorldPosition().x);
	//std::string y = std::to_string(-this->GetTransform().GetWorldPosition().y);

	//GameEngineDebug::OutPutString("StateCLimb====================================================");
	//GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);
	//GameEngineDebug::OutPutString("POS > " + x + ", " + y);

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


void Player::CommonShootEnd()
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