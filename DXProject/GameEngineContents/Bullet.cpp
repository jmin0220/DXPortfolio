#include "PreCompile.h"
#include "Bullet.h"

Bullet::Bullet() 
	: Collision_(nullptr)
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
	this->GetTransform().SetWorldMove({ 1.0, 0.0, 0.0 });

	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		                   , std::bind(&Bullet::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool Bullet::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	// TODO::�ӽ��ڵ�
	_Other->GetActor()->Death();
	this->Death();

	return false;
}
