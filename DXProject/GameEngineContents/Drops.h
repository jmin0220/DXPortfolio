#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class Drops : public GameEngineActor
{
public:
	// constrcuter destructer
	Drops();
	~Drops();

	// delete Function
	Drops(const Drops& _Other) = delete;
	Drops(Drops&& _Other) noexcept = delete;
	Drops& operator=(const Drops& _Other) = delete;
	Drops& operator=(Drops&& _Other) noexcept = delete;

	static inline void SetPlayerPos(float4 _Pos)
	{
		PlayerPos_ = _Pos;
	}

	static inline void SetColMap(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	static void CreateCoinsAndExp(int _GoldValue, int _ExpValue, float4 _Pos, GameEngineLevel* _Level);

protected:
	// 추락 판정용 맵정보
	static GameEngineTexture* ColMap_;

	void Start() override {};
	void Update(float _DeltaTime) override {};

	GameEngineTextureRenderer* Renderer_;

	float PlayerChaseTimer_;

	// 등장한 뒤 날아갈 방향
	float4 FlyDir_;

	static float4 PlayerPos_;
};

