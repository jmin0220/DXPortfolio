#include "PreCompile.h"
#include "ContentsFont.h"

ContentsFont::ContentsFont() 
	: DeathTimer_(0.0f)
	, LiveTimer_(0.0f)
	, DeathFlg_(false)
	, IsBulletDmg_(false)
	, UpperMoveSpeed_(60.0f)
	, Invisible_(1.0f)
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

		// Death���� ���� �ð��� 
		if (DeathTimer_ - LiveTimer_ <= 0.5)
		{
			// ���� ����
			for (auto& Renderer : FontRendererVector_)
			{
				Invisible_ -= _DeltaTime * 2;
				Renderer->GetPixelData().MulColor.a = Invisible_;
			}
		}
	}
}