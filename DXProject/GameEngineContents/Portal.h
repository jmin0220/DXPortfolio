#pragma once

enum class PortalState
{
	NonActivate,	// Index 0 -> 
	Activate,		//		 0
	KillBoss,		//		 1
};

// Ό³Έν :
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

	void SetPortalState(PortalState _State)
	{
		PortalState_ = _State;
	}

	inline bool IsCreateBoss()
	{
		return RespawnBossTimer_ < 0.0f && RespawnBossFlg_ == true;
	}

	inline bool GetRespawnBossFlg()
	{
		return RespawnBossFlg_;
	}

	inline void PortalNextLevelOnRenderer()
	{
		Renderer_->SetFolderTextureToIndex(TEX_OBJECT_TELEPORTAL, 1);
	}

protected:
	void Start() override;
	void Update(float _DeltatTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;
	PortalState PortalState_;

	bool CollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);

	float RespawnBossTimer_;
	bool RespawnBossFlg_;
};

