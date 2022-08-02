#include "PreCompile.h"
#include "Player.h"

#pragma region FSM Start

void Player::CommonIdleStart()
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_IDLE);
	Renderer_->ScaleToTexture();
}


void Player::CommonMoveStart()
{
	// 애니메이션 전환
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_WALK);
	Renderer_->ScaleToTexture();
}


void Player::CommonShootStart()
{
	// 애니메이션 전환
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

	// 이동키가 눌리면 이동
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
	// 공격키가 눌리면 스테이트 전환
	if (true == IsShootKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_SHOOT);
		return;
	}

	// 키가 떨어졌을경우 Idle상태로 전환
	if (false == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_IDLE);
		return;
	}

	// 좌우 이동 판정
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


	// 디버그용 키
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
	// TODO::밧줄 범위를 벗어나면 Climb상태 -> Idle로 전환

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

	// climb상태에서 위아래 조작
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