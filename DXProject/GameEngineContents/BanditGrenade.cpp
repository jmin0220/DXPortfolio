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
	// 수류탄의 몸체
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	Renderer_->CreateFrameAnimationFolder(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, FrameAnimation_DESC(PLAYER_ANIM_BANDIT_SKILL2_EXPLOSION, ANIMATION_FRAME_DELAY, true));
	Renderer_->AnimationBindFrame(PLAYER_ANIM_BANDIT_SKILL2_GRENADE, [=](const FrameAnimation_DESC& _Info)
		{
			// 매 프레임마다 회전
			Renderer_->GetTransform().SetAddWorldRotation(60.0f);
		}
	);

	Renderer_->ChangeFrameAnimation(PLAYER_ANIM_BANDIT_SKILL2_GRENADE);
	Renderer_->ScaleToTexture();

	// 수류탄의 이펙트
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

	// 수류탄 몸체의 충돌체
	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::PlayerBullet);
	Collision_->GetTransform().SetWorldScale({ 24.0f, 24.0f, 1.0f });	// 회전하므로 정사각형으로 컬리전 설정
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
		MsgBoxAssert("충돌맵이 존재하지 않습니다.");
	}

	// 낙하 처리
	// 하단 중앙
	float4 ColorDown = ColMap_->GetPixelToFloat4(this->GetTransform().GetWorldPosition().ix() + Renderer_->GetCurTexture()->GetScale().hix()
		, -this->GetTransform().GetWorldPosition().iy() + Renderer_->GetCurTexture()->GetScale().hiy() + 300 * _DeltaTime);

	// 바닥이 닿지 않으면 낙하
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

	// 크리티컬 찬스
	if (PlayerStatus::CritChance_ >= GameEngineRandom::MainRandom.RandomInt(0, 100))
	{
		piercingbullet->SetCritFlgTrue();
		Damage_ *= 1.5f;
	}

	piercingbullet->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());
	piercingbullet->SetDamage(Damage_);
	piercingbullet->SetDirection(float4::ZERO);	// 콜리전의 피봇은 중심
	piercingbullet->SetPiercingLength(158.0f);	// 렌더러의 이미지 X크기
	piercingbullet->ResizePiercingBulletXSize();
	piercingbullet->SetBulletYPositionLevel(0);
}

bool BanditGrenade::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Renderer_->Off();
	EffectRenderer_->On();

	return true;
}