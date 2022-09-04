#pragma once
#include "Item.h"

// Ό³Έν :
class Warbanner : public Item
{
public:
	// constrcuter destructer
	Warbanner();
	~Warbanner();

	// delete Function
	Warbanner(const Warbanner& _Other) = delete;
	Warbanner(Warbanner&& _Other) noexcept = delete;
	Warbanner& operator=(const Warbanner& _Other) = delete;
	Warbanner& operator=(Warbanner&& _Other) noexcept = delete;

	void Initialize() override;

protected:

private:

};

