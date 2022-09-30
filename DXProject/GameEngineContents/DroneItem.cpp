#include "PreCompile.h"
#include "DroneItem.h"
#include "Player.h"

DroneItem::DroneItem() 
{
}

DroneItem::~DroneItem() 
{
}

void DroneItem::Start()
{
	Initialize();
}

void DroneItem::Update(float _DeltaTime)
{
	// �÷��̾�
	if (false == Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
		, std::bind(&DroneItem::CollisionCheckPlayer, this, std::placeholders::_1, std::placeholders::_2)))
	{
		FontRenderer_->Off();
	}
}

CollisionReturn DroneItem::CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	float4 thisPos = this->GetTransform().GetWorldPosition();
	float4 MainCameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();

	FontRenderer_->On();
	// ������������ ��ũ������������ ��ȯ�Ͽ� FontRenderer�� ����
	FontRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
								  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) - 75.0f });

	if (true == GameEngineInput::GetInst()->IsPress(Player_KEY_INTERACTIVE))
	{
		// �÷��̾ ���� ��尡 ����Ұ�쿡��
		if (DronePrice_ <= Player::GetPlayerGold())
		{
			// �������� ���̰�
			Player::AddGold(-DronePrice_);

			// ���ڸ� ����
			AddDrone();
		}
	}

	return CollisionReturn::Break;
}