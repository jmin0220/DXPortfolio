#pragma once

// Ό³Έν :
class Bouncer : public GameEngineActor
{
public:
	// constrcuter destructer
	Bouncer();
	~Bouncer();

	// delete Function
	Bouncer(const Bouncer& _Other) = delete;
	Bouncer(Bouncer&& _Other) noexcept = delete;
	Bouncer& operator=(const Bouncer& _Other) = delete;
	Bouncer& operator=(Bouncer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	CollisionReturn CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	CollisionReturn CollisionCheckMonster(GameEngineCollision* _This, GameEngineCollision* _Other);

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	
};

