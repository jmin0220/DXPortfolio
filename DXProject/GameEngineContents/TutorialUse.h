#pragma once

// Ό³Έν :
class TutorialUse : public GameEngineActor
{
public:
	// constrcuter destructer
	TutorialUse();
	~TutorialUse();

	// delete Function
	TutorialUse(const TutorialUse& _Other) = delete;
	TutorialUse(TutorialUse&& _Other) noexcept = delete;
	TutorialUse& operator=(const TutorialUse& _Other) = delete;
	TutorialUse& operator=(TutorialUse&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;

};

