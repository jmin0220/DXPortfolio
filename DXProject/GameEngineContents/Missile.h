#pragma once

// Ό³Έν :
class MissileSmokeRenderer;
class Missile : public GameEngineActor
{
public:
	// constrcuter destructer
	Missile();
	~Missile();

	// delete Function
	Missile(const Missile& _Other) = delete;
	Missile(Missile&& _Other) noexcept = delete;
	Missile& operator=(const Missile& _Other) = delete;
	Missile& operator=(Missile&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;	
};

