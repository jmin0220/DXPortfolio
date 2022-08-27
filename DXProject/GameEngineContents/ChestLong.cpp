#include "PreCompile.h"
#include "ChestParent.h"
#include "ChestLong.h"

ChestLong::ChestLong() 
{
}

ChestLong::~ChestLong() 
{
}

void ChestLong::Initialize()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

}

