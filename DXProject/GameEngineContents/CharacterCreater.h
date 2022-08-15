#pragma once
#include "GameEngineCore/GameEngineActor.h"

// 설명 : 맵을 검색해서 적정한 위치에 캐릭터를 생성해주는 클래스
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

	inline void SetCurPlayerPos(float4 _Pos)
	{
		CurPlayerPos_ = _Pos;
	}

	inline float4 OutputPlayerCreatePos()
	{
		return CreatePlayerPos_;
	}

	inline float4 OutputMonsterCreatePos()
	{
		return CreateMonsterPos_;
	}

	void MakePlayerPosition();
	void MakeMonsterPosition();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	float4 MakePosition(int _CreateMod);

	static GameEngineTexture* ColMap_;

	static float4 CurPlayerPos_;
	float4 CreatePlayerPos_;

	float4 CreateMonsterPos_;
};

