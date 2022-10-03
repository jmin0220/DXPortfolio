#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Stage1Level.h"
#include "HUD.h"
#include "Bullet.h"
#include "PiercingBullet.h"
#include "CommonFunction.h"

float Player::PlayTimeTimer_ = 0.0f;
int Player::Lv_ = 1;
int Player::Hp_ = 0;
int Player::MaxHp_ = 0;
int Player::Gold_ = 999;
int Player::Exp_ = 0;
int Player::MaxExp_ = 50;
std::vector<Item*> Player::ItemVector_ = {};
Item* Player::UseItem_ = nullptr;
bool Player::AddItemFlg_ = false;
bool Player::AddUseItemFlg_ = false;
float4 Player::MoveDir_ = float4::RIGHT;

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(Player_MOVE_SPEED)
	, JumpSpeed_(0.f)
	, FallSpeed_(350.f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
	, IsGround_(false)
	, IsClimb_(false)
	, FrameAnimDelay_(0.06f)
	, ColorCheckPos_(float4::ZERO)
	, CritChance_(5)
{
}

Player::~Player() 
{
}

void Player::LevelEndEvent()
{
	this->SetLevelOverOn();
	HUD_->SetLevelOverOn();
	HUD_->ActorAllOverLevel();
	UseItem_->SetLevelOverOn();

	if (ItemVector_.size() != 0)
	{
		for (Item* tmp : ItemVector_)
		{
			tmp->SetLevelOverOn();
		}
	}
}

void Player::Start()
{
	// Ű���� �ʱ�ȭ
	KeyInit();
	// �ִϸ��̼� �ʱ�ȭ
	AnimationInit();
	// ������Ʈ �ʱ�ȭ
	StateInit();
	// ���������� ����� �������ͽ��� �ʱ�ȭ
	PlayerBuffStatusInit();
	// ���������� �ؾ��ϴ� �ʱ�ȭ
	PlayerCommonInit();

}

void Player::Update(float _DeltaTime)
{
	PlayerStatus::AddFrameStatusToTrueStatus(); // -> �����ӽ����� ����

	ColorCheckPos_ = { this->GetTransform().GetWorldPosition().x
			        , -this->GetTransform().GetWorldPosition().y };

	// ��ŸŸ�� �ʱ�ȭ
	DeltaTime_ = _DeltaTime;

	// �÷��� Ÿ�̸�
	PlayTimeTimer_ += DeltaTime_;

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

	if (true == AddItemFlg_)
	{
		HUD_->AddItemUpdate();
		AddItemFlg_ = false;
	}

	if (true == AddUseItemFlg_)
	{
		HUD_->AddUseItemUpdate();
		AddUseItemFlg_ = false;
	}

	for (Item* tmp : ItemVector_)
	{
		tmp->FrameItemUpdate(this->GetTransform().GetWorldPosition());
	}

	// ������ üũ
	PlayerLevelUp();

	// ������ ���üũ
	PlayerUseItem();

	// ī�޶� ������Ʈ
	CameraUpdate();

	// ī�޶� ���� ����Ʈ
	CommonFunction::CommonFunction_->CameraShakeEffect(GetLevel()->GetMainCameraActor());

	// �� ĳ���Ͱ� ������ �ִ� ������Ʈ ��ġ
	CharacterUpdate(DeltaTime_);

	PlayerStatus::ResetFrameStatus(); // -> �����ӽ����� �ʱ�ȭ
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

		GameEngineInput::GetInst()->CreateKey(Player_KEY_INTERACTIVE, 'A');

		GameEngineInput::GetInst()->CreateKey(Player_KEY_USE_ITEMS, 'G');

		// TODO::����׿� �����̵�
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DEBUG_DOWN, 'S');
	}
}

void Player::PlayerBuffStatusInit()
{
	PlayerStatus::BaseSpeed_ = this->Speed_;
	PlayerStatus::BaseAtkSpeed_ = this->AtkSpeed_;
	PlayerStatus::BaseDamage_ = this->Damage_;
	PlayerStatus::BaseHp_ = this->Hp_;
	PlayerStatus::BaseCritChance_ = this->CritChance_;

	PlayerStatus::ResetStatus();
}

