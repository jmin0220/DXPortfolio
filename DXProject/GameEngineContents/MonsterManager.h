#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/CoreMinimal.h>
#include "Monster.h"
#include "BossMonster.h"

// 설명 :
class BossHUD;
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

	inline void CreateBossFlgOn(int bossOption = 0)
	{
		CreateBoss(bossOption);
		CreateBossFlg_ = true;
	}

	inline bool GetBossKilledFlg()
	{
		return BossKilledFlg_;
	}

	std::list<Monster*> GetAllMonsterList()
	{
		return Monster_;
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

	// TODO::보스몬스터 생성 플래그 true -> HUD->On(), BossMonster생성
	// Boss가 생성되는 위치는 n초전의 플레이어의 위치 -> 플레이어 바로 근처의 지면을 확실하게 알기 위해서

	
	// 보스몬스터 생성 플래그
	bool CreateBossFlg_;
	// 보스가 Kill당함 플래그
	bool BossKilledFlg_;
	// Boss관련 인터페이스
	BossHUD* BossHUD_;

	// 따로 관리될 보스 몬스터
	BossMonster* BossMonster_;

	void CreateBoss(int bossOption);
};