#pragma once
#include "StageLevelParent.h"

// Ό³Έν :
class Stage2Level : public StageLevelParent
{
public:
	// constrcuter destructer
	Stage2Level();
	~Stage2Level();

	// delete Function
	Stage2Level(const Stage2Level& _Other) = delete;
	Stage2Level(Stage2Level&& _Other) noexcept = delete;
	Stage2Level& operator=(const Stage2Level& _Other) = delete;
	Stage2Level& operator=(Stage2Level&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

};

