#include "PreCompile.h"
#include "Missile.h"
#include "MissileSmokeRenderer.h"

Missile::Missile() 
{
}

Missile::~Missile() 
{
}

void Missile::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_MISSILE, FrameAnimation_DESC(TEX_EFFECT_MISSILE, ANIMATION_FRAME_DELAY, true));
	Renderer_->ChangeFrameAnimation(TEX_EFFECT_MISSILE);
	Renderer_->ScaleToTexture();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 32.0f, 6.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
}

void Missile::Update(float _DeltaTime)
{
	// n초마다 스모크 이펙트 생성
	if (this->GetAccTime() > 0.01)
	{
		this->ReSetAccTime();

		CreateComponent<MissileSmokeRenderer>();
	}
}
