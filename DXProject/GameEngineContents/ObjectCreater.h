#pragma once
#include "Portal.h"

// Ό³Έν :
class ObjectCreater : public GameEngineActor
{
public:
	// constrcuter destructer
	ObjectCreater();
	~ObjectCreater();

	// delete Function
	ObjectCreater(const ObjectCreater& _Other) = delete;
	ObjectCreater(ObjectCreater&& _Other) noexcept = delete;
	ObjectCreater& operator=(const ObjectCreater& _Other) = delete;
	ObjectCreater& operator=(ObjectCreater&& _Other) noexcept = delete;

	inline void SetColMapInfo(GameEngineTexture* _ColMap)
	{
		ColMap_ = _ColMap;
	}

	Portal* GetPortal()
	{
		return tmpPortal_;
	}

	void CreateObject();

private:
	static GameEngineTexture* ColMap_;
	Portal* tmpPortal_;
};

