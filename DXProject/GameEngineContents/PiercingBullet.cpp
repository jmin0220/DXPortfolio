#include "PreCompile.h"
#include "PiercingBullet.h"
#include "Monster.h"
#include "ContentsFont.h"
#include <algorithm>
#include "Player.h"

PiercingBullet::PiercingBullet() 
{
}

PiercingBullet::~PiercingBullet() 
{
}

void PiercingBullet::Start()
{
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 10.0f, 10.0f, 1.0f });

	this->Death(0.2f);
}

void PiercingBullet::Update(float _DeltaTime)
{
	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		, std::bind(&PiercingBullet::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}


bool PiercingBullet::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// �̹� �浹������ ������ ����
	if (find(CheckedMonster_.begin(), CheckedMonster_.end(), _Other) != CheckedMonster_.end())
	{
		return false;
	}

	CheckedMonster_.push_back(_Other);

	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->HitFunction(Damage_);
	TmpMonster->ChangeStateToHitted();
	
	CreateHitEffect();

	// �Ѿ� ������ ������Ʈ
	for (Item* tmpItem : Player::ItemVector_)
	{
		tmpItem->BulletItemUpdate(this->GetTransform().GetWorldPosition(), this->CirtFlg_);
	}

	// ������ ��Ʈ ���
	DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	if (true == CirtFlg_)
	{
		DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f * BulletYPositionLevel_ }, TextType::Crit);
	}
	else
	{
		DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f * BulletYPositionLevel_ });
	}
	DamageFont_->GetTransform().SetWorldPosition({ _Other->GetTransform().GetWorldPosition().x, _Other->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);

	DamageFont_->SetDeathTimer(1.0f);


	return false;
}

void PiercingBullet::ChangeCollisionPivot()
{
	float4 thisPos = this->GetTransform().GetWorldPosition();
	if (Direction_.CompareInt3D(float4::LEFT))
	{
		Collision_->GetTransform().SetWorldPosition({ thisPos.x - PiercingLength_ / 2, thisPos.y, thisPos.z });
	}
	else if (Direction_.CompareInt3D(float4::RIGHT))
	{
		Collision_->GetTransform().SetWorldPosition({ thisPos.x + PiercingLength_ / 2, thisPos.y, thisPos.z });
	}
	else if (Direction_.CompareInt3D(float4::ZERO))
	{
		Collision_->GetTransform().SetWorldPosition({ thisPos.x, thisPos.y, thisPos.z });
	}
}

void PiercingBullet::CreateHitEffect()
{
	GameEngineTextureRenderer* EffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	EffectRenderer_->SetSamplingModePoint();
	EffectRenderer_->CreateFrameAnimationFolder(EFFECT_ANIM_NORMAL_SPARK, FrameAnimation_DESC(TEX_EFFECT_NORMAL_SPARK, ANIMATION_FRAME_DELAY, false));
	EffectRenderer_->ChangeFrameAnimation(EFFECT_ANIM_NORMAL_SPARK);
	EffectRenderer_->AnimationBindEnd(EFFECT_ANIM_NORMAL_SPARK, [=](const FrameAnimation_DESC&) {	this->Death(); });
	EffectRenderer_->SetScaleModeImage();
	EffectRenderer_->ScaleToTexture();

	if (DamageFont_ != nullptr && false == DamageFont_->GetDeathFlg())
	{
		DamageFont_->Death();
	}
}
