#pragma once
#include "Item.h"

// Ό³Έν :
class AtGMissileMk1 : public Item
{
public:
	// constrcuter destructer
	AtGMissileMk1();
	~AtGMissileMk1();

	// delete Function
	AtGMissileMk1(const AtGMissileMk1& _Other) = delete;
	AtGMissileMk1(AtGMissileMk1&& _Other) noexcept = delete;
	AtGMissileMk1& operator=(const AtGMissileMk1& _Other) = delete;
	AtGMissileMk1& operator=(AtGMissileMk1&& _Other) noexcept = delete;

	void Initialize() override;

protected:
	void AtkItemUpdate(float4 _PlayerPos) override;

};