void Player::PlayerCommonInit()
{
	// UI ����
	HUD_ = GetLevel()->CreateActor<HUD>();

	// ������ ����Ʈ
	LevelUpEffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LevelUpEffectRenderer_->CreateFrameAnimationFolder(TEX_INTERFACE_LEVELUP_START, FrameAnimation_DESC(TEX_INTERFACE_LEVELUP_START, 0.04, false));
	LevelUpEffectRenderer_->CreateFrameAnimationFolder(TEX_INTERFACE_LEVELUP_END, FrameAnimation_DESC(TEX_INTERFACE_LEVELUP_END, 0.04, true));
	
	LevelUpEffectRenderer_->AnimationBindFrame(TEX_INTERFACE_LEVELUP_START, [&](const FrameAnimation_DESC& _Desc)
		{
			// �����������ӿ��� ���
			if (_Desc.CurFrame == 7)
			{
				LevelUpEffectRenderer_->AddAccTime(DeltaTime_);

				if (LevelUpEffectRenderer_->GetAccTime() >= 3.0f)
				{
					LevelUpEffectRenderer_->ReSetAccTime();
					LevelUpEffectRenderer_->CurAnimationReset();
					LevelUpEffectRenderer_->ChangeFrameAnimation(TEX_INTERFACE_LEVELUP_END);
				}
			}
		});

	LevelUpEffectRenderer_->AnimationBindEnd(TEX_INTERFACE_LEVELUP_END, [&](const FrameAnimation_DESC&)
		{
			LevelUpEffectRenderer_->ChangeFrameAnimation(TEX_INTERFACE_LEVELUP_START);
			LevelUpEffectRenderer_->Off();
		});

	LevelUpEffectRenderer_->ChangeFrameAnimation(TEX_INTERFACE_LEVELUP_START);
	LevelUpEffectRenderer_->SetSamplingModePoint();
	LevelUpEffectRenderer_->SetScaleModeImage();
	LevelUpEffectRenderer_->SetPivot(PIVOTMODE::CENTER);
	LevelUpEffectRenderer_->Off();

	LevelUpEffectRenderer_->GetTransform().SetWorldMove(GetTransform().GetUpVector() * 40.0f);
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

	Renderer_->SetPivot(PIVOTMODE::CENTER);
}

// ī�޶� �̵� ������Ʈ
void Player::CameraUpdate()
{
	float4 PlayerPos = this->GetTransform().GetLocalPosition();

	// ī�޶� ����
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ PlayerPos.x, PlayerPos.y, -1700 });


	// ī�޶� �� ������ �������� ����ġ
	if (GetLevel()->GetMainCameraActorTransform().GetWorldPosition().x <= GameEngineWindow::GetInst()->GetScale().hx() + 14.0f)
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ GameEngineWindow::GetInst()->GetScale().hx() + 14.0f
			, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().y
			, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().z });
	}
	if (GetLevel()->GetMainCameraActorTransform().GetWorldPosition().x >= ColMap_->GetScale().x - GameEngineWindow::GetInst()->GetScale().hx())
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ ColMap_->GetScale().x - GameEngineWindow::GetInst()->GetScale().hx()
			, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().y
			, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().z });
	}
	if (GetLevel()->GetMainCameraActorTransform().GetWorldPosition().y <= -(ColMap_->GetScale().y + GameEngineWindow::GetInst()->GetScale().hy()))
	{
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ GetLevel()->GetMainCameraActorTransform().GetWorldPosition().x
			, ColMap_->GetScale().y - GameEngineWindow::GetInst()->GetScale().hy()
			, GetLevel()->GetMainCameraActorTransform().GetWorldPosition().z });
	}
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

