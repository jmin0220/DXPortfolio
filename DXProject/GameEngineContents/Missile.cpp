#include "PreCompile.h"
#include "Missile.h"
#include "MissileSmokeRenderer.h"
#include "Monster.h"
#include "ContentsFont.h"

Missile::Missile() 
	: Speed_(300.0f)
	, DegreeX_(0.0f)
	, Damage_(25)
	, IsExplosion_(false)
	, CurDegree_(0.0f)
	, SuicideTimer_(0.0f)
	, SetPositionFlg_(false)
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
	Renderer_->CreateFrameAnimationFolder(TEX_EFFECT_MISSILE_EXPLOSION, FrameAnimation_DESC(TEX_EFFECT_MISSILE_EXPLOSION, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(TEX_EFFECT_MISSILE);
	Renderer_->ScaleToTexture();
	Renderer_->SetScaleModeImage();

	Renderer_->AnimationBindEnd(TEX_EFFECT_MISSILE_EXPLOSION, [=](const FrameAnimation_DESC&) {	Renderer_->Death();  Renderer_ = nullptr; });

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetWorldScale({ 32.0f, 6.0f, 1.0f });
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);

	ExplosionCollision_ = CreateComponent<GameEngineCollision>();
	ExplosionCollision_->GetTransform().SetWorldScale({ 60.0f, 62.0f, 1.0f });
	ExplosionCollision_->ChangeOrder(ObjectGroup::PlayerBullet);
	//ExplosionCollision_->SetCollisionMode(CollisionMode::Ex);
	ExplosionCollision_->Off();
}

void Missile::Update(float _DeltaTime)
{
	SuicideTimer_ += _DeltaTime;

	if (false == IsExplosion_)
	{
		ChaseTimer_ += _DeltaTime;

		// ��ǥ�� �������
		if (TargetPos_.CompareInt3D(float4::ZERO))
		{
			DegreeX_ += 20.0f * _DeltaTime;

			if (DegreeX_ >= 360.0f)
			{
				DegreeX_ = 0.0f;
			}

			// sin����� ȸ��
			this->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, cosf(DegreeX_) * 2 });

			if (ChaseTimer_ >= 0.5f)
			{
				// ����� ������� ����
				if (false == FindChaseMonster())
				{
					Explosion();
				}
			}
		}
		// ��ǥ�� �������
		else
		{
			// ȸ��
			NowDegree_ = float4::VectorXYtoDegree(this->GetTransform().GetWorldPosition(), TargetPos_);

			float TrueRotateDegree = 0.0f;

			if (false == SetPositionFlg_)
			{
				SetPositionFlg_ = true;
				TrueRotateDegree = NowDegree_ - CurDegree_ - this->GetTransform().GetLocalRotation().z;
			}
			else
			{
				TrueRotateDegree = NowDegree_ - CurDegree_;
			}

			CurDegree_ = NowDegree_;

			DegreeX_ += 20.0f * _DeltaTime;

			if (DegreeX_ >= 360.0f)
			{
				DegreeX_ = 0.0f;
			}

			this->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, TrueRotateDegree + cosf(DegreeX_), 0.0f });
		}

		this->GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);

	}

	// �浹����
	if (false == IsExplosion_)
	{
		Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
			, std::bind(&Missile::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		ExplosionCollision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
			, std::bind(&Missile::ExplosionCollisionCheck, this, std::placeholders::_1, std::placeholders::_2));

		// �ѹ� �����ϰ� Off
		ExplosionCollision_->Off();
	}

	// n�ʸ��� ����ũ ����Ʈ ����
	if (this->GetAccTime() > 0.005 && false == IsExplosion_)
	{
		this->ReSetAccTime();

		CreateComponent<MissileSmokeRenderer>();
	}

	if (SuicideTimer_ >= 3.0f && Renderer_ != nullptr)
	{
		Explosion();
	}

	if (this->GetTransform().GetWorldPosition().CompareInt2D(TargetPos_) && Renderer_ != nullptr)
	{
		Explosion();
	}

	// ���Ⱑ ��� ������� �ı�
	if (this->Childs.size() == 2)
	{
		this->Death();
	}
}


void Missile::Explosion()
{
	IsExplosion_ = true;
	Collision_->Off();
	ExplosionCollision_->On();

	Renderer_->ChangeFrameAnimation(TEX_EFFECT_MISSILE_EXPLOSION);
}

CollisionReturn Missile::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Explosion();

	return CollisionReturn::Break;
}

CollisionReturn Missile::ExplosionCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Monster* TmpMonster = dynamic_cast<Monster*>(_Other->GetActor());

	if (true == TmpMonster->GetMonsterDeath())
	{
		return CollisionReturn::ContinueCheck;
	}

	TmpMonster->HitFunction(Damage_);
	TmpMonster->ChangeStateToHitted();


	// ������ ��Ʈ ���
	ContentsFont* DamageFont_ = GetLevel()->CreateActor<ContentsFont>();

	DamageFont_->CreateFontRenderer<GameEngineTextureRenderer>(std::to_string(Damage_), { 0, 30.0f + 25.0f });
	DamageFont_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	DamageFont_->SetIsBulletDmg(true);

	DamageFont_->SetDeathTimer(1.0f);

	return CollisionReturn::ContinueCheck;
}
