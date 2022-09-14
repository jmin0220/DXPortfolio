#include "PreCompile.h"
#include "ItemManager.h"
#include "Player.h"
#include "Item.h"
#include <GameEngineBase/GameEngineRandom.h>

#pragma region ITEMS
#include "BarbedWire.h"
#include "MeatNugget.h"
#include "Warbanner.h"
#include "RedWhip.h"
#include "HarvesterScythe.h"
#include "Sawmerang.h"
#pragma endregion

std::vector<Item*> ItemManager::ItemVector_ = {};
float4 ItemManager::PlayerPos_ = float4::ZERO;

ItemManager::ItemManager() 
{
}

ItemManager::~ItemManager() 
{
}

void ItemManager::CreateItem(GameEngineLevel* _Level, float4 _Pos)
{
	// �������� �������� ������
	int ItemMaxNum = static_cast<int>(ItemList::End) - 1;
	CreateItem(_Level, static_cast<ItemList>(GameEngineRandom::MainRandom.RandomInt(0, ItemMaxNum)), _Pos);
}

void ItemManager::CreateItem(GameEngineLevel* _Level, ItemList _ItemList, float4 _Pos)
{
	Item* tmpItem = nullptr;

	// ������ ����
	switch (_ItemList)
	{
	case ItemList::BarbedWire:
		tmpItem = _Level->CreateActor<BarbedWire>();
		break;
	case ItemList::RedWhip:
		tmpItem = _Level->CreateActor<RedWhip>();
		break;
	case ItemList::MeatNugget:
		tmpItem = _Level->CreateActor<MeatNugget>();
		break;
	case ItemList::Warbanner:
		tmpItem = _Level->CreateActor<Warbanner>();
		break;
	case ItemList::HarvesterScythe:
		tmpItem = _Level->CreateActor<HarvesterScythe>();
		break;
	case ItemList::Sawmerang:
		tmpItem = _Level->CreateActor<Sawmerang>();
	case ItemList::End:
		break;
	default:
		break;
	}
		
	tmpItem->Initialize();
	// �׽�Ʈ�� ������
	tmpItem->GetTransform().SetWorldPosition({ _Pos.x, _Pos.y, static_cast<float>(ZOrder::Item) });

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

		// ������Ʈ�� ����� ������
		if (ToPlayerLength_.Length() <= 30)
		{
			// �÷��̾ ��� �߰�
			Player* tmpPlayer = nullptr;
			tmpPlayer->AddItem(tmpItem);

			// RootingFlag�� True�� �������� ȿ������ ������Ʈ ����
			tmpItem->SetPlayerPos(PlayerPos_);
			tmpItem->SetItemRootingFlgTrue();

			ItemVector_.erase(ItemVector_.begin() + i);

			return;
		}

		i++;
	}
}

