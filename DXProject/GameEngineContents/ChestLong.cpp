#include "PreCompile.h"
#include "ChestLong.h"
#include "Drops.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <math.h>
#include "ItemManager.h"

ChestLong::ChestLong() 
	: IsSelected_(false)
{
	ChestPrice_ = 17;
}

ChestLong::~ChestLong() 
{
}

void ChestLong::Update(float _DeltaTime)
{
	// 열려져있는 상자라면 업데이트를 무시
	if (true == IsOpen_)
	{
		return;
	}

	// 충돌처리
	if (false == Collision_->IsCollision(CollisionType::CT_AABB2D, ObjectGroup::Player, CollisionType::CT_AABB2D
		, std::bind(&ChestLong::CollisionFunc, this, std::placeholders::_1, std::placeholders::_2)))
	{
		FontRenderer_->Off();
	}

	WaveAnimItemRenderer(_DeltaTime);
}

void ChestLong::Initialize()
{
	float4 thisPos = this->GetTransform().GetWorldPosition();

	// 상자 자신의 렌더러
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetSamplingModePoint();
	Renderer_->SetScaleModeImage();

	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_LONG_IDLE, FrameAnimation_DESC(TEX_OBJECT_CHEST_LONG_IDLE, ANIMATION_FRAME_DELAY, true));
	Renderer_->CreateFrameAnimationFolder(TEX_OBJECT_CHEST_LONG_OPEN, FrameAnimation_DESC(TEX_OBJECT_CHEST_LONG_OPEN, ANIMATION_FRAME_DELAY, false));
	Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_LONG_IDLE);
	Renderer_->SetPivot(PIVOTMODE::BOT);

	// 상자에 표시될 폰트 렌더러
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetText("Press 'A' to buy item ($ " + std::to_string(ChestPrice_) + ")", FONT_RISKOFRAIN);
	FontRenderer_->SetSize(15);
	FontRenderer_->SetLeftAndRightSort(LeftAndRightSort::CENTER);
	FontRenderer_->Off();

	FontYPosWeighted = -70.0f; // 가중치 설정


	// 플레이어와 충돌할 콜리전
	Collision_ = CreateComponent<GameEngineCollision>();

	Collision_->ChangeOrder(ObjectGroup::Chest);
	Collision_->GetTransform().SetWorldScale({ 44.0f, 26.0f, 1.0f });
	Collision_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x
												, this->GetTransform().GetWorldPosition().y + 13.0f
												, this->GetTransform().GetWorldPosition().z });


	// chest가 만들어낼 아이템 랜더러
	ShowItemRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ShowItemRenderer_->SetSamplingModePoint();
	ShowItemRenderer_->GetTransform().SetWorldPosition({ thisPos.x, thisPos.y + 50.0f, thisPos.z });

	// 만들어야할 아이템을 랜덤으로 생성
	ItemList_ = static_cast<ItemList>(GameEngineRandom::MainRandom.RandomInt(static_cast<int>(ItemList::BarbedWire), static_cast<int>(ItemList::End) - 1));

	switch (ItemList_)
	{
	case ItemList::BarbedWire:
		ShowItemRenderer_->SetTexture(ITEM_NAME_BARBEDWIRE);
		break;
	case ItemList::RedWhip:
		ShowItemRenderer_->SetTexture(ITEM_NAME_REDWHIP);
		break;
	case ItemList::MeatNugget:
		ShowItemRenderer_->SetTexture(ITEM_NAME_MEATNUGGET);
		break;
	case ItemList::Warbanner:
		ShowItemRenderer_->SetTexture(ITEM_NAME_WARBANNER);
		break;
	case ItemList::HarvesterScythe:
		ShowItemRenderer_->SetTexture(ITEM_NAME_HARVESTERSCYTHE);
		break;
	case ItemList::Sawmerang:
		ShowItemRenderer_->SetTexture(ITEM_NAME_SAWMERANG);
		break;
	default:
		break;
	}
	ShowItemRenderer_->ScaleToTexture();
}

void ChestLong::ChangeOpenAnim()
{
	IsSelected_ = true;		// 선택된 Chest에만 True로 변경

	ChangeOpenAnimChestLong();
}

void ChestLong::WaveAnimItemRenderer(float _DeltaTime)
{
	static float MovedYPos = 0.0f;
	static float Ypos = 8.0f;

	ShowItemRenderer_->GetTransform().SetWorldMove({0.0f, Ypos * _DeltaTime, 0.0f });
	MovedYPos += Ypos * _DeltaTime;	// 이동한 거리

	// 10.0f이상 이동했으면 위아래 반전
	if (abs(MovedYPos) > 45.0f)
	{
		Ypos *= -1.0f;
		MovedYPos = 0.0f;
	}
}

bool ChestLong::CollisionFunc(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return CollisionCheckPlayer(_This, _Other);
}

void ChestLong::ChangeOpenAnimChestLong()
{
	// 이미 열려져있는 경우에는 무시
	if (true == IsOpen_)
	{
		return;
	}

	// 선택받았을 경우에만 아이템을 생성
	if (true == IsSelected_)
	{
		float4 tmpPos = this->GetTransform().GetWorldPosition();
		ItemManager::CreateItem(GetLevel(), ItemList_, { tmpPos.x, tmpPos.y - 20.0f, tmpPos.z});
	}
	
	// 애니메이션은 선택 유무와 상관없이 열리도록
	IsOpen_ = true;
	Renderer_->ChangeFrameAnimation(TEX_OBJECT_CHEST_LONG_OPEN);
	FontRenderer_->Off();
	ShowItemRenderer_->Off();
}
