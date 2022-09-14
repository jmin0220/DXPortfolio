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
	// ���ư��� ������
	if (false == IsReturn_)
	{
		this->GetTransform().SetWorldMove(FlyDirection_ * Speed_ * _DeltaTime);
		FlyLength_ += FlyDirection_.x * Speed_ * _DeltaTime;

		if (abs(FlyLength_) >= 700.0f)
		{
			IsReturn_ = true;

			// �浹�ߴ� ���� ����Ʈ�� �ʱ�ȭ
			CheckedMonster_.clear();
		}
	}
	// ���ƿ��� ������
	else
	{
		FlyDirection_ = PlayerPos_ - this->GetTransform().GetWorldPosition();

		this->GetTransform().SetWorldMove(FlyDirection_.NormalizeReturn() * Speed_ * _DeltaTime);

		// �÷��̾�� ���������� Death
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
	// �̹� �浹������ ������ ����
	if (find(CheckedMonster_.begin(), CheckedMonster_.end(), _Other) != CheckedMonster_.end())
	{
		return false;
	}

	CheckedMonster_.push_back(_Other);

	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->HitFunction(PlayerStatus::GetiDamage() * 5);
	TmpMonster->ChangeStateToHitted();

	// ������ ��Ʈ ���
	ContentsFont* DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(PlayerStatus::GetiDamage() * 5), { 0, 30.0f + 25.0f });
	DamageFont_->GetTransform().SetWorldPosition({ _Other->GetTransform().GetWorldPosition().x, _Other->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);

	DamageFont_->SetDeathTimer(1.0f);

	return true;
}
