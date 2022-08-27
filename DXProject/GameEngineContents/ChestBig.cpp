#include "PreCompile.h"
#include "ChestBig.h"

ChestBig::ChestBig() 
{
}

ChestBig::~ChestBig() 
{
}

void ChestBig::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
}