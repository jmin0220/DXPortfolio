#pragma once
#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineCore.h>

// Ό³Έν :
class RiskOfRain : public GameEngineCore
{
public:
	// constrcuter destructer
	RiskOfRain();
	~RiskOfRain();

	// delete Function
	RiskOfRain(const RiskOfRain& _Other) = delete;
	RiskOfRain(RiskOfRain&& _Other) noexcept = delete;
	RiskOfRain& operator=(const RiskOfRain& _Other) = delete;
	RiskOfRain& operator=(RiskOfRain&& _Other) noexcept = delete;

	std::string GetWindowTitle() override
	{
		return "RiskOfRain";
	}
protected:
	void Start() override;

	void Update(float _DeltaTime) override;

	void End() override;

private:

};

