#include "PreCompile.h"
#include "ObjectCreater.h"
#include "ChestNormal.h"
#include "ChestBig.h"
#include "ChestLongSet.h"
#include "Portal.h"
#include "Bouncer.h"
#include "AttackDroneItem.h"
#include "MissileDroneItem.h"

GameEngineTexture* ObjectCreater::ColMap_ = nullptr;

ObjectCreater::ObjectCreater() 
{
}

ObjectCreater::~ObjectCreater() 
{
}


void ObjectCreater::CreateObject()
{
	int ScaleX = ColMap_->GetScale().ix() - 1;
	int ScaleY = ColMap_->GetScale().iy() - 1;

	PixelColor Red;
	Red.r = 255; Red.g = 0; Red.b = 0; Red.a = 255;
	PixelColor Green;
	Green.r = 10; Green.g = 255; Green.b = 10; Green.a = 255;
	PixelColor Blue;
	Blue.r = 0; Blue.g = 0; Blue.b = 255; Blue.a = 255;
	PixelColor Black;
	Black.r = 0; Black.g = 0; Black.b = 0; Black.a = 255;
	PixelColor Sky;
	Sky.r = 0; Sky.g = 10; Sky.b = 200; Sky.a = 255;
	PixelColor AtkDrone;
	AtkDrone.r = 0; AtkDrone.g = 0; AtkDrone.b = 1; AtkDrone.a = 255;
	PixelColor missileDrone;
	missileDrone.r = 0; missileDrone.g = 0; missileDrone.b = 2; missileDrone.a = 255;

	for (int x = 0; x <= ScaleX; x++)
	{
		for (int y = 0; y <= ScaleY; y++)
		{
			// Color R     => ChestNormal
			//       G     => ChestBig
			//       B     => ChestLongSet
			// Color Black => Teleportal
			// Color Sky   => Bouncer
			// 0, 0, 1     => AttackDrone
			// 0, 0, 2     => MissileDrone
 
			PixelColor tmpColor = ColMap_->GetPixelToPixelColor(x, y);
			// 7963 2783
			if (x == 7963 && y == 2783)
			{
				int a = 0;
			}

			if (tmpColor.r == 0 && tmpColor.g == 0 && tmpColor.b == 0)
			{
				int a = 0;
			}

			if (tmpColor.Color == Red.Color)
			{
				ChestNormal* TmpChest = GetLevel()->CreateActor<ChestNormal>();
				TmpChest->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest)});

				continue;
			}
			if (tmpColor.Color == Green.Color)
			{
				ChestBig* TmpChest = GetLevel()->CreateActor<ChestBig>();
				TmpChest->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest) });

				continue;
			}
			if (tmpColor.Color == Blue.Color)
			{ 
				ChestLongSet* TmpChest = GetLevel()->CreateActor<ChestLongSet>();
				TmpChest->CreateChestLongSet({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest) });

				continue;
			}
			if (tmpColor.Color == Black.Color)
			{
				tmpPortal_ = GetLevel()->CreateActor<Portal>();
				tmpPortal_->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Teleportal) });
				
				continue;
			}
			if (tmpColor.Color == Sky.Color)
			{
				Bouncer* TmpBouncer = GetLevel()->CreateActor<Bouncer>();
				TmpBouncer->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest) });

				continue;
			}
			if (tmpColor.Color == AtkDrone.Color)
			{
				AttackDroneItem* TmpDrone = GetLevel()->CreateActor<AttackDroneItem>();
				TmpDrone->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest) });

				continue;
			}
			if (tmpColor.Color == missileDrone.Color)
			{
				MissileDroneItem* TmpDrone = GetLevel()->CreateActor<MissileDroneItem>();
				TmpDrone->GetTransform().SetWorldPosition({ static_cast<float>(x), static_cast<float>(-y), static_cast<float>(ZOrder::Chest) });

				continue;
			}
		}
	}
}
