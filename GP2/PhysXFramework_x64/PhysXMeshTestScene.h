#pragma once
#include "GameScene.h"

class PhysXMeshTestScene : public GameScene
{
public:
	PhysXMeshTestScene() :GameScene(L"BouncingBallsScene") {}
	~PhysXMeshTestScene() override = default;
	PhysXMeshTestScene(const PhysXMeshTestScene& other) = delete;
	PhysXMeshTestScene(PhysXMeshTestScene&& other) noexcept = delete;
	PhysXMeshTestScene& operator=(const PhysXMeshTestScene& other) = delete;
	PhysXMeshTestScene& operator=(PhysXMeshTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;

	void onTrigger(PxTriggerPair* pairs, PxU32 count) override;


private:
	GameObject* m_pChairConvex{};
	GameObject* m_pChairTriangle{};

	GameObject* m_pSphere{};
};

