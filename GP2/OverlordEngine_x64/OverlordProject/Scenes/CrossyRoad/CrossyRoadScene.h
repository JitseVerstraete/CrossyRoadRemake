#pragma once
#include "Scenegraph/GameScene.h"
class CrossyRoadScene : public GameScene
{
public:
	CrossyRoadScene() :GameScene(L"CrossyRoadScene") {}
	~CrossyRoadScene() override = default;
	CrossyRoadScene(const CrossyRoadScene& other) = delete;
	CrossyRoadScene(CrossyRoadScene&& other) noexcept = delete;
	CrossyRoadScene& operator=(const CrossyRoadScene& other) = delete;
	CrossyRoadScene& operator=(CrossyRoadScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void OnGUI() override;

};

