#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Option.h"
#include "MonsterManager.h"
#include "CharacterCreater.h"
#include "ObjectCreater.h"

// 레벨의 진행단계
enum class LevelProcess
{
	NonActivePortal,
	ActivePortal,
	CreatedBoss,
	KIllBoss,
};

// 설명 :
class GameEngineActor;
class Player;
class StageGround;
class HUD;
class ItemManager;
class DebuggerGUI;
class Portal;
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


	void LevelStartEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	static Player* Player_;
	StageGround* StageActor_;
	Option Option_;
	MonsterManager* MonsterManager_;
	ObjectCreater* ObjectCreater_;
	ItemManager* ItemManager_;
	CharacterCreater* CharacterCreater_;
	Portal* Portal_;

	// 레벨 진행수준
	LevelProcess LevelProcess_;

	static DebuggerGUI* DebuggerGUI_;

	int BossCreateOption_;
private:
};

