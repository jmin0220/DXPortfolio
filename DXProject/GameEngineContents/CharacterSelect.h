#pragma once
#include "PreCompile.h"
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
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

private:
	CharacterSelecter* CharacterSelecter_;
};
