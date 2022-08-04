#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"

// ���� :
class MonsterManager : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterManager();
	~MonsterManager();

	// delete Function
	MonsterManager(const MonsterManager& _Other) = delete;
	MonsterManager(MonsterManager&& _Other) noexcept = delete;
	MonsterManager& operator=(const MonsterManager& _Other) = delete;
	MonsterManager& operator=(MonsterManager&& _Other) noexcept = delete;

	inline void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void SetColMapInfoToMonster(GameEngineTexture* _ColMap);

	// ������ �����ֱ�
	// 1���� -> 30���� -> 2���� -> 30���� -> 4���� -> .... �ݺ�
	// 30�� �������� �����Ǵ� ���͵� ������ Ÿ�̸�
	float SingleMonsterRespawnTimer_;

	// 30�ʸ� ī��Ʈ �� Ÿ�̸�
	float GroupMonsterRespawnTimer_;

	// ������ �� ��ġ
	float4 RespawnPos_;

	// ������ ����
	Monster* Monster_;

	// �浹�� �� ����
	GameEngineTexture* ColMap_;
};