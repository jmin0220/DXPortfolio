#include "PreCompile.h"
#include "Bouncer.h"
#include "Monster.h"
#include "Player.h"

Bouncer::Bouncer() 
{
}

Bouncer::~Bouncer() 
{
}

void Bouncer::Start()
{
	// TODO::디버그용 임시위치
	this->GetTransform().SetWorldPosition({719.0f, -863.0f});

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_BOUNCER, FrameAnimation_DESC(TEX_OBJECT_BOUNCER, ANIMATION_FRAME_DELAY, true));
	Renderer_->ChangeFrameAnimation(TEX_OBJECT_BOUNCER);
	Renderer_->SetPivot(PIVOTMODE::BOT);
	Renderer_->ScaleToTexture();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::Bouncer);
	Collision_->GetTransform().SetWorldScale({ 42.0f, 116.0f, 1.0f });
	Collision_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x
												, this->GetTransform().GetWorldPosition().y + 64.0f
												, this->GetTransform().GetWorldPosition().z });
}

void Bouncer::Update(float _DeltaTime)
{
	// 몬스터
	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		, std::bind(&Bouncer::CollisionCheckMonster, this, std::placeholders::_1, std::placeholders::_2));

	// 플레이어
	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
		, std::bind(&Bouncer::CollisionCheckPlayer, this, std::placeholders::_1, std::placeholders::_2));
}

CollisionReturn Bouncer::CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Player* TmpPlayer = dynamic_cast<Player*>(_Other->GetActor());
	TmpPlayer->SetJumpSpeedByBouncer();

	return CollisionReturn::Break;
}

CollisionReturn Bouncer::CollisionCheckMonster(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());
	TmpMonster->SetJumpSpeedByBouncer();

	return CollisionReturn::Break;
}