#pragma once
#include "PreCompile.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "StartSoundPlayer.h"

// Ό³Έν :
class CharacterSelecter;
class CharacterSelect : public GameEngineLevel
{
public:
	// constrcuter destructer
	CharacterSelect();
	~CharacterSelect();

	// delete Function
	CharacterSelect(const CharacterSelect& _Other) = delete;
	CharacterSelect(CharacterSelect&& _Other) noexcept = delete;
	CharacterSelect& operator=(const CharacterSelect& _Other) = delete;
	CharacterSelect& operator=(CharacterSelect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelEndEvent() override;

private:
	CharacterSelecter* CharacterSelecter_;
	StartSoundPlayer SoundPlayer_;
};

