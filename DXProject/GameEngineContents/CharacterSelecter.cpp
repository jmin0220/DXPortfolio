#include "PreCompile.h"
#include "GameEngineCore/GameEngineRenderer.h"
#include "CharacterSelecter.h"

CharacterSelecter::CharacterSelecter() 
	: Renderer_(nullptr)
{
}

CharacterSelecter::~CharacterSelecter() 
{
}

void CharacterSelecter::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void CharacterSelecter::Update(float _DeltaTime)
{
}

