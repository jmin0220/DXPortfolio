#include "PreCompile.h"
#include "Player.h"
#include "Stage1Level.h"
#include "HUD.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(100.0f)
	, JumpSpeed_(0.f)
	, FallSpeed_(270.f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
	, IsGround_(false)
	, IsClimb_(false)
	, MoveDir_(float4::RIGHT)
	, FrameAnimDelay_(0.06f)
	, ColorCheckPos_(float4::ZERO)
	, Lv_(1)
	, Exp_(0)
	, Gold_(0)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// Ű���� �ʱ�ȭ
	KeyInit();
	// �ִϸ��̼� �ʱ�ȭ
	AnimationInit();
	// ������Ʈ �ʱ�ȭ
	StateInit();

	HUD_ = GetLevel()->CreateActor<HUD>();
}

void Player::Update(float _DeltaTime)
{
	ColorCheckPos_ = { this->GetTransform().GetWorldPosition().x
			        , -this->GetTransform().GetWorldPosition().y };

	// ��ŸŸ�� �ʱ�ȭ
	DeltaTime_ = _DeltaTime;

	// Ÿ�̸� ����
	AtkTimer_ += DeltaTime_;

	// �ȼ��ʰ��� �浹ó��
	GroundFallCheck();

	// �����Է�
	JumpUpdate();

	// ������Ʈ ������Ʈ
	StateManager_.Update(DeltaTime_);

	// �¿���� üũ
	CheckNegativeX();

	// ī�޶� ������Ʈ
	CameraUpdate();
}

void Player::KeyInit()
{
	if (false == GameEngineInput::GetInst()->IsKey(PLAYER_KEY_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_RIGHT, VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_JUMP, VK_SPACE);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DOWN, VK_DOWN);

		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL1, 'Z');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL2, 'X');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL3, 'C');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL4, 'V');


		// TODO::����׿� �����̵�
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_DOWN, 'S');
	}
}


#pragma region KeyInputFunctions

// �̵�Ű ����
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_RIGHT) 
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT) 
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_RIGHT) 
		)
	{
		return false;
	}

	return true;
}

// ����Ű ����
bool Player::IsJumpKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_JUMP))
	{
		return false;
	}

	return true;
}

bool Player::IsJumpKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_JUMP))
	{
		return false;
	}

	return true;
}

bool Player::IsJumpKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_JUMP))
	{
		return false;
	}

	return true;
}

// ���� ����Ű(Climb)
bool Player::IsUpKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

bool Player::IsUpKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

bool Player::IsUpKeyUp()
{

	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_UP))
	{
		return false;
	}

	return true;
}

// �Ʒ��� ����Ű(Climb)
bool Player::IsDownKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}

bool Player::IsDownKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}

bool Player::IsDownKeyUp()
{

	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_DOWN))
	{
		return false;
	}

	return true;
}


// Skill1Ű ����
bool Player::IsSkill1KeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(Player_KEY_SKILL1))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill1KeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(Player_KEY_SKILL1))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill1KeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(Player_KEY_SKILL1))
	{
		return false;
	}

	return true;
}

// Skill2Ű ����
bool Player::IsSkill2KeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(Player_KEY_SKILL2))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill2KeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(Player_KEY_SKILL2))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill2KeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(Player_KEY_SKILL2))
	{
		return false;
	}

	return true;
}

// Skill3Ű ����
bool Player::IsSkill3KeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(Player_KEY_SKILL3))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill3KeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(Player_KEY_SKILL3))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill3KeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(Player_KEY_SKILL3))
	{
		return false;
	}

	return true;
}

// Skill2Ű ����
bool Player::IsSkill4KeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(Player_KEY_SKILL4))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill4KeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(Player_KEY_SKILL4))
	{
		return false;
	}

	return true;
}

bool Player::IsSkill4KeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(Player_KEY_SKILL4))
	{
		return false;
	}

	return true;
}
#pragma endregion


void Player::CheckNegativeX()
{
	if (true == IsClimb_)
	{
		return;
	}

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

// ī�޶� �̵� ������Ʈ
void Player::CameraUpdate()
{
	float4 PlayerPos = this->GetTransform().GetLocalPosition();

	// ī�޶� ����
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ PlayerPos.x, PlayerPos.y });
}

