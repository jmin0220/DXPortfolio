#include "PreCompile.h"
#include "Drops.h"

float4 Drops::PlayerPos_ = float4::ZERO;

Drops::Drops() 
	: PlayerChaseTimer_(0.0f)
{
}

Drops::~Drops() 
{
}