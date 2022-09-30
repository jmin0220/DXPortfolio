#pragma once
#include "Drone.h"

// Ό³Έν :
class DroneItem : public Drone
{
public:
	// constrcuter destructer
	DroneItem();
	~DroneItem();

	// delete Function
	DroneItem(const DroneItem& _Other) = delete;
	DroneItem(DroneItem&& _Other) noexcept = delete;
	DroneItem& operator=(const DroneItem& _Other) = delete;
	DroneItem& operator=(DroneItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void Initialize() {};

	GameEngineTextureRenderer* Renderer_;
	GameEngineFontRenderer* FontRenderer_;
	GameEngineCollision* Collision_;

	int DronePrice_;

	CollisionReturn CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual void AddDrone() {};
};

