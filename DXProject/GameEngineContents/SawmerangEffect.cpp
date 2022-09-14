#include "PreCompile.h"
#include "SawmerangEffect.h"
#include <math.h>
#include "PlayerStatus.h"
#include "Monster.h"
#include "ContentsFont.h"

SawmerangEffect::SawmerangEffect() 
	: Speed_(800.0f)
	, FlyLength_(0.0f)
	, IsReturn_(false)
{
}

SawmerangEffect::~SawmerangEffect() 
{
}


void SawmerangEffect::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->CreateFrameAnimationFolder(ITEM_ANIMATION_SAWMERANG_EFFECT, FrameAnimation_DESC(ITEM_ANIMATION_SAWMERANG_EFFECT, ANIMATION_FRAME_DELAY, true));
	Renderer_->ChangeFrameAnimation(ITEM_ANIMATION_SAWMERANG_EFFECT);
	Renderer_->SetScaleModeImage();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 54.0f, 54.0f, 1.0f });
}

void SawmerangEffect::Update(float _DeltaTime)
{
	// 날아가고 있을때
	if (false == IsReturn_)
	{
		this->GetTransform().SetWorldMove(FlyDirection_ * Speed_ * _DeltaTime);
		FlyLength_ += FlyDirection_.x * Speed_ * _DeltaTime;

		if (abs(FlyLength_) >= 700.0f)
		{
			IsReturn_ = true;

			// 충돌했던 몬스터 리스트를 초기화
			CheckedMonster_.clear();
		}
	}
	// 돌아오고 있을떄
	else
	{
		FlyDirection_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

		this->GetTransform().SetWorldMove(FlyDirection_.NormalizeReturn() * Speed_ * _DeltaTime);

		// 플레이어에게 도달했으면 Death
		if(FlyDirection_.Length() <= 10.0f)
		//if (this->GetTransform().GetWorldPosition().CompareInt2D(PlayerPos_))
		{
			this->Death();
		}
	}

	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		, std::bind(&SawmerangEffect::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool SawmerangEffect::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// 이미 충돌한적이 있으면 무시
	if (find(CheckedMonster_.begin(), CheckedMonster_.end(), _Other) != CheckedMonster_.end())
	{
		return false;
	}

	CheckedMonster_.push_back(_Other);

	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->HitFunction(PlayerStatus::GetiDamage() * 5);
	TmpMonster->ChangeStateToHitted();

	// 데미지 폰트 출력
	ContentsFont* DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(PlayerStatus::GetiDamage() * 5), { 0, 30.0f + 25.0f });
	DamageFont_->GetTransform().SetWorldPosition({ _Other->GetTransform().GetWorldPosition().x, _Other->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);

	DamageFont_->SetDeathTimer(1.0f);

	return true;
}