// �ð��� ���� ���� ���ǵ� �� ����
void Player::JumpUpdate()
{
	if (true == IsJumpKeyDown())
	{
		PlayerJump();
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

// ���� ���ǵ� �Է�
void Player::PlayerJump()
{
	if (true == IsGround_)
	{
		GameEngineDebug::OutPutString("IsGround_ True");
	}
	else
	{
		GameEngineDebug::OutPutString("IsGround_ False");
	}

	// ���� ����ִ� ��쿡�� ���� ����
	if (true == IsGround_)
	{
 		IsGround_ = false;
		JumpSpeed_ = Player_JUMP_SPEED;
	}

	// Climb�����̸鼭 ����Ű�� �Է����� ��쿡�� ���� ����
	if (true == IsClimb_ &&
		true == IsMoveKeyPress())
	{
		StateManager_.ChangeState(PLAYER_STATE_IDLE);

		IsGround_ = false;
		JumpSpeed_ = Player_JUMP_SPEED;
	}
}

// �ϴ� �浹 üũ �� �߷�ó��
void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// �ٿ� Ÿ�� ������ �߷��� ���� ����
	if (true == IsClimb_)
	{
		return;
	}

	// �ϴ� �߾�
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// �ϴ� ����
	float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// �ϴ� ����
	float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
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
			ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// �ϴ� ����
			ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
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
// ĳ���� ������ �� �浹 üũ
bool Player::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ������ �ߴ�
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// ������ �ϴ�
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	return true;
}

// ĳ���� ���� �� �浹 üũ
bool Player::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ���� �ߴ�
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// ���� �ϴ�
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	return true;
}

// ����Ÿ�� ���� �Լ�
bool Player::CanClimb(int _CheckPosFlg)
{
	// int _CheckPosFlg
	// 0 = Top
	// 1 = Center
	// 2 = Bottom

	switch (_CheckPosFlg)
	{
	case 0:
	{
		float4 Color[4] = {};

		// ������ 4�ȼ��� ��� �������� ��Ÿ��
		Color[0] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix(), ColorCheckPos_.iy() - Renderer_->GetCurTexture()->GetScale().hiy());
		Color[1] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() - 1, ColorCheckPos_.iy() - Renderer_->GetCurTexture()->GetScale().hiy());
		Color[2] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 1, ColorCheckPos_.iy() - Renderer_->GetCurTexture()->GetScale().hiy());
		Color[3] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 2, ColorCheckPos_.iy() - Renderer_->GetCurTexture()->GetScale().hiy());

		if (true == Color[0].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[1].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[2].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[3].CompareInt4D({ 0.0f, 1.0f, 0.0f }))
		{
			return true;
		}

		return false;
	}
		break;
	case 1:
	{
		float4 Color[4] = {};

		// ������ 4�ȼ��� ��� �������� ��Ÿ��
		Color[0] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix(), ColorCheckPos_.iy());
		Color[1] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() - 1, ColorCheckPos_.iy());
		Color[2] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 1, ColorCheckPos_.iy());
		Color[3] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 2, ColorCheckPos_.iy());

		if (true == Color[0].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[1].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[2].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[3].CompareInt4D({ 0.0f, 1.0f, 0.0f }))
		{
			return true;
		}

		return false;
	}
		break;
	case 2:
	{
		float4 Color[4] = {};

		// ������ 4�ȼ��� ��� �������� ��Ÿ��
		Color[0] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix(), ColorCheckPos_.iy() + Renderer_->GetCurTexture()->GetScale().hiy());
		Color[1] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() - 1, ColorCheckPos_.iy() + Renderer_->GetCurTexture()->GetScale().hiy());
		Color[2] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 1, ColorCheckPos_.iy() + Renderer_->GetCurTexture()->GetScale().hiy());
		Color[3] = ColMap_->GetPixelToFloat4(ColorCheckPos_.ix() + 2, ColorCheckPos_.iy() + Renderer_->GetCurTexture()->GetScale().hiy());

		if (true == Color[0].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[1].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[2].CompareInt4D({ 0.0f, 1.0f, 0.0f }) &&
			true == Color[3].CompareInt4D({ 0.0f, 1.0f, 0.0f }))
		{
			return true;
		}

		return false;
	}
		break;
	default:
		return false;
		break;
	}
}