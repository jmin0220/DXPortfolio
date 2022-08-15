#pragma once
#include "Drops.h"

// Ό³Έν :
class Exp : public Drops
{
public:
	// constrcuter destructer
	Exp();
	~Exp();

	// delete Function
	Exp(const Exp& _Other) = delete;
	Exp(Exp&& _Other) noexcept = delete;
	Exp& operator=(const Exp& _Other) = delete;
	Exp& operator=(Exp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

