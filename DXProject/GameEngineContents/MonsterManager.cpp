#include "PreCompile.h"
#include "MonsterManager.h"
#include "Lemurian.h"

MonsterManager::MonsterManager() 
	: SingleMonsterRespawnTimer_(0.0f)
	, GroupMonsterRespawnTimer_(0.0f)
	, RespawnPos_(float4::ZERO)
	, Monster_(nullptr)
{
}

MonsterManager::~MonsterManager() 
{
}



void MonsterManager::Start()
{
	// TODO::���� ������ ������ ���
}

void MonsterManager::Update(float _DeltaTime)
{
	// TODO::���� ������ ������ �Է�

	// TODO:: Ÿ�̸ӿ� ���� ������ ����
	SingleMonsterRespawnTimer_ += _DeltaTime;
	GroupMonsterRespawnTimer_ += _DeltaTime;

	// �ӽ� Ÿ�̸�
	if (SingleMonsterRespawnTimer_ >= 3.0f)
	{
		Monster_ = GetLevel()->CreateActor<Lemurian>();
		Monster_->GetTransform().SetWorldPosition(RespawnPos_);

		Monster_->SetColMapInfo(ColMap_);

		SingleMonsterRespawnTimer_ = 0.0f;
	}
}