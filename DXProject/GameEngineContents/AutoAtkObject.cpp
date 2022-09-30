#include "PreCompile.h"
#include "AutoAtkObject.h"
#include "Monster.h"

std::list<Monster*> AutoAtkObject::Monster_ = {};

AutoAtkObject::AutoAtkObject()
	: TargetPos_(float4::ZERO)
	, ToEnemyLength_(FLT_MAX)
	, ToEnemyPos_(float4::ZERO)
{
}

AutoAtkObject::~AutoAtkObject() 
{
}

bool AutoAtkObject::FindChaseMonster(float _FindLength)
{
	ToEnemyLength_ = FLT_MAX;
	ToEnemyPos_ = float4::ZERO;
	TargetPos_ = float4::ZERO;

	for (Monster* tmpMonster : Monster_)
	{
		float tmpLength = (this->GetTransform().GetWorldPosition() - tmpMonster->GetTransform().GetWorldPosition()).Length();

		if (tmpLength < ToEnemyLength_ && tmpLength <= _FindLength)
		{
			ToEnemyLength_ = tmpLength;
			ToEnemyPos_ = tmpMonster->GetTransform().GetWorldPosition();
		}
	}

	if (ToEnemyPos_.CompareInt2D(float4::ZERO))
	{
		return false;
	}

	TargetPos_ = ToEnemyPos_;

	return true;
}