#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineTextureRenderer*> FontRendererVector_;


public:
	void CreateFontRenderer(std::string _Text, float4 _Pivot);

	void ChangeFontRenderer(std::string _Text, float4 _Pivot);

};


enum class FONT_INDEX
{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Dollar,							//$
	Exclamaion_Mark,				//!
	Empty,
};