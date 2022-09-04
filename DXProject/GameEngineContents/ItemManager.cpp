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
	// TODO::�������� �������� ������
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

