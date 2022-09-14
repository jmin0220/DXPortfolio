#pragma once
#include "Item.h"

// Ό³Έν :
class Sawmerang : public Item
{
public:
	// constrcuter destructer
	Sawmerang();
	~Sawmerang();

	// delete Function
	Sawmerang(const Sawmerang& _Other) = delete;
	Sawmerang(Sawmerang&& _Other) noexcept = delete;
	Sawmerang& operator=(const Sawmerang& _Other) = delete;
	Sawmerang& operator=(Sawmerang&& _Other) noexcept = delete;

	void Initialize() override;

	void UseItemUpdate(float4 _PlayerPos, float4 _Dir = float4::ZERO) override;

protected:

private:

};

