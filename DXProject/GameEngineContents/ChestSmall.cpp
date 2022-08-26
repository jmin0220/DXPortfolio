#include "PreCompile.h"
#include "ChestSmall.h"

ChestSmall::ChestSmall()
{
}

ChestSmall::~ChestSmall()
{
}

void ChestSmall::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

}
