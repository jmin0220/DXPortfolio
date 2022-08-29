#include "PreCompile.h"
#include "Exp.h"
#include "Player.h"

Exp::Exp() 
{
}

Exp::~Exp() 
{
}

void Exp::SetDestPos(float4 _DestPos)
{
	DestPos_.x = this->GetTransform().GetWorldPosition().x + _DestPos.x;
	DestPos_.y = this->GetTransform().GetWorldPosition().y + _DestPos.y;

	this->GetTransform().SetWorldPosition(DestPos_);
}

void Exp::Start()
{
	// 경험치는 중력의 영향을 받지 않음.

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_NORMAL_EXP, FrameAnimation_DESC(TEX_EFFECT_NORMAL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_SMALL_EXP, FrameAnimation_DESC(TEX_EFFECT_SMALL_EXP, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_DEATH_EXP, FrameAnimation_DESC(TEX_EFFECT_DEATH_EXP, ANIMATION_FRAME_DELAY, true));

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_SMALL_EXP);
}

void Exp::Update(float _DeltaTime)
{
	PlayerChaseTimer_ += _DeltaTime;

	if (PlayerChaseTimer_ <= 0.5f)
	{
		return;
	}
	else
	{
	// 오브젝트가 플레이어에게 충분히 근접했다면
	if (false == ChasePlayer())
	{
		// 플레이어에 골드 추가
		Player::AddExp(ExpValue_);

		// 오브젝트 삭제
		this->Death();

		return;
	}
	}

	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// 오브젝트가 충분히 근접함
	if (FlyDir_.Length() <= 10)
	{
		// 플레이어에 골드 추가
		Player::AddExp(ExpValue_);

		// 오브젝트 삭제
		this->Death();

		return;
	}
}

bool Exp::ChasePlayer()
{
	// 플레이어 위치로 방향을 설정
	FlyDir_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

	// 오브젝트가 충분히 근접함
	if (FlyDir_.Length() <= 10.0f)
	{
		return false;
	}
	// 오브젝트가 충분히 근접하지 못함
	else
	{
		FlyDir_.Normalize();

		// 플레이어를 향해 이동
		// TODO::Sin곡선으로 날아가야하지 않나?
		this->GetTransform().SetWorldMove(FlyDir_ * GameEngineTime::GetDeltaTime() * 300.0f);
		return true;
	}
}