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
int Player::MaxExp_ = 100;
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
	if ("STAGE2" == this->GetLevel()->GetNameCopy())
	{
		HUD_->OffActors();
		HUD_->Off();
		this->Off();
	}

	this->SetLevelOverOn();
	HUD_->SetLevelOverOn();
	HUD_->ActorAllOverLevel();

	if (UseItem_ != nullptr)
	{
		UseItem_->SetLevelOverOn();
	}

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
	// 키조작 초기화
	KeyInit();
	// 애니메이션 초기화
	AnimationInit();
	// 스테이트 초기화
	StateInit();
	// 최종적으로 적용될 스테이터스의 초기화
	PlayerBuffStatusInit();
	// 공통적으로 해야하는 초기화
	PlayerCommonInit();

}

void Player::Update(float _DeltaTime)
{
	PlayerStatus::AddFrameStatusToTrueStatus(); // -> 프레임스탯을 적용

	ColorCheckPos_ = { this->GetTransform().GetWorldPosition().x
			        , -this->GetTransform().GetWorldPosition().y };

	// 델타타임 초기화
	DeltaTime_ = _DeltaTime;

	// 플레이 타이머
	PlayTimeTimer_ += DeltaTime_;

	// 타이머 측정
	AtkTimer_ += DeltaTime_;

	// 픽셀맵과의 충돌처리
	GroundFallCheck();

	// 점프입력
	JumpUpdate();

	// 스테이트 업데이트
	StateManager_.Update(DeltaTime_);

	// 좌우반전 체크
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

	// 레벨업 체크
	PlayerLevelUp();

	// 아이템 사용체크
	PlayerUseItem();

	// 카메라 업데이트
	CameraUpdate();

	// 카메라 흔들기 이펙트
	CommonFunction::CommonFunction_->CameraShakeEffect(GetLevel()->GetMainCameraActor());

	// 각 캐릭터가 가지고 있는 업데이트 수치
	CharacterUpdate(DeltaTime_);

	PlayerStatus::ResetFrameStatus(); // -> 프레임스탯을 초기화
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

		// TODO::디버그용 상하이동
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
	// UI 관련
	HUD_ = GetLevel()->CreateActor<HUD>();

	// 레벨업 이펙트
	LevelUpEffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LevelUpEffectRenderer_->CreateFrameAnimationFolder(TEX_INTERFACE_LEVELUP_START, FrameAnimation_DESC(TEX_INTERFACE_LEVELUP_START, 0.04, false));
	LevelUpEffectRenderer_->CreateFrameAnimationFolder(TEX_INTERFACE_LEVELUP_END, FrameAnimation_DESC(TEX_INTERFACE_LEVELUP_END, 0.04, true));
	
	LevelUpEffectRenderer_->AnimationBindFrame(TEX_INTERFACE_LEVELUP_START, [&](const FrameAnimation_DESC& _Desc)
		{
			// 마지막프레임에서 대기
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

// 이동키 판정
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

// 점프키 판정
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

// 위쪽 방향키(Climb)
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

// 아래쪽 방향키(Climb)
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


// Skill1키 판정
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

// Skill2키 판정
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

// Skill3키 판정
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

// Skill2키 판정
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
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
	}

	Renderer_->SetPivot(PIVOTMODE::CENTER);
}

// 카메라 이동 업데이트
void Player::CameraUpdate()
{
	float4 PlayerPos = this->GetTransform().GetLocalPosition();

	// 카메라 추적
	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ PlayerPos.x, PlayerPos.y, -1700 });


	// 카메라가 맵 범위를 벗어났을경우 재위치
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

// 시간에 따른 점프 스피드 값 조정
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

