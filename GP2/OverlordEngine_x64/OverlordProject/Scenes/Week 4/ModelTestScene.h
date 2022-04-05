#pragma once
#include "C:\DAE_Local\GraphicsProgramming2\GP2\OverlordEngine_x64\OverlordEngine\Scenegraph\GameScene.h"
class ModelTestScene : public GameScene
{
public:
	ModelTestScene() :GameScene(L"ModelTestScene") {}
	~ModelTestScene() override = default;

	ModelTestScene(const ModelTestScene& other) = delete;
	ModelTestScene(ModelTestScene&& other) noexcept = delete;
	ModelTestScene& operator=(const ModelTestScene& other) = delete;
	ModelTestScene& operator=(ModelTestScene&& other) noexcept = delete;
private:

	void Initialize() override;



};

