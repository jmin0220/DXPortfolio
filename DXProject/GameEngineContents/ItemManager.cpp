#include "PreCompile.h"
#include "ItemManager.h"
#include "Player.h"
#include "Item.h"
#include "BarbedWire.h"

std::vector<Item*> ItemManager::ItemVector_ = {};
float4 ItemManager::PlayerPos_ = float4::ZERO;

ItemManager::ItemManager() 
{
}

ItemManager::~ItemManager() 
{
}

void ItemManager::CreateItem()
{
	// TODO::아이템이 무작위로 생성됨
	Item* tmpItem = GetLevel()->CreateActor<BarbedWire>();
	tmpItem->Initialize();
	tmpItem->GetTransform().SetWorldPosition({ 156.0f, -804.0f, static_cast<float>(ZOrder::Item) });

	ItemVector_.push_back(tmpItem);
}

void ItemManager::Start()
{

}

void ItemManager::Update(float _DeltaTime)
{
	int i = 0;

	for (Item* tmpItem : ItemVector_)
	{
		ToPlayerLength_ = PlayerPos_ - tmpItem->GetTransform().GetWorldPosition();

		// 오브젝트가 충분히 근접함
		if (ToPlayerLength_.Length() <= 30)
		{
			// 플레이어에 골드 추가
			Player* tmpPlayer = nullptr;
			tmpPlayer->AddItem(tmpItem);

			// RootingFlag가 True인 아이템은 효과만을 업데이트 해줌
			tmpItem->SetPlayerPos(PlayerPos_);
			tmpItem->SetItemRootingFlgTrue();

			ItemVector_.erase(ItemVector_.begin() + i);

			return;
		}

		i++;
	}
}

