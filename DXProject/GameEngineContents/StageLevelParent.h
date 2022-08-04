#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Option.h"
#include "MonsterManager.h"

// Ό³Έν :
class GameEngineActor;
class Player;
class StageGround;
class HUD;
class StageLevelParent : public GameEngineLevel
{
public:
	// constrcuter destructer
	StageLevelParent();
	~StageLevelParent();

	// delete Function
	StageLevelParent(const StageLevelParent& _Other) = delete;
	StageLevelParent(StageLevelParent&& _Other) noexcept = delete;
	StageLevelParent& operator=(const StageLevelParent& _Other) = delete;
	StageLevelParent& operator=(StageLevelParent&& _Other) noexcept = delete;



protected:
	void Start() override {};
	void Update(float _DeltaTime) override {};
	void End() override {};

	Player* Player_;
	StageGround* StageActor_;
	Option Option_;
	MonsterManager* MonsterManager_;
private:
};

