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
	// 플레이어
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
	// 월드포지션을 스크린포지션으로 전환하여 FontRenderer에 적용
	FontRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
								  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) - 75.0f });

	if (true == GameEngineInput::GetInst()->IsPress(Player_KEY_INTERACTIVE))
	{
		// 플레이어가 가진 골드가 충분할경우에만
		if (DronePrice_ <= Player::GetPlayerGold())
		{
			// 소지금을 줄이고
			Player::AddGold(-DronePrice_);

			// 상자를 오픈
			AddDrone();
		}
	}

	return CollisionReturn::Break;
}