#include "PreCompile.h"
#include "ContentsFont.h"

ContentsFont::ContentsFont() 
	: DeathTimer_(0.0f)
	, LiveTimer_(0.0f)
	, DeathFlg_(false)
	, IsBulletDmg_(false)
	, UpperMoveSpeed_(60.0f)
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

	if (true == IsBulletDmg_)
	{
		this->GetTransform().SetWorldMove(GetTransform().GetUpVector() * UpperMoveSpeed_ * _DeltaTime);
	}
}