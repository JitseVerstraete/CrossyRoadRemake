#pragma once
class CrossyUI : public GameObject
{
public:
	CrossyUI() = default;
	~CrossyUI() override = default;

	CrossyUI(const CrossyUI& other) = delete;
	CrossyUI(CrossyUI&& other) noexcept = delete;
	CrossyUI& operator=(const CrossyUI& other) = delete;
	CrossyUI& operator=(CrossyUI&& other) noexcept = delete;

	void SetScore(int score);
	void SetGameOver(bool gameOver) { m_GameOver = gameOver; }

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:
	int m_Score{0};
	bool m_GameOver{ false };
	SpriteFont* m_pSmallFont{};
	SpriteFont* m_pBigFont{};

	bool m_ScoreTextDirty{ false };
	std::wstring m_ScoreText{};

	const std::wstring m_GameOverText{ L"game over" };
	const std::wstring m_RestartText{ L"press space to restart" };
};

