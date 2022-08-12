#include "PreCompile.h"
#include "CharacterCreater.h"
#include <GameEngineBase/GameEngineRandom.h>

CharacterCreater::CharacterCreater() 
	: ColMap_(nullptr)
	, CreatePlayerPos_(float4::ZERO)
{
}

CharacterCreater::~CharacterCreater() 
{
}

void CharacterCreater::Start()
{
	


}

void CharacterCreater::Update(float _DeltaTime)
{

}

void CharacterCreater::MakePosition()
{
	GameEngineRandom* Random = new GameEngineRandom();

	CreatePlayerPos_.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
	CreatePlayerPos_.y = Random->RandomInt(0, ColMap_->GetScale().y);

	float4 Color2 = ColMap_->GetPixelToFloat4(897, 736);

	// x������ �÷��̾ ������ �� �ִ� ��ġ �˻�
	for (;;)
	{
		float4 Color = ColMap_->GetPixelToFloat4(CreatePlayerPos_.x, CreatePlayerPos_.y);

		// �� �˻�
		if (true == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
		{
			for (;;)
			{
				// ������� �� ���� ��ġ�� õ���� ���� Ž��
				CreatePlayerPos_.y--;
				Color = ColMap_->GetPixelToFloat4(CreatePlayerPos_.x, CreatePlayerPos_.y);

				// ���̻� ���� �ƴϸ� �ݺ� ����
				if (false == Color.CompareInt4D({ 1.0f, 0.0f, 1.0f }))
				{
					break;
				}
			}
			break;
		}

		// ���� �ƴϾ��ٸ� xy��ǥ�� �ٽ� �˻��Ͽ� ��Ž��
		CreatePlayerPos_.x = Random->RandomInt(100, ColMap_->GetScale().x - 100);
		CreatePlayerPos_.y = Random->RandomInt(0, ColMap_->GetScale().y);
	}

	// �÷��̾�� �ݿ��ϱ� ���Ͽ� y�� ����
	CreatePlayerPos_.y = -CreatePlayerPos_.y + 30;

	//CreatePlayerPos_ = { 33, -597 };

	int a = 0;
}