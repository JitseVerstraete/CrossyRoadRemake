#pragma once
#include "Scenegraph/GameScene.h"

class Terrain;
class CrossyCharacter;
class CrossyFollowCam;
class CrossyUI;

class CrossyMenu : public GameScene
{
public:
	CrossyMenu() :GameScene(L"CrossyMenu") {}
	~CrossyMenu() override = default;
	CrossyMenu(const CrossyMenu& other) = delete;
	CrossyMenu(CrossyMenu&& other) noexcept = delete;
	CrossyMenu& operator=(const CrossyMenu& other) = delete;
	CrossyMenu& operator=(CrossyMenu&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void PostDraw() override;
	void OnGUI() override;

private:


	ModelAnimator* m_StartModelAnimator{};
	ModelAnimator* m_QuitModelAnimator{};

	SpriteFont* m_pFont{};


	CrossyCharacter* m_pBlancCharacter{};

	bool m_StartedHovered{ false };
	bool m_QuitHovered{ false };

};

