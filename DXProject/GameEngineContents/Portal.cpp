#include "PreCompile.h"
#include "Portal.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>

Portal::Portal() 
	: RespawnBossTimer_(0.0f)
	, RespawnBossFlg_(false)
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	/*
	Index == 0 -> 비활성화 상태~ 활성화되고 보스가 처치되기 전까지
	      == 1 -> 보스가 처치되고 플레이어가 사용해야할 때
		  == 2 -> 다음 스테이지로 넘어가서 플레이어의 뒤쪽에 깔리는 이미지
	*/
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetFolderTextureToIndex(TEX_OBJECT_TELEPORTAL, 0);
	Renderer_->SetSamplingModePoint();
	Renderer_->ScaleToTexture();
	Renderer_->SetPivot(PIVOTMODE::BOT);

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::Portal);
	Collision_->GetTransform().SetWorldScale({96.0f, 50.0f});
	Collision_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x
												, this->GetTransform().GetWorldPosition().y + 25.0f
												, this->GetTransform().GetWorldPosition().z });
}

void Portal::Update(float _DeltatTime)
{
	if (true == RespawnBossFlg_)
	{
		RespawnBossTimer_ -= _DeltatTime;
	}

	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
		, std::bind(&Portal::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool Portal::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (GameEngineInput::GetInst()->IsDown(Player_KEY_INTERACTIVE))
	{
		switch (PortalState_)
		{
		case PortalState::NonActivate:
			// 포탈의 스테이트를 Activate로 변경하고 보스 출현 타이머 스타트
			RespawnBossFlg_ = true;
			RespawnBossTimer_ = 20.0f;
			CommonFunction::CommonFunction_->CameraShakeEffectOn(20.0f, 1.0f);
			break;
		case PortalState::Activate:
			// 동작하지 않음
			break;
		case PortalState::KillBoss:
			// 다음레벨로 이동
			GEngine::ChangeLevel(LEVEL_STAGE2);
			break;
		default:
			break;
		}
	}

	return true;
}

