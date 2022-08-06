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

	ChaseFlgUpdate();

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

void Monster::ChaseFlgUpdate()
{
	// �� ������ �Ÿ��� ������ ������ ������ chase���·� ��ȯ
	// ChaseFlg�� false�� ��ȯ���� ����
	if (false == ChaseFlg_)
	{
		// ���Ϳ� �÷��̾� ������ �Ÿ��� ���
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
	// ���� ����ִ� ��쿡�� ���� ����
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

// TODO::ĳ���͵��� �Ǻ��� �����Ǹ� �浹������ ��ġ�� �Բ� ������ ��.
bool Monster::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ������ �ϴ�
	// �ٴ��� ������ ����
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// ������ �ߴ�
	// ���� ���� ������ ����
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
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ���� �ϴ�
	// �ٴ��� ������ ����
	{
		float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1);

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return true;
		}
	}

	// ���� �ߴ�
	// ���� ���� ������ ����
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
		// Idle���� Move�� ��ȯ�ɶ� ������ ��������
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

	// ���������� 
	if (MonsterPos.x <= PlayerPos_.x)
	{
		MoveDir_ = float4::RIGHT;

		if (true == GroundRightCheck())
		{
			return;
		}

		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * DeltaTime_);

	}
	// ��������
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