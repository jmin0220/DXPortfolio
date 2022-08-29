#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class TextType
{
	Normal,
	Large,
	Crit,
};

// 설명 :
class ContentsFont : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsFont();
	~ContentsFont();

	// delete Function
	ContentsFont(const ContentsFont& _Other) = delete;
	ContentsFont(ContentsFont&& _Other) noexcept = delete;
	ContentsFont& operator=(const ContentsFont& _Other) = delete;
	ContentsFont& operator=(ContentsFont&& _Other) noexcept = delete;

	inline void SetDeathTimer(float _Timer = 1.0f)
	{
		DeathTimer_ = _Timer;
		DeathFlg_ = true;
	}

	inline bool GetDeathFlg()
	{
		return DeathFlg_;
	}

	inline void SetIsBulletDmg(bool _Flg)
	{
		IsBulletDmg_ = _Flg;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineTextureRenderer*> FontRendererVector_;

	float DeathTimer_;
	float LiveTimer_;
	bool DeathFlg_;
	bool IsBulletDmg_;

	float UpperMoveSpeed_;
	// 투명도
	float Invisible_;

public:
	// 폰트 렌더러를 새로 생성
	template<typename RendererType>
	void CreateFontRenderer(std::string _Text, float4 _Pivot, TextType _Type = TextType::Normal)
	{
		FontRendererVector_.reserve(_Text.size());
		size_t FontSize = _Text.size();
		std::string FontSizeSetter = "";

		// 설정된 text의 글자수만큼 렌더러를 생성
		for (int i = 0; i < FontSize; ++i)
		{
			RendererType* TmpRenderer = CreateComponent<RendererType>();
			FontRendererVector_.push_back(static_cast<GameEngineTextureRenderer*>(TmpRenderer));
		}

		switch (_Type)
		{
		case TextType::Normal:
			FontSizeSetter = "";
			break;
		case TextType::Large:
			FontSizeSetter = "Large";
			break;
		case TextType::Crit:
			FontSizeSetter = "Crit";
			break;
		default:
			FontSizeSetter = "";
			break;
		}

		// 설정된 text에 맞춰 랜더러에 텍스쳐를 설정
		float MarginX = 0;
		for (int Count_ = 0; Count_ < FontSize; ++Count_)
		{
			switch (_Text.c_str()[Count_])
			{
			case '0':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_0.png");
				break;
			case '1':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_1.png");
				MarginX -= FontRendererVector_.at(Count_)->GetCurTexture()->GetScale().hx();
				break;
			case '2':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_2.png");
				break;
			case '3':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_3.png");
				break;
			case '4':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_4.png");
				break;
			case '5':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_5.png");
				break;
			case '6':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_6.png");
				break;
			case '7':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_7.png");
				break;
			case '8':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_8.png");
				break;
			case '9':
				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_9.png");
				break;
			case '!':
				// 존재하지 않는 텍스쳐라면 Normal사이즈의 0
				if (_Type == TextType::Large)
				{
					FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_0);
					break;
				}

				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_10.png");
				break;
			case '$':
				// 존재하지 않는 텍스쳐라면 Normal사이즈의 0
				if (_Type == TextType::Large || _Type == TextType::Crit)
				{
					FontRendererVector_.at(Count_)->SetTexture(TEX_FONT_NORMAL_0);
					break;
				}

				FontRendererVector_.at(Count_)->SetTexture(FontName + FontSizeSetter + "_11.png");
				break;

			default:
				FontRendererVector_.at(Count_)->SetTexture("NSet.png");
				break;
			}
			FontRendererVector_.at(Count_)->ScaleToTexture();

			// 위치 조정
			FontRendererVector_.at(Count_)->GetTransform().SetLocalPosition({ _Pivot.x + MarginX, 0 + _Pivot.y });
			MarginX += FontRendererVector_.at(Count_)->GetCurTexture()->GetScale().x + 2.0f;

			// 1일때 다음 글자의 포지션을 조정
			// 왜?
			if (_Text.c_str()[Count_] == '1')
			{
				MarginX += FontRendererVector_.at(Count_)->GetCurTexture()->GetScale().hx();
			}

		}

		// 크리티컬일경우 '!' 추가
		if (_Type == TextType::Crit)
		{
			RendererType* TmpRenderer = CreateComponent<RendererType>();
			TmpRenderer->SetTexture(TEX_FONT_CRIT_10);
			TmpRenderer->ScaleToTexture();

			MarginX -= TmpRenderer->GetCurTexture()->GetScale().hx();
			TmpRenderer->GetTransform().SetLocalPosition({ _Pivot.x + MarginX, 0 + _Pivot.y });

			FontRendererVector_.push_back(static_cast<GameEngineTextureRenderer*>(TmpRenderer));
		}
	}

	// 이미 존재하는 폰트 렌더러를 수정
	template<typename RendererType>
	void ChangeFontRenderer(std::string _Text, float4 _Pivot, TextType _Type = TextType::Normal)
	{
		// 저장되어있던 랜더러를 삭제
		std::vector<GameEngineTextureRenderer*>::iterator Start = FontRendererVector_.begin();

		for (Start; Start != FontRendererVector_.end(); ++Start)
		{
			if ((*Start) != nullptr)
			{
				(*Start)->Death();
			}
		}

		FontRendererVector_.clear();

		// 설정된 텍스트로 렌더러를 다시 생성
		CreateFontRenderer<RendererType>(_Text, _Pivot, _Type);
	}
};