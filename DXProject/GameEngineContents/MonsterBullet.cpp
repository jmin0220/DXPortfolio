#include "PreCompile.h"
#include "MonsterBullet.h"
#include "Monster.h"
#include "ContentsFont.h"
#include "Player.h"

MonsterBullet::MonsterBullet()
	: Collision_(nullptr)
	, Renderer_(nullptr)
	, BulletDeathFlg_(false)
	, BulletYPositionLevel_(0)
	, BulletSpeed_(2500)
{
}

MonsterBullet::~MonsterBullet() 
{
}

void MonsterBullet::SetBulletAnim(std::string _AnimName)
{
	Renderer_->CreateFrameAnimationFolder(_AnimName, FrameAnimation_DESC(_AnimName, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(_AnimName);
	Renderer_->AnimationBindEnd(_AnimName, [=](const FrameAnimation_DESC&) {	this->Death(); });
	Renderer_->SetScaleModeImage();
	Renderer_->ScaleToTexture();
}

void MonsterBullet::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::MonsterBullet);
	Collision_->GetTransform().SetWorldScale({ 15.0f, 10.0f, 1.0f });

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	SetBulletAnim(EFFECT_ANIM_NORMAL_SPARK);

	Renderer_->SetSamplingModePoint();
	Renderer_->Off();
}

void MonsterBullet::Update(float _DeltaTime)
{
	// 총알의 파괴애니메이션이 출력중이면 더이상 업데이트하지 않음.
	if (true == BulletDeathFlg_)
	{
		return;
	}

	this->GetTransform().SetWorldMove(Direction_ * _DeltaTime * BulletSpeed_);
	FlyLength_ += Direction_.x * _DeltaTime * BulletSpeed_;

	// 일정거리 이상 날아가면 파괴
	if (std::abs(FlyLength_) >= 800.0f)
	{
		BulletDeath();
	}
	else
	{
		Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
			, std::bind(&MonsterBullet::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
}

void MonsterBullet::CheckNegativeX()
{
	if (Direction_.CompareInt3D(float4::LEFT))
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

CollisionReturn MonsterBullet::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Player* TmpPlayer = dynamic_cast<Player*>(_Other->GetActor());
	TmpPlayer->AddNowHp(-Damage_);
	// 데미지 폰트 출력
	DamageFont_ = GetLevel()->CreateActor<ContentsFont>();
	DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f * BulletYPositionLevel_ });
	DamageFont_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);
	DamageFont_->SetDeathTimer(1.0f);

	BulletDeath();

	return CollisionReturn::Break;
}

void MonsterBullet::BulletDeath()
{
	BulletDeathFlg_ = true;
	Collision_->Off();

	Renderer_->On();

	if (DamageFont_ != nullptr && false == DamageFont_->GetDeathFlg())
	{
		DamageFont_->Death();
	}

	CheckNegativeX();
}
