#include "PreCompile.h"
#include "CharacterCreater.h"
#include <GameEngineBase/GameEngineRandom.h>

GameEngineTexture* CharacterCreater::ColMap_ = nullptr;
float4 CharacterCreater::CurPlayerPos_ = float4::ZERO;

CharacterCreater::CharacterCreater() 
	: CreatePlayerPos_(float4::ZERO)
{
}

CharacterCreater::~CharacterCreater() 
{
}

void CharacterCreater::MakePlayerPosition()
{
	CreatePlayerPos_ = MakePosition(0);
}

void CharacterCreater::MakeMonsterPosition()
{
	CreateMonsterPos_ = MakePosition(1);
}

void CharacterCreater::Start()
{
	
}

void CharacterCreater::Update(float _DeltaTime)
{

}

float4 CharacterCreater::MakePosition(int _CreateMod)
{
	/*
	_CreateMod == 0 -> �÷��̾� ����
				  1 -> ���� ����
				  2 -> ������Ʈ ����?
	*/


	GameEngineRandom* Random = new GameEngineRandom();
	float4 CreatePos = float4::ZERO;

	// ���� �ϳ��� �Էµ��� �ʾ������

	switch (_CreateMod)
	{
	case 0:
		CreatePos.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
		CreatePos.y = Random->RandomInt(100, ColMap_->GetScale().y - 100);
		CreatePos.z = static_cast<float>(ZOrder::Player);
		break;
	case 1:
		CreatePos.x = Random->RandomInt(CurPlayerPos_.x - 1000, CurPlayerPos_.x + 1000);
		CreatePos.y = Random->RandomInt(CurPlayerPos_.y - 1000, CurPlayerPos_.y + 1000);
		CreatePos.y = -CreatePos.y;

		if (CreatePos.x >= ColMap_->GetScale().x)
		{
			CreatePos.x = ColMap_->GetScale().x - 100;
		}
		if (CreatePos.y >= ColMap_->GetScale().y)
		{
			CreatePos.y = ColMap_->GetScale().y - 100;
		}

		CreatePos.z = static_cast<float>(ZOrder::Monsters);

		break;
	case 2:
		// TODO::������Ʈ ���� ��ġ?
		break;
	default:
		break;
	}

	int Count_ = 0;

	// x������ �÷��̾ ������ �� �ִ� ��ġ �˻�
	for (;;)
	{
		float4 Color = ColMap_->GetPixelToFloat4(CreatePos.x, CreatePos.y);

		// �� �˻�
		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			for (;;)
			{
				// ������� �� ���� ��ġ�� õ���� ���� Ž��
				CreatePos.y--;
				Color = ColMap_->GetPixelToFloat4(CreatePos.x, CreatePos.y);

				// ���̻� ���� �ƴϸ� �ݺ� ����
				if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
				{
					break;
				}
			}
			break;
		}

		// ���� �ƴϾ��ٸ� xy��ǥ�� �ٽ� �˻��Ͽ� ��Ž��
		switch (_CreateMod)
		{
		case 0:
			CreatePos.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
			CreatePos.y = Random->RandomInt(100, ColMap_->GetScale().y - 100);
			CreatePos.z = static_cast<float>(ZOrder::Player);
			break;
		case 1:
			CreatePos.x = Random->RandomInt(CurPlayerPos_.x - 1000, CurPlayerPos_.x + 1000);
			CreatePos.y = Random->RandomInt(CurPlayerPos_.y - 1000, CurPlayerPos_.y + 1000);
			CreatePos.y = -CreatePos.y;

			if (CreatePos.x >= ColMap_->GetScale().x)
			{
				CreatePos.x = ColMap_->GetScale().x - 100;
			}
			if (CreatePos.y >= ColMap_->GetScale().y)
			{
				CreatePos.y = ColMap_->GetScale().y - 100;
			}
			CreatePos.z = static_cast<float>(ZOrder::Monsters);

			break;
		case 2:
			// TODO::������Ʈ ���� ��ġ?
			break;
		default:
			break;
		}
	}

	// �÷��̾�� �ݿ��ϱ� ���Ͽ� y�� ����
	CreatePos.y = -CreatePos.y + 30;

	// ����׿� ��ġ
	//CreatePos = { 33, -597 };

	delete Random;
	Random = nullptr;

	return CreatePos;
}