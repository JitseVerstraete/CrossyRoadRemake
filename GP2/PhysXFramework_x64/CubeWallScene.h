#pragma once
#include "GameScene.h"

class CubeWallScene final : public GameScene
{
public:
	CubeWallScene() :GameScene(L"CubeWallScene") {}
	~CubeWallScene() override = default;
	CubeWallScene(const CubeWallScene& other) = delete;
	CubeWallScene(CubeWallScene&& other) noexcept = delete;
	CubeWallScene& operator=(const CubeWallScene& other) = delete;
	CubeWallScene& operator=(CubeWallScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;
	void OnSceneActivated() override;
	void OnSceneDeactivated() override;

private:
	enum class InputIds
	{
		MoveRight,
		MoveLeft,
		MoveForward,
		MoveBack,
		Jump
	};

	GameObject* m_pSphere{};
	std::vector<GameObject*> m_pCubes;

	


};
