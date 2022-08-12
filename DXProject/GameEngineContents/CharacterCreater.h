#pragma once
#include "GameEngineCore/GameEngineActor.h"

// ���� : ���� �˻��ؼ� ������ ��ġ�� ĳ���͸� �������ִ� Ŭ����
class CharacterCreater : public GameEngineActor
{
public:
	// constrcuter destructer
	CharacterCreater();
	~CharacterCreater();

	// delete Function
	CharacterCreater(const CharacterCreater& _Other) = delete;
	CharacterCreater(CharacterCreater&& _Other) noexcept = delete;
	CharacterCreater& operator=(const CharacterCreater& _Other) = delete;
	CharacterCreater& operator=(CharacterCreater&& _Other) noexcept = delete;

	inline void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	inline float4 OutputPlayerCreatePos()
	{
		return CreatePlayerPos_;
	}

	void MakePosition();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	GameEngineTexture* ColMap_;

	float4 CreatePlayerPos_;
};

