#include "PreCompile.h"
#include "ChestParent.h"
#include <GameEngineBase/GameEngineRandom.h>

ChestParent::ChestParent()
	: Renderer_(nullptr)
	, GoldValue_(0)
	, ExpValue_(0)
	, IsOpen_(false)
{
}

ChestParent::~ChestParent()
{
}

void ChestParent::Start()
{
	Initialize();

	// 개체마다 다른 골드, 경험치를 생성
	// TODO::시간별로 다른 경험치, 골드를 생성
	GameEngineRandom* tmpRandom = new GameEngineRandom();
	GoldValue_ = tmpRandom->RandomInt(4 * 1, 5 * 1);
	ExpValue_ = tmpRandom->RandomInt(10 * 1, 13 * 1);
}

void ChestParent::Update(float _DeltaTime)
{
	// 플레이어
	if (false == Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
		, std::bind(&ChestParent::CollisionCheckPlayer, this, std::placeholders::_1, std::placeholders::_2)))
	{
		FontRenderer_->Off();
	}
}

bool ChestParent::CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (false == IsOpen_)
	{
		float4 thisPos = this->GetTransform().GetWorldPosition();
		float4 MainCameraPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();

		FontRenderer_->On();
		// 월드포지션을 스크린포지션으로 전환하여 FontRenderer에 적용
		FontRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
									  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) - 75.0f });

	}

	if (true == GameEngineInput::GetInst()->IsPress(Player_KEY_INTERACTIVE))
	{
		IsOpen_ = true;
		ChangeOpenAnim();
	}

	return true;
}