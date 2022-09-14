#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"

// 설명 :
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

	void AllMonsterStateChangeToIdle();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	// 몬스터의 생성주기
	// 1마리 -> 30초후 -> 2마리 -> 30초후 -> 4마리 -> .... 반복
	// 30초 간격으로 생성되는 몬스터들 사이의 타이머
	float SingleMonsterRespawnTimer_;

	// 30초를 카운트 할 타이머
	float GroupMonsterRespawnTimer_;

	// 리스폰 될 위치
	float4 RespawnPos_;
	// 플레이어 캐릭터의 위치
	float4 PlayerPos_;

	// 생성될 몬스터
	std::list<Monster*> Monster_;

	// 충돌용 맵 정보
	GameEngineTexture* ColMap_;

	CharacterCreater* CharacterCreater_;
};