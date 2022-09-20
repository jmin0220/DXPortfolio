#pragma once

enum class PortalState
{
	NonActivate,	// Index 0
	Activate,		//		 1
	Sleep,			//		 2
};

// ���� :
class Portal : public GameEngineActor
{
public:
	// constrcuter destructer
	Portal();
	~Portal();

	// delete Function
	Portal(const Portal& _Other) = delete;
	Portal(Portal&& _Other) noexcept = delete;
	Portal& operator=(const Portal& _Other) = delete;
	Portal& operator=(Portal&& _Other) noexcept = delete;

	PortalState GetPortalState()
	{
		return PortalState_;
	}

protected:
	void Start() override;
	void Update(float _DeltatTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	PortalState PortalState_;

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	// TODO::�ܺο��� Portal�� ���¸� ����
};

