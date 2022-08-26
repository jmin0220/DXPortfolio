#include "PreCompile.h"
#include "ChestBig.h"

ChestBig::ChestBig() 
{
}

ChestBig::~ChestBig() 
{
}

void ChestBig::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
}