#pragma once

// ���� :
class Monster;
class AutoAtkObject : public GameEngineActor
{
public:
	// constrcuter destructer
	AutoAtkObject();
	~AutoAtkObject();

	// delete Function
	AutoAtkObject(const AutoAtkObject& _Other) = delete;
	AutoAtkObject(AutoAtkObject&& _Other) noexcept = delete;
	AutoAtkObject& operator=(const AutoAtkObject& _Other) = delete;
	AutoAtkObject& operator=(AutoAtkObject&& _Other) noexcept = delete;

	static void SetMonsterList(std::list<Monster*> _Monster)
	{
		Monster_ = _Monster;
	}

protected:

	void Start() override {};
	void Update(float _DeltaTime) override {};

	// ������ ����
	static std::list<Monster*> Monster_;
};

