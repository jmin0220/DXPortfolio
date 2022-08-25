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
	bool CollisionCheckPlayer(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool CollisionCheckMonster(GameEngineCollision* _This, GameEngineCollision* _Other);

	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	
};

