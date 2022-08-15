#pragma once
#include "Drops.h"

// Ό³Έν :
class Gold : public Drops
{
public:
	// constrcuter destructer
	Gold();
	~Gold();

	// delete Function
	Gold(const Gold& _Other) = delete;
	Gold(Gold&& _Other) noexcept = delete;
	Gold& operator=(const Gold& _Other) = delete;
	Gold& operator=(Gold&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

