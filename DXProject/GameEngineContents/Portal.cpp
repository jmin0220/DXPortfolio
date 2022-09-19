#include "PreCompile.h"
#include "Portal.h"

Portal::Portal() 
	: PortalState_(PortalState::Activate)
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

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->ChangeOrder(ObjectGroup::Portal);
	Collision_->GetTransform().SetWorldScale({96.0f, 50.0f});
}

void Portal::Update(float _DeltatTime)
{
	switch (PortalState_)
	{
	case PortalState::NonActivate:
		Renderer_->SetFolderTextureToIndex(TEX_OBJECT_TELEPORTAL, 0);
		break;
	case PortalState::Activate:
		Renderer_->SetFolderTextureToIndex(TEX_OBJECT_TELEPORTAL, 1);
		break;
	case PortalState::Sleep:
		Renderer_->SetFolderTextureToIndex(TEX_OBJECT_TELEPORTAL, 2);
		break;
	default:
		break;
	}

	Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Monster, CollisionType::CT_AABB2D
		, std::bind(&Portal::CollisionCheck, this, std::placeholders::_1, std::placeholders::_2));
}

bool Portal::CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	switch (PortalState_)
	{
	case PortalState::NonActivate:
		// TODO::화면 흔들림 이펙트
		// TODO::보스 생성 플래그 On
		break;
	case PortalState::Activate:
		// TODO::LevelChange
		break;
	case PortalState::Sleep:
			return true;
		break;
	default:
		break;
	}

	return true;
}

