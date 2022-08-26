#include "PreCompile.h"
#include "ChestParent.h"
#include <GameEngineBase/GameEngineRandom.h>

ChestParent::ChestParent()
	: Renderer_(nullptr)
	, GoldValue_(0)
	, ExpValue_(0)
{
}

ChestParent::~ChestParent()
{
}

void ChestParent::Start()
{
	AnimationInit();

	// ��ü���� �ٸ� ���, ����ġ�� ����
	// TODO::�ð����� �ٸ� ����ġ, ��带 ����
	GameEngineRandom* tmpRandom = new GameEngineRandom();
	GoldValue_ = tmpRandom->RandomInt(4 * 1, 5 * 1);
	ExpValue_ = tmpRandom->RandomInt(10 * 1, 13 * 1);
}

void ChestParent::Update(float _DeltaTime)
{

}