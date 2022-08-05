#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineRandom.h>

Monster::Monster() 
	: Renderer_(nullptr)
	, JumpSpeed_(0.f)
	, FallSpeed_(270.f)
	, DeltaTime_(0.0f)
	, FrameAnimDelay_(0.06f)
{
}

Monster::~Monster() 
{
}

void Monster::Start()
{
	// �ִϸ��̼� �ʱ�ȭ
	AnimationInit();

	// ������Ʈ �ʱ�ȭ
	StateInit();
}

void Monster::Update(float _DeltaTime)
{
	DeltaTime_ = _DeltaTime;

	// �ȼ��ʰ��� �浹ó��
	GroundFallCheck();

	JumpUpdate();

	// ������Ʈ ������Ʈ
	StateManager_.Update(_DeltaTime);

	// �¿���� üũ
	CheckNegativeX();
}

void Monster::CheckNegativeX()
{
	if (MoveDir_.CompareInt3D(float4::LEFT))
	{
		// �¿����
		Renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	// TODO::�ִϸ��̼��� �����ӿ� ���� �Ǻ����� ������ �ʿ� ����.
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

void Monster::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// �ϴ� �߾�
	float4 ColorDown = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// �ϴ� ����
	float4 ColorDownLeft = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// �ϴ� ����
	float4 ColorDownRight = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	// �ϴ� 3���� ��� ���� ���� �ʾƾ� �ٴ�����
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
			// ���� ��ĭ �ø�
			this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

			// �ø����� �ȼ� ���
			// �ϴ� �߾�
			ColorDown = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownLeft = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownRight = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

			// ���� ���� �ö������ Ż��
			if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
				)
			{
				// �ٽ� ��ĭ ����
				this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
				break;
			}
		}
	}
}

bool Monster::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ������ �ߴ�
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// ������ �ϴ�
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

bool Monster::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ���� �ߴ�
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// ���� �ϴ�
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


void Monster::MonsterJump()
{
	// ���� ����ִ� ��쿡�� ���� ����
	if (true == IsGround_)
	{
		IsGround_ = false;
		JumpSpeed_ = -150.0f;
	}
}

#pragma region Common FSM Function


void Monster::CommonIdleStart(std::string _AnimName)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonMoveStart(std::string _AnimName)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonAttackStart(std::string _AnimName)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonChaseStart(std::string _AnimName)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonDeathStart(std::string _AnimName)
{
	// �ִϸ��̼� ��ȯ
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->ScaleToTexture();
}

void Monster::CommonIdleUpdate()
{
	ToMoveGauge_ += DeltaTime_;

	if (ToMoveGauge_ >= 3.0f)
	{
		// Idle���� Move�� ��ȯ�ɶ� ������ ��������
		MoveDirFlg_ = GameEngineRandom::MainRandom.RandomInt(0, 1);
		StateManager_.ChangeState(MONSTER_FSM_MOVE);
		ToMoveGauge_ = 0.0f;
	}
}

void Monster::CommonMoveUpdate()
{
	ToIdleGauge_ += DeltaTime_;

	if (ToIdleGauge_ >= 3.0f)
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

#pragma endregion