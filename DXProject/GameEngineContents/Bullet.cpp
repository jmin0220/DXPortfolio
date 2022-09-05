#include "PreCompile.h"
#include "Bullet.h"
#include "Monster.h"
#include "ContentsFont.h"

Bullet::Bullet() 
	: Collision_(nullptr)
	, Renderer_(nullptr)
	, BulletDeathFlg_(false)
	, BulletYPositionLevel_(0)
	, BulletSpeed_(3000)
{
}

Bullet::~Bullet() 
{
}

void Bullet::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 10.0f, 10.0f, 1.0f });
}

void Bullet::Update(float _DeltaTime)
{
	// 총알의 파괴애니메이션이 출력중이면 더이상 업데이트하지 않음.
	if (true == BulletDeathFlg_)
	{
		return;
	}

	if (Direction_.CompareInt3D(float4::LEFT))
	{
		this->GetTransform().SetWorldMove(GetTransform().GetLeftVector() * _DeltaTime * BulletSpeed_);
		FlyLength_ += GetTransform().GetRightVector().x * _DeltaTime * BulletSpeed_;
	}
	else
	{
		this->GetTransform().SetWorldMove(GetTransform().GetRightVector() * _DeltaTime * BulletSpeed_);
		FlyLength_ += GetTransform().GetLeftVector().x * _DeltaTime * BulletSpeed_;
	}

	// 일정거리 이상 날아가면 파괴
	if (std::abs(FlyLength_) >= 800.0f)
	{
		BulletDeath();
	}
	else
	{
		Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
			, std::bind(&Bullet::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
}

bool Bullet::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->HitFunction(Damage_);
	TmpMonster->ChangeStateToHitted();

	// 데미지 폰트 출력
	DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	if (true == CirtFlg_)
	{
		DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f * BulletYPositionLevel_ }, TextType::Crit);
	}
	else
	{
		DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f * BulletYPositionLevel_ });
	}
	DamageFont_->GetTransform().SetWorldPosition({this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y});
	DamageFont_->SetIsBulletDmg(true);

	DamageFont_->SetDeathTimer(1.0f);

	BulletDeath();

	return false;
}

void Bullet::CheckNegativeX()
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

void Bullet::BulletDeath()
{
	BulletDeathFlg_ = true;
	Collision_->Off();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->SetSamplingModePoint();
	// TODO::총알파괴 애니메이션을 외부에서 Set할 수 있도록 수정
	Renderer_->CreateFrameAnimationFolder(EFFECT_ANIM_NORMAL_SPARK, FrameAnimation_DESC(TEX_EFFECT_NORMAL_SPARK, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(EFFECT_ANIM_NORMAL_SPARK);
	Renderer_->AnimationBindEnd(EFFECT_ANIM_NORMAL_SPARK, [=](const FrameAnimation_DESC&) {	this->Death(); });
	Renderer_->SetScaleModeImage();
	Renderer_->ScaleToTexture();

	if (DamageFont_ != nullptr && false == DamageFont_->GetDeathFlg())
	{
		DamageFont_->Death();
	}

	CheckNegativeX();
}
