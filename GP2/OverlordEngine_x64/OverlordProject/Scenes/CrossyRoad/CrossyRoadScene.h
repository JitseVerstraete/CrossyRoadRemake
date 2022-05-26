#pragma once
#include "Scenegraph/GameScene.h"

class Terrain;
class CrossyCharacter;
class CrossyFollowCam;

class CrossyRoadScene : public GameScene
{
public:
	CrossyRoadScene() :GameScene(L"CrossyRoadScene") {}
	~CrossyRoadScene() override ;
	CrossyRoadScene(const CrossyRoadScene& other) = delete;
	CrossyRoadScene(CrossyRoadScene&& other) noexcept = delete;
	CrossyRoadScene& operator=(const CrossyRoadScene& other) = delete;
	CrossyRoadScene& operator=(CrossyRoadScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void PostDraw() override;
	void OnGUI() override;

private:
	bool m_GameOver{ false };
	const int m_MaxWidth{ 4 };
	const int m_TerrainSlicesAhead{ 16 };

	//player object
	CrossyCharacter* m_pPlayerCharacter = nullptr;

	//terrain object
	Terrain* m_pTerrain = nullptr;

	//camera
	CrossyFollowCam* m_pFollowCamera = nullptr;
};

