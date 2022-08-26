#include "PreCompile.h"
#include "ChestParent.h"
#include "ChestLong.h"

ChestLong::ChestLong() 
{
}

ChestLong::~ChestLong() 
{
}

void ChestLong::AnimationInit()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

}

