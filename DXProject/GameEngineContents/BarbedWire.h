#pragma once
#include "Item.h"

// Ό³Έν :
class BarbedWire : public Item
{
public:
	// constrcuter destructer
	BarbedWire();
	~BarbedWire();

	// delete Function
	BarbedWire(const BarbedWire& _Other) = delete;
	BarbedWire(BarbedWire&& _Other) noexcept = delete;
	BarbedWire& operator=(const BarbedWire& _Other) = delete;
	BarbedWire& operator=(BarbedWire&& _Other) noexcept = delete;

	void Initialize() override;

protected:
	void FrameItemUpdate(float4 _PlayerPos) override;

private:
	std::list<GameEngineCollision*> CheckedMonster_;

	GameEngineCollision* Collision_;
	GameEngineTextureRenderer* EffectRenderer_;

	CollisionReturn CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
};

