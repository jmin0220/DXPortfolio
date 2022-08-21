#include "PreCompile.h"
#include "ContentsFont.h"

ContentsFont::ContentsFont() 
	: DeathTimer_(0.0f)
	, LiveTimer_(0.0f)
	, DeathFlg_(false)
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::Start()
{
}

void ContentsFont::Update(float _DeltaTime)
{
	LiveTimer_ += _DeltaTime;

	if (LiveTimer_ >= DeathTimer_ && DeathFlg_ == true)
	{
		this->Death();
	}
}