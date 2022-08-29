#include "PreCompile.h"
#include "ChestParent.h"
#include <GameEngineBase/GameEngineRandom.h>

ChestParent::ChestParent()
	: Renderer_(nullptr)
	, GoldValue_(1)
	, ExpValue_(1)
	, IsOpen_(false)
{
}

ChestParent::~ChestParent()
{
}

void ChestParent::Start()
{
	Initialize();

	// ��ü���� �ٸ� ���, ����ġ�� ����
	// TODO::�ð����� �ٸ� ����ġ, ��带 ����
	GameEngineRandom* tmpRandom = new GameEngineRandom();
	GoldValue_ = tmpRandom->RandomInt(4 * GoldValue_, 5 * GoldValue_);
	ExpValue_ = tmpRandom->RandomInt(10 * ExpValue_, 13 * ExpValue_);

	delete tmpRandom;
	tmpRandom = nullptr;
}

void ChestParent::Update(float _DeltaTime)
{
	// �÷��̾�
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
		// ������������ ��ũ������������ ��ȯ�Ͽ� FontRenderer�� ����
		FontRenderer_->SetScreenPostion({ thisPos.x - MainCameraPos.x + GameEngineWindow::GetScale().x / 2
									  , -(thisPos.y - MainCameraPos.y - GameEngineWindow::GetScale().y / 2) - 75.0f });

	}

	if (true == GameEngineInput::GetInst()->IsPress(Player_KEY_INTERACTIVE))
	{
		ChangeOpenAnim();
	}

	return true;
}