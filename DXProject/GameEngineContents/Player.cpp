#include "PreCompile.h"
#include "Player.h"
#include "Stage1Level.h"

Player::Player() 
	:Renderer_(nullptr)
	, Speed_(200.0f)
	, DeltaTime_(0.0f)
	, ColMap_(nullptr)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// 키조작 초기화
	KeyInit();
	// 애니메이션 초기화
	AnimationInit();
	// 스테이트 초기화
	StateInit();
}

void Player::Update(float _DeltaTime)
{
	// 델타타임 초기화
	DeltaTime_ = _DeltaTime;

	// 점프입력
	JumpUpdate();

	// 픽셀맵과의 충돌처리
	GroundFallCheck();

	// 스테이트 업데이트
	StateManager_.Update(DeltaTime_);

	// 좌우반전 체크
	CheckNegativeX();

	// 카메라 업데이트
	CameraUpdate();

}

void Player::KeyInit()
{
	if (false == GameEngineInput::GetInst()->IsKey(PLAYER_KEY_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_LEFT, VK_LEFT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_RIGHT, VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_JUMP, VK_SPACE);

		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_SHOOT, 'Z');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL1, 'X');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL2, 'C');
		GameEngineInput::GetInst()->CreateKey(Player_KEY_SKILL3, 'V');


		// TODO::디버그용 상하이동
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_UP, VK_UP);
		GameEngineInput::GetInst()->CreateKey(PLAYER_KEY_DOWN, VK_DOWN);
	}
}


void Player::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_IDLE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_IDLE, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SHOOT, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SHOOT, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_WALK, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_WALK, 0.1f, true));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_JUMP, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_JUMP, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_CLIMB, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_CLIMB, 0.1f, false));
	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_DEATH, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_DEATH, 0.1f, false));

	//Renderer_->GetTransform().SetLocalScale({ 66, 30 });
	//Renderer_->CreateFrameAnimationFolder("BanditShoot2", FrameAnimation_DESC("BanditShoot2", 0.1f));
	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_IDLE);
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::LEFT);
}

void Player::StateInit()
{
	StateManager_.CreateStateMember(PLAYER_STATE_IDLE, this, &Player::IdleUpdate, &Player::IdleStart, &Player::IdleEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_MOVE, this, &Player::MoveUpdate, &Player::MoveStart, &Player::MoveEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SHOOT, this, &Player::ShootUpdate, &Player::ShootStart, &Player::ShootEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL1, this, &Player::Skill1Update, &Player::Skill1Start, &Player::Skill1End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL2, this, &Player::Skill2Update, &Player::Skill2Start, &Player::Skill2End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL3, this, &Player::Skill3Update, &Player::Skill3Start, &Player::Skill3End);
	StateManager_.CreateStateMember(PLAYER_STATE_SKILL4, this, &Player::Skill4Update, &Player::Skill4Start, &Player::Skill4End);
	StateManager_.CreateStateMember(PLAYER_STATE_CLIMB, this, &Player::ClimbUpdate, &Player::ClimbStart, &Player::ClimbEnd);
	StateManager_.CreateStateMember(PLAYER_STATE_DEATH, this, &Player::DeathUpdate, &Player::DeathStart, &Player::DeathEnd);
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}

// 이동키 판정
bool Player::IsMoveKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsDown(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsPress(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

bool Player::IsMoveKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_LEFT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_RIGHT) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_UP) &&
		false == GameEngineInput::GetInst()->IsUp(PLAYER_KEY_DOWN)
		)
	{
		return false;
	}

	return true;
}

// 발사키 판정
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

void Player::CheckNegativeX()
{
	if (MoveDir_.CompareInt2D(float4::LEFT))
	{
		// 좌우반전
		Renderer_->GetTransform().PixLocalNegativeX();
		Renderer_->SetPivot(PIVOTMODE::RIGHT);
	}
	else
	{
		Renderer_->GetTransform().PixLocalPositiveX();
		Renderer_->SetPivot(PIVOTMODE::LEFT);
	}
}

void Player::CameraUpdate()
{
	// 카메라 추적
	GetLevel()->GetMainCameraActorTransform().SetLocalPosition(this->GetTransform().GetLocalPosition());
}


void Player::JumpUpdate()
{
	// TODO::점프 기능
}

void Player::GroundFallCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix()
		                          , -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 1.0f);

	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * DeltaTime_);
	}
	else if (false == Color.CompareInt4D(float4::ZERO))
	{
		int a = 0;
	}
}

bool Player::GroundRightCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy());


	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		return false;
	}

	return true;
}

bool Player::GroundLeftCheck()
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	float4 Color = ColMap_->GetPixel(this->GetTransform().GetWorldPosition().ix() - Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy());


	if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		return false;
	}

	return true;
}

void Player::EndAnimation(const FrameAnimation_DESC& _Info)
{
	// 스테이트 전환
	StateManager_.ChangeState(PLAYER_STATE_IDLE);
}
