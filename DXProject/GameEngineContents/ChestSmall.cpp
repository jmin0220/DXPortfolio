#include "PreCompile.h"
#include "ChestSmall.h"

ChestSmall::ChestSmall()
{
}

ChestSmall::~ChestSmall()
{
}

void ChestSmall::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

}
