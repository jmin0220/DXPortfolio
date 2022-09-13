#include "PreCompile.h"
#include "BanditGrenade.h"
#include "PiercingBullet.h"
#include <GameEngineBase/GameEngineRandom.h>

BanditGrenade::BanditGrenade()
{
}

BanditGrenade::~BanditGrenade()
{
}


void BanditGrenade::Start()
{
	// ����ź�� ��ü
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, ANIMATION_FRAME_DELAY, true));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, [=](const FrameAnimation_DESC& _Info)
		{
			// �� �����Ӹ��� ȸ��
			Renderer_->GetTransform().SetAddWorldRotation(60.0f);
		}
	);

	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SKILL2_GRENADE);
	Renderer_->ScaleToTexture();

	// ����ź�� ����Ʈ
	EffectRenderer_ = CreateComponent<GameEngineTextureRenderer>();

	EffectRenderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, ANIMATION_FRAME_DELAY, false));
	EffectRenderer_->AnimationBindFrame(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, [=](const FrameAnimation_DESC& _Info)
		{
			if (_Info.CurFrame == 1)
			{
				CreateExplosion();
			}
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
	GroundFall(_DeltaTime);

	Collision_->IsCollision(CollisionType::CT_SPHERE2D, ObjectGroup::Monster, CollisionType::CT_SPHERE2D
		, std::bind(&BanditGrenade::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
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
		GetTransform().SetWorldMove(CreatedDir_ * 150.0f * _DeltaTime);
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * 30.0f * _DeltaTime);
	}
	else
	{
		CreateExplosion();
		this->Death();
	}
}

void BanditGrenade::CreateExplosion()
{
	PiercingBullet* piercingbullet = GetLevel()->CreateActor<PiercingBullet>();

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

bool BanditGrenade::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Renderer_->Off();
	EffectRenderer_->On();

	return true;
}