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
	Index == 0 -> ��Ȱ��ȭ ����~ Ȱ��ȭ�ǰ� ������ óġ�Ǳ� ������
	      == 1 -> ������ óġ�ǰ� �÷��̾ ����ؾ��� ��
		  == 2 -> ���� ���������� �Ѿ�� �÷��̾��� ���ʿ� �򸮴� �̹���
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
			// ��Ż�� ������Ʈ�� Activate�� �����ϰ� ���� ���� Ÿ�̸� ��ŸƮ
			RespawnBossFlg_ = true;
			RespawnBossTimer_ = 20.0f;
			CommonFunction::CommonFunction_->CameraShakeEffectOn(20.0f, 1.0f);
			break;
		case PortalState::Activate:
			// �������� ����
			break;
		case PortalState::KillBoss:
			// ���������� �̵�
			GEngine::ChangeLevel(LEVEL_STAGE2);
			break;
		default:
			break;
		}
	}

	return true;
}

