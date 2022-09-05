#pragma once

// Ό³Έν :
class ChestLong;
class ChestLongSet : public GameEngineActor
{
public:
	// constrcuter destructer
	ChestLongSet();
	~ChestLongSet();

	// delete Function
	ChestLongSet(const ChestLongSet& _Other) = delete;
	ChestLongSet(ChestLongSet&& _Other) noexcept = delete;
	ChestLongSet& operator=(const ChestLongSet& _Other) = delete;
	ChestLongSet& operator=(ChestLongSet&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);

	ChestLong* ChestLong[3];

private:

};

