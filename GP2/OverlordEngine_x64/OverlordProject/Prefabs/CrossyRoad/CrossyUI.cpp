#include "stdafx.h"
#include "CrossyUI.h"

void CrossyUI::SetScore(int score)
{
	m_Score = score;
	m_ScoreTextDirty = true;
}

void CrossyUI::Initialize(const SceneContext&)
{
	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/Consolas_32.fnt");
}

void CrossyUI::Update(const SceneContext& sceneContext)
{
	if (m_ScoreTextDirty)
	{

		m_ScoreTextDirty = false;
	}


	TextRenderer::Get()->DrawText(m_pFont, L"Sup", { sceneContext.windowWidth / 9.f * 4.f, 0.f });
}