void Player::PlayerLevelUp()
{
	// ������
	if (Exp_ >= MaxExp_)
	{
		Lv_++;

		Exp_ = 0;

		PlayerStatus::BaseDamage_ += this->LvPerDamage_;
		PlayerStatus::BaseHp_ = this->LvPerHp_;
		PlayerStatus::ResetStatus();

		// ������ ����Ʈ
		LevelUpEffectRenderer_->On();

		HUD_->SetLevelFont(Lv_);

		// �������� �������� ���������� �缳��
		for (Item* tmpItem : ItemVector_)
		{
			tmpItem->BuffItemUpdate();
		}

		// �������� ������ �߻��� ������
		for (Item* tmpItem : ItemVector_)
		{
			tmpItem->LevelUpItemUpdate(this->GetTransform().GetWorldPosition());
		}
	}
}

void Player::PlayerUseItem()
{
	if(GameEngineInput::GetInst()->IsDown(Player_KEY_USE_ITEMS))
	{
		if (nullptr != UseItem_)
		{
			UseItem_->UseItemUpdate(this->GetTransform().GetWorldPosition(), MoveDir_);
		}
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
	float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 4
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// �ϴ� ����
	float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 4
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	// �ϴ� 3���� ��� ���� ���� �ʾƾ� �ٴ�����
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
		)
	{
		IsGround_ = false;

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * JumpSpeed_ * DeltaTime_ * 2);
	}
	else
	{
		IsGround_ = true;

		for (int i = 0; i < 3; i++)
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


void Player::CreateBullet(int _CurFrame, int _LastFrame, BulletType _BulletType, float _DmgRatio, float _PiercingLength)
{
	static int YposLevel = 0;

	int tmp = GameEngineRandom::MainRandom.RandomInt(Lv_ * 0, Lv_ * 3);
	int TrueDmg = (PlayerStatus::Damage_ + tmp) * _DmgRatio;

	switch (_BulletType)
	{
	case BulletType::Bullet:
	{
		Bullet* bullet = GetLevel()->CreateActor<Bullet>();

		// ũ��Ƽ�� ����
		if (PlayerStatus::CritChance_ >= GameEngineRandom::MainRandom.RandomInt(0, 100))
		{
			bullet->SetCritFlgTrue();
			TrueDmg *= 1.5f;
		}

		bullet->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
		bullet->SetDamage(TrueDmg);
		bullet->SetDirection(MoveDir_);
		bullet->SetBulletYPositionLevel(YposLevel);
	}
	break;
	case BulletType::PiercingBullet:
	{
		PiercingBullet* piercingbullet = GetLevel()->CreateActor<PiercingBullet>();

		// ũ��Ƽ�� ����
		if (PlayerStatus::CritChance_ >= GameEngineRandom::MainRandom.RandomInt(0, 100))
		{
			piercingbullet->SetCritFlgTrue();
			TrueDmg *= 1.5f;
		}

		piercingbullet->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
		piercingbullet->SetDamage(TrueDmg);
		piercingbullet->SetDirection(MoveDir_);
		piercingbullet->SetPiercingLength(_PiercingLength);
		piercingbullet->ResizePiercingBulletXSize();
		piercingbullet->SetBulletYPositionLevel(YposLevel);
	}
	break;
	default:
		break;
	}

	YposLevel++;

	// �̹� �ִϸ��̼ǿ��� �Ѿ��� ��� ��
	if (_CurFrame == _LastFrame)
	{
		YposLevel = 0;
	}
}

void Player::AddItem(Item * _Item)
{
	bool OverlapFlg = false;

	for (Item* tmpItem : ItemVector_)
	{
		// �ش�������� �̹� ������ ���� �ִ°��
		if (_Item->GetItemName() == tmpItem->GetItemName())
		{
			// ī���͸� �ø���
			tmpItem->AddOverlapCounter();
			OverlapFlg = true;
			// �߰��� ������ �������� ����
			_Item->Death(3.0f);
		}
	}

	if (false == OverlapFlg)
	{
		// �ش� �������� ������ ���� ���� ��쿡�� ItemVector�� �߰�
		ItemVector_.push_back(_Item);
	}

	// ���� �������� �������ڸ��� ������Ʈ�� ������
	PlayerStatus::ResetStatus();
	for (Item* tmpItem : ItemVector_)
	{
		tmpItem->BuffItemUpdate();
	}

	AddItemFlg_ = true;

	return;
}