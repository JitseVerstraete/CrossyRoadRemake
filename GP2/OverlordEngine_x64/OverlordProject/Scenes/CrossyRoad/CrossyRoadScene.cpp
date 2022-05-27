#include "stdafx.h"
#include "CrossyRoadScene.h"


#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"
#include "Materials/Post/PostVignette.h"

#include "Prefabs/CrossyRoad/Terrain.h"
#include "Prefabs/CrossyRoad/CrossyCharacter.h"
#include "Prefabs/CrossyRoad/CrossyFollowCam.h"
#include "Prefabs/CrossyRoad/CrossyUI.h"


CrossyRoadScene::~CrossyRoadScene()
{
	if (m_pPlayerCharacter && m_pPlayerCharacter->IsDead())
	{
		delete m_pPlayerCharacter;
	};
}

void CrossyRoadScene::Initialize()
{

	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.drawPhysXDebug = false;
	m_SceneContext.pLights->SetDirectionalLight({ -5.f, 10.f, 0.f }, m_LightDir);

	ShadowMapRenderer::Get()->SetProjectionSize(15.f);



	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);


	m_pPlayerCharacter = AddChild(new CrossyCharacter(m_MaxWidth));
	m_pTerrain = AddChild(new Terrain(m_pPlayerCharacter, m_TerrainSlicesAhead, m_MaxWidth));
	m_pFollowCamera = AddChild(new CrossyFollowCam(m_pPlayerCharacter, 50.f, -10.f, 25.f, 2, 20.f));
	m_pPlayerCharacter->SetTerrain(m_pTerrain);
	m_pUiObject = AddChild(new CrossyUI());

	AddPostProcessingEffect(MaterialManager::Get()->CreateMaterial<PostVignette>());

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
	inputAction = InputAction(Respawn, InputState::pressed, VK_SPACE);
	m_SceneContext.pInput->AddInputAction(inputAction);
}

void CrossyRoadScene::Update()
{

	if (m_pPlayerCharacter->IsDead() && !m_GameOver)
	{
		RemoveChild(m_pPlayerCharacter, false);
		m_GameOver = true;


	}

	if (m_GameOver && m_SceneContext.pInput->IsActionTriggered(Respawn))
	{
		//spawn new terrain
		m_pTerrain->Reset();

		//reset player character & camera
		m_pPlayerCharacter->Resapwn();
		if (m_pFollowCamera) m_pFollowCamera->Reset();

		//add child back to the game
		AddChild(m_pPlayerCharacter);

		//reset game over bool
		m_GameOver = false;
	}

	
	m_SceneContext.pLights->SetDirectionalLight({ -5.f, 5.f, (float)m_pPlayerCharacter->GetScore() - 2.1f}, m_LightDir);
	m_pUiObject->SetScore(m_pPlayerCharacter->GetScore());
	m_pUiObject->SetGameOver(m_GameOver);
}

void CrossyRoadScene::PostDraw()
{
	//ShadowMapRenderer::Get()->Debug_DrawDepthSRV({ m_SceneContext.windowWidth - 10.f, 10.f }, { 0.2f, 0.2f }, { 1.f,0.f });

}


void CrossyRoadScene::OnGUI()
{
}
