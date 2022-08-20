#include "PreCompile.h"
#include "ContentsFont.h"

ContentsFont::ContentsFont() 
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
}

void ContentsFont::CreateFontRenderer(std::string _Text, float4 _Pivot)
{
	FontRendererVector_.reserve(_Text.size());
	size_t FontSize = _Text.size();

	// ������ text�� ���ڼ���ŭ �������� ����
	for (int i = 0; i < FontSize; ++i)
	{
		GameEngineTextureRenderer* TmpRenderer = CreateComponent<GameEngineTextureRenderer>();
		FontRendererVector_.push_back(TmpRenderer);
	}

	// ������ text�� ���� �������� �ؽ��ĸ� ����
	float MarginX = 0;
	for (int Count_ = 0; Count_ < FontSize; ++Count_)
	{
		switch (_Text.c_str()[Count_])
		{
		case '0':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_0);
			break;
		case '1':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_1);
			break;
		case '2':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_2);
			break;
		case '3':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_3);
			break;
		case '4':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_4);
			break;
		case '5':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_5);
			break;
		case '6':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_6);
			break;
		case '7':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_7);
			break;
		case '8':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_8);
			break;
		case '9':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_9);
			break;
		case '!':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_10);
			break;
		case '$':
			FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_11);
			break;

		default:
			FontRendererVector_.at(Count_)->SetTexture("NSet.png");
			break;
		}
		FontRendererVector_.at(Count_)->ScaleToTexture();

		// ��ġ ����
		FontRendererVector_.at(Count_)->GetTransform().SetWorldPosition({ _Pivot.x + MarginX, 0 + _Pivot.y });
		MarginX += FontRendererVector_.at(Count_)->GetCurTexture()->GetScale().x + 1.5f;
	}
}

void ContentsFont::ChangeFontRenderer(std::string _Text, float4 _Pivot)
{
	// ����Ǿ��ִ� �������� ����
	std::vector<GameEngineTextureRenderer*>::iterator Start = FontRendererVector_.begin();

	for (Start; Start != FontRendererVector_.end(); ++Start)
	{
		if ((*Start) != nullptr)
		{
			(*Start)->Death();
		}
	}

	FontRendererVector_.clear();

	// ������ �ؽ�Ʈ�� �������� �ٽ� ����
	CreateFontRenderer(_Text, _Pivot);
}
