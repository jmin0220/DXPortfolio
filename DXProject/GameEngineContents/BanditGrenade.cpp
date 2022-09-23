#include "PreCompile.h"
#include "BanditGrenade.h"
#include "PiercingBullet.h"
#include <GameEngineBase/GameEngineRandom.h>

BanditGrenade::BanditGrenade()
	: IsExplosion_(false)
	, JumpSpeed_(500.0f)
{
}

BanditGrenade::~BanditGrenade()
{
}


void BanditGrenade::Start()
{
	// ����ź�� ��ü
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, ANIMATION_FRAME_DELAY, true));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, [=](const FrameAnimation_DESC& _Info)
		{
			// �� �����Ӹ��� ȸ��
			Renderer_->GetTransform().SetAddWorldRotation({ 0.0f, 0.0f, 60.0f, 0.0f });
		}
	);

	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SKILL2_GRENADE);
	Renderer_->ScaleToTexture();

	// ����ź�� ����Ʈ
	EffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	EffectRenderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, ANIMATION_FRAME_DELAY, false));
	EffectRenderer_->AnimationBindFrame(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, [=](const FrameAnimation_DESC& _Info)
		{
			if (1 == _Info.CurFrame && false == IsExplosion_)
			{
				CreateExplosion();
			}
		}
	);	
	
	EffectRenderer_->AnimationBindEnd(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, [=](const FrameAnimation_DESC& _Info)
		{
			this->Death();
		}
	);

	EffectRenderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION);
	EffectRenderer_->ScaleToTexture();

	EffectRenderer_->Off();

	// ����ź ��ü�� �浹ü
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 24.0f, 24.0f, 1.0f });	// ȸ���ϹǷ� ���簢������ �ø��� ����
};

void BanditGrenade::Update(float _DeltaTime)
{
	if (false == IsExplosion_)
	{
		GroundFall(_DeltaTime);

		Collision_->IsCollision(CollisionType::CT_SPHERE2D, ObjectGroup::Monster, CollisionType::CT_SPHERE2D
			, std::bind(&BanditGrenade::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
	}
};

void BanditGrenade::GroundFall(float _DeltaTime)
{
	if (nullptr == ColMap_)
	{
		MsgBoxAssert("�浹���� �������� �ʽ��ϴ�.");
	}

	// ���� ó��
	// �ϴ� �߾�
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// �ٴ��� ���� ������ ����
	if (false == ColorDown.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
	{
		GetTransform().SetWorldMove(CreatedDir_ * 500.0f * _DeltaTime);
		GetTransform().SetWorldMove((GetTransform().GetDownVector() * 240.0f + JumpSpeed_) * _DeltaTime);

		JumpSpeed_ -= 10.0f;

		if (JumpSpeed_ <= 0.0f)
		{
			JumpSpeed_ = 0.0f;
		}
	}
	else
	{
		CreateExplosion();
	}
}

void BanditGrenade::CreateExplosion()
{
	PiercingBullet* piercingbullet = GetLevel()->CreateActor<PiercingBullet>();

	// ���� ����Ʈ On
	Renderer_->Off();
	EffectRenderer_->On();
	IsExplosion_ = true;

	// ũ��Ƽ�� ����
	if (PlayerStatus::CritChance_ >= GameEngineRandom::MainRandom.RandomInt(0, 100))
	{
		piercingbullet->SetCritFlgTrue();
		Damage_ *= 1.5f;
	}

	piercingbullet->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
	piercingbullet->SetDamage(Damage_);
	piercingbullet->SetDirection(float4::ZERO);	// �ݸ����� �Ǻ��� �߽�
	piercingbullet->SetPiercingLength(158.0f);	// �������� �̹��� Xũ��
	piercingbullet->ResizePiercingBulletXSize();
	piercingbullet->SetBulletYPositionLevel(0);
}

CollisionReturn BanditGrenade::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	CreateExplosion();

	return CollisionReturn::Break;
}