// 점프 스피드 입력
void Player::PlayerJump()
{
	if (true == IsGround_)
	{
		std::string tmp = "IsGround_ True" + std::to_string(this->GetTransform().GetWorldPosition().y);
		GameEngineDebug::OutPutString(tmp.c_str());
	}
	else
	{
		std::string tmp = "IsGround_ False" + std::to_string(this->GetTransform().GetWorldPosition().y);
		GameEngineDebug::OutPutString(tmp.c_str());
	}

	// 땅에 닿아있는 경우에만 점프 가능
	if (true == IsGround_)
	{
 		IsGround_ = false;
		JumpSpeed_ = Player_JUMP_SPEED;
	}

	// Climb상태이면서 방향키를 입력중일 경우에도 점프 가능
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
	// 레벨업
	if (Exp_ >= MaxExp_)
	{
		GameEngineSound::SoundPlayOneShot("wLevelUp.wav");
		Lv_++;

		Exp_ = 0;

		PlayerStatus::BaseDamage_ += this->LvPerDamage_;
		PlayerStatus::BaseHp_ = this->LvPerHp_;
		PlayerStatus::ResetStatus();

		// 레벨업 이펙트
		LevelUpEffectRenderer_->On();

		HUD_->SetLevelFont(Lv_);

		// 레벨업된 스탯으로 버프아이템 재설정
		for (Item* tmpItem : ItemVector_)
		{
			tmpItem->BuffItemUpdate();
		}

		// 레벨업이 있을때 발생할 아이템
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

// 하단 충돌 체크 후 중력처리
void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 줄에 타고 있으면 중력을 받지 않음
	if (true == IsClimb_)
	{
		return;
	}

	//// 하단 중앙
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 좌측
	float4 ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 4
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
	// 하단 우측
	float4 ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 4
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

	PixelColor Magenta;
	Magenta.r = 255, Magenta.g = 0, Magenta.b = 255, Magenta.a = 255;

	// 하단 3점이 모두 땅에 닿지 않아야 바닥으로
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
		false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
		)
	{
		IsGround_ = false;

		GetTransform().SetWorldMove(GetTransform().GetDownVector() * JumpSpeed_ * DeltaTime_ * 2);

		std::string tmp = "IsGround_ False , " + std::to_string(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()) 
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_)

			+ "," + std::to_string(this->GetTransform().GetWorldPosition().ix() + 4)
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_)

			+ "," + std::to_string(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 4)
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		GameEngineDebug::OutPutString(tmp.c_str());
	}
	else
	{
		std::string tmp = "IsGround_ True , " + std::to_string(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix())
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_)

			+ "," + std::to_string(this->GetTransform().GetWorldPosition().ix() + 4)
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_)

			+ "," + std::to_string(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 4)
			+ "," + std::to_string(-this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
		GameEngineDebug::OutPutString(tmp.c_str());
		IsGround_ = true;

		for (int i = 0; i < 3; i++)
		{
			// 위로 한칸 올림
			this->GetTransform().SetWorldUpMove(1.0f, DeltaTime_);

			// 올린뒤의 픽셀 취득
			// 하단 중앙
			ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 좌측
			ColorDownLeft = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);
			// 하단 우측
			ColorDownRight = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix() - 2
				, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + JumpSpeed_ * DeltaTime_);

			// 가장 위로 올라왔으면 탈출
			if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownLeft.CompareInt4D({ 1.0f, 0.0f, 1.0f }) &&
				false == ColorDownRight.CompareInt4D({ 1.0f, 0.0f, 1.0f })
				)
			{
				// 다시 한칸 내림
				this->GetTransform().SetWorldDownMove(1.0f, DeltaTime_);
				break;
			}
		}
	}
}

// 캐릭터 오른쪽 맵 충돌 체크
bool Player::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 오른쪽 중단
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// 오른쪽 하단
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

// 캐릭터 왼쪽 맵 충돌 체크
bool Player::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 왼쪽 중단
	{
		float4 Color = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix()
			, -this->GetTransform().GetWorldPosition().iy());

		if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			return false;
		}
	}

	// 왼쪽 하단
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

// 밧줄타기 판정 함수
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

		// 밧줄의 4픽셀이 모두 겹쳐져야 줄타기
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

		// 밧줄의 4픽셀이 모두 겹쳐져야 줄타기
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

		// 밧줄의 4픽셀이 모두 겹쳐져야 줄타기
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
	// 총알이 생성되는 순간 실행
	for (Item* tmp : ItemVector_)
	{
		tmp->AtkItemUpdate(this->GetTransform().GetWorldPosition());
	}

	static int YposLevel = 0;

	int tmp = GameEngineRandom::MainRandom.RandomInt(Lv_ * 0, Lv_ * 3);
	int TrueDmg = (PlayerStatus::Damage_ + tmp) * _DmgRatio;

	switch (_BulletType)
	{
	case BulletType::Bullet:
	{
		Bullet* bullet = GetLevel()->CreateActor<Bullet>();

		// 크리티컬 찬스
		if (PlayerStatus::CritChance_ >= GameEngineRandom::MainRandom.RandomInt(0, 100))
		{
			bullet->SetCritFlgTrue();
			TrueDmg *= 1.5f;

			GameEngineSound::SoundPlayOneShot("wCrit.wav");
		}
		else
		{
			GameEngineSound::SoundPlayOneShot("wBullet1.wav");
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

		// 크리티컬 찬스
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

	// 이번 애니메이션에서 총알을 모두 쏨
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
		// 해당아이템을 이미 습득한 적이 있는경우
		if (_Item->GetItemName() == tmpItem->GetItemName())
		{
			// 카운터를 올리고
			tmpItem->AddOverlapCounter();
			OverlapFlg = true;
			// 추가로 생성된 아이템을 삭제
			_Item->Death(3.0f);
		}
	}

	if (false == OverlapFlg)
	{
		// 해당 아이템을 습득한 적이 없는 경우에는 ItemVector에 추가
		ItemVector_.push_back(_Item);
	}

	// 버프 아이템은 습득하자마자 업데이트를 진행함
	PlayerStatus::ResetStatus();
	for (Item* tmpItem : ItemVector_)
	{
		tmpItem->BuffItemUpdate();
	}

	AddItemFlg_ = true;

	return;
}