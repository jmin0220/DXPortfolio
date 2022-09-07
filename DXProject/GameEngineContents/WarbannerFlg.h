#pragma once
#include "Drops.h"

// Ό³Έν :
class WarbannerFlg : public Drops
{
public:
	// constrcuter destructer
	WarbannerFlg();
	~WarbannerFlg();

	// delete Function
	WarbannerFlg(const WarbannerFlg& _Other) = delete;
	WarbannerFlg(WarbannerFlg&& _Other) noexcept = delete;
	WarbannerFlg& operator=(const WarbannerFlg& _Other) = delete;
	WarbannerFlg& operator=(WarbannerFlg&& _Other) noexcept = delete;

	void GroundFall();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* CircleRenderer_;

};

