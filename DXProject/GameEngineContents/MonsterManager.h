#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"

// ���� :
class CharacterCreater;
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

	inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

	inline void SetRespawnPos(float4 _Pos)
	{
		RespawnPos_ = _Pos;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// ������ �����ֱ�
	// 1���� -> 30���� -> 2���� -> 30���� -> 4���� -> .... �ݺ�
	// 30�� �������� �����Ǵ� ���͵� ������ Ÿ�̸�
	float SingleMonsterRespawnTimer_;

	// 30�ʸ� ī��Ʈ �� Ÿ�̸�
	float GroupMonsterRespawnTimer_;

	// ������ �� ��ġ
	float4 RespawnPos_;
	// �÷��̾� ĳ������ ��ġ
	float4 PlayerPos_;

	// ������ ����
	std::list<Monster*> Monster_;

	// �浹�� �� ����
	GameEngineTexture* ColMap_;

	CharacterCreater* CharacterCreater_;
};