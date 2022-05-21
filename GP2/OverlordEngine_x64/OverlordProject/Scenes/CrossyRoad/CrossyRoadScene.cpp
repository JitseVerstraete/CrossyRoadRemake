#include "stdafx.h"
#include "CrossyRoadScene.h"


#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

#include "Prefabs/CrossyRoad/Terrain.h"
#include "Prefabs/CrossyRoad/CrossyCharacter.h"
#include "Prefabs/CrossyRoad/CrossyFollowCam.h"


void CrossyRoadScene::Initialize()
{
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	m_pPlayerCharacter = AddChild(new CrossyCharacter());
	m_pTerrain = AddChild(new Terrain(m_pPlayerCharacter, 10));  
	m_pFollowCamera = AddChild(new CrossyFollowCam(m_pPlayerCharacter, 50.f, -10.f, 25.f, 2, 20.f));


	//input actions
	auto inputAction = InputAction(PressForward, InputState::pressed, VK_UP);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(PressBackward, InputState::pressed, VK_DOWN);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(PressLeft, InputState::pressed, VK_LEFT);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(PressRight, InputState::pressed, VK_RIGHT);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(ReleaseForward, InputState::released, VK_UP);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(ReleaseBackward, InputState::released, VK_DOWN);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(ReleaseLeft, InputState::released, VK_LEFT);
	m_SceneContext.pInput->AddInputAction(inputAction);
	inputAction = InputAction(ReleaseRight, InputState::released, VK_RIGHT);
	m_SceneContext.pInput->AddInputAction(inputAction);

}

void CrossyRoadScene::OnGUI()
{
}
