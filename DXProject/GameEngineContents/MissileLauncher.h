#pragma once
#include "Item.h"

// Ό³Έν :
class MissileLauncher : public Item
{
public:
	// constrcuter destructer
	MissileLauncher();
	~MissileLauncher();

	// delete Function
	MissileLauncher(const MissileLauncher& _Other) = delete;
	MissileLauncher(MissileLauncher&& _Other) noexcept = delete;
	MissileLauncher& operator=(const MissileLauncher& _Other) = delete;
	MissileLauncher& operator=(MissileLauncher&& _Other) noexcept = delete;

	void Initialize() override;

	void UseItemUpdate(float4 _PlayerPos, float4 _Dir = float4::ZERO) override;

protected:

private:

};

