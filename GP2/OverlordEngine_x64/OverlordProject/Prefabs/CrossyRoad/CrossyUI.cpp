#include "stdafx.h"
#include "CrossyUI.h"

void CrossyUI::SetScore(int score)
{
	m_Score = score;
	m_ScoreTextDirty = true;
}

void CrossyUI::Initialize(const SceneContext&)
{
	m_ScoreTextDirty = true;
	m_pSmallFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/SuperMario_40.fnt");
	m_pBigFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/SuperMario_80.fnt");
}

void CrossyUI::Update(const SceneContext& sceneContext)
{
	if (m_ScoreTextDirty)
	{
		m_ScoreText = L"SCORE: " + std::to_wstring(m_Score);
		m_ScoreTextDirty = false;
	}

	if (m_GameOver)
	{
		TextRenderer::Get()->DrawText(m_pBigFont, m_GameOverText, { sceneContext.windowWidth / 2 - 240.f, sceneContext.windowHeight / 2 - 50.f }, XMFLOAT4{Colors::OrangeRed});
		TextRenderer::Get()->DrawText(m_pSmallFont, m_RestartText, { sceneContext.windowWidth / 2 - 300.f, sceneContext.windowHeight / 2 + 20.f }, XMFLOAT4{ Colors::LightYellow });
	}

	TextRenderer::Get()->DrawText(m_pSmallFont, m_ScoreText, { sceneContext.windowWidth / 2 - 90.f, 0.f });
}
