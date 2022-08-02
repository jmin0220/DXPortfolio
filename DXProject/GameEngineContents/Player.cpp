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
	, FrameAnimDelay_(0.1f)
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

	HUD_ = GetLevel()->CreateActor<HUD>(ObjectGroup::UI);
}

void Player::Update(float _DeltaTime)
{
	// ��ŸŸ�� �ʱ�ȭ
	DeltaTime_ = _DeltaTime;

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

		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_SHOOT, 'Z');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL1, 'X');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL2, 'C');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL3, 'V');


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

// �߻�Ű ����
bool Player::IsShootKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

bool Player::IsShootKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

bool Player::IsShootKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_SHOOT))
	{
		return false;
	}

	return true;
}

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
#pragma endregion


void Player::CheckNegativeX()
{
	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		// �¿����
		Renderer_->GetTransform().PixLocalNegativeX();
		//Renderer_->SetPivot(PIVOTMODE::RIGHT);
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	// TODO::�ִϸ��̼��� �����ӿ� ���� �Ǻ����� ������ �ʿ� ����.
	Renderer_->SetPivot(PIVOTMODE::LEFT);
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
	// ���� ����ִ� ��쿡�� ���� ����
	if (true == IsGround_)
	{
		IsGround_ = false;
		JumpSpeed_ = -150.0f;
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
	}

	// ����׿� RGB�� ����
	//std::string r = std::to_string(ColorDown.r);
	//std::string g = std::to_string(ColorDown.g);
	//std::string b = std::to_string(ColorDown.b);

	//GameEngineDebug::OutPutString("RGB > " + r + ", " + g + ", " + b);

}

// ĳ���� ������ �� �浹 üũ
bool Player::GroundRightCheck()
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

// ĳ���� ���� �� �浹 üũ
bool Player::GroundLeftCheck()
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