#include "PreCompile.h"
#include "BarbedWire.h"
#include "Monster.h"
#include "ContentsFont.h"

BarbedWire::BarbedWire() 
{
}

BarbedWire::~BarbedWire() 
{
}

void BarbedWire::Initialize()
{
	ItemName_ = "BarbedWire";

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetTexture(ITEM_NAME_BARBEDWIRE);
	Renderer_->SetPivot(PIVOTMODE::CENTER);
	Renderer_->ScaleToTexture();

	ItemNameRenderer_ = CreateComponent<GameEngineFontRenderer>();
	ItemNameRenderer_->SetText("BarbedWire", FONT_RISKOFRAIN);
	ItemNameRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	ItemNameRenderer_->SetSize(25.0f);
	ItemNameRenderer_->Off();

	PickUpRenderer_ = CreateComponent<GameEngineFontRenderer>();
	PickUpRenderer_->SetText("Hurt nearby enemies.", FONT_RISKOFRAIN);
	PickUpRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	PickUpRenderer_->SetSize(15.0f);
	PickUpRenderer_->Off();

	EffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	EffectRenderer_->SetSamplingModePoint();
	EffectRenderer_->CreateFrameAnimationFolder(TEX_EFFECT_BARBEDWIRE_THORN, FrameAnimation_DESC(TEX_EFFECT_BARBEDWIRE_THORN, ANIMATION_FRAME_DELAY, true));
	EffectRenderer_->ChangeFrameAnimation(TEX_EFFECT_BARBEDWIRE_THORN);
	EffectRenderer_->SetPivot(PIVOTMODE::CENTER);
	EffectRenderer_->ScaleToTexture();
	EffectRenderer_->GetPixelData().MulColor.a = 0.7f;
	EffectRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 70.0f, 70.0f, 1.0f });
}

void BarbedWire::FrameItemUpdate(float4 _PlayerPos)
{
	EffectRenderer_->On();

	this->GetTransform().SetWorldPosition(_PlayerPos);

	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		, std::bind(&BarbedWire::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

	// 몬스터들과의 데미지 처리는 1초에 한번만
	if (GetAccTime() >= 1.0f)
	{
		CheckedMonster_.clear();
		ReSetAccTime();
	}
}

CollisionReturn BarbedWire::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// 이미 충돌한적이 있으면 무시
	if (find(CheckedMonster_.begin(), CheckedMonster_.end(), _Other) != CheckedMonster_.end())
	{
		return CollisionReturn::Break;
	}

	CheckedMonster_.push_back(_Other);

	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->HitFunction(10);
	TmpMonster->ChangeStateToHitted();

	// 데미지 폰트 출력
	ContentsFont* DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(10), { 0, 30.0f + 25.0f});

	DamageFont_->GetTransform().SetWorldPosition({ _Other->GetTransform().GetWorldPosition().x, _Other->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);
	DamageFont_->SetDeathTimer(1.0f);

	return CollisionReturn::Break;
}

