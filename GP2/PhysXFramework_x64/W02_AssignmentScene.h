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

	void onTrigger(PxTriggerPair* pairs, PxU32 count) override;

private:
	//static level
	GameObject* m_pStaticLevel{};

	//player controlled sphere
	GameObject* m_pPlayerSphere{};

	//two hatches that drop the spheres
	GameObject* m_pBlueHatch{};
	GameObject* m_pRedHatch{};

	//two other spheres on the hatches
	GameObject* m_pBlueSphere{};
	GameObject* m_pRedSphere{};

	//two destinct boxes
	GameObject* m_pBlueBox{};
	GameObject* m_pRedBox{};

	//two corresponding triggers
	PxShape* m_pBlueTrigger{};
	PxShape* m_pRedTrigger{};

	//sounds
	FMOD::Sound* m_pBellSound{};
};

