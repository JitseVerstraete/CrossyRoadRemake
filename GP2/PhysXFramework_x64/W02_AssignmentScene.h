#pragma once
#include "GameScene.h"

class W02_AssignmentScene : public GameScene
{
public:
	W02_AssignmentScene() :GameScene(L"W02AssingmentScene") {}
	~W02_AssignmentScene() override = default;
	W02_AssignmentScene(const W02_AssignmentScene& other) = delete;
	W02_AssignmentScene(W02_AssignmentScene&& other) noexcept = delete;
	W02_AssignmentScene& operator=(const W02_AssignmentScene& other) = delete;
	W02_AssignmentScene& operator=(W02_AssignmentScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;

private:
	//static level
	GameObject* m_pStaticLevel{};

	//player controlled sphere
	GameObject* m_pPlayerSphere{};

	//two other spheres

	//two destinct boxes

	//two corresponding triggers

	//two hatches that drop the spheres

	//sounds
};

