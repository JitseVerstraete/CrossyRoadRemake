#include "stdafx.h"
#include "CrossyMenu.h"


#include "Prefabs/CrossyRoad/CrossyCharacter.h"
#include "Prefabs/CrossyRoad/Terrain.h"

#include "Materials/DiffuseMaterial_Skinned.h"


void CrossyMenu::Initialize()
{
	m_SceneContext.settings.enableOnGUI = false;
	m_SceneContext.settings.showInfoOverlay = false;
	m_SceneContext.settings.drawGrid = false;
	m_SceneContext.settings.drawPhysXDebug = false;



	//CAMERA
	GameObject* pCam = AddChild(new GameObject());
	CameraComponent* pCamComp = pCam->AddComponent(new CameraComponent());
	//pCamComp->UseOrthographicProjection();
	pCamComp->SetOrthoSize(8.f);

	float distance = 10.f;
	float pitch{ 20.f };
	float yaw{ 0.f };
	pCam->GetTransform()->Rotate(pitch, yaw, 0.f);

	//lookat translation
	XMFLOAT3 forward{ sin(XMConvertToRadians(yaw)) * cos(XMConvertToRadians(pitch)) ,
					sin(XMConvertToRadians(-pitch)),
					cos(XMConvertToRadians(yaw)) * cos(XMConvertToRadians(pitch))
	};

	XMFLOAT3 transform = XMFLOAT3(-forward.x * distance, -forward.y * distance, -forward.z * distance);
	pCam->GetTransform()->Translate(transform);

	//activate
	pCamComp->SetActive(true);

	//SPRITES
	GameObject* pSpriteObject{};

	pSpriteObject = AddChild(new GameObject());
	pSpriteObject->AddComponent(new SpriteComponent(L"Textures/Background.png", { 0, 1 }));
	pSpriteObject->GetTransform()->Translate(0.f, m_SceneContext.windowHeight, 0.f);
	pSpriteObject->GetTransform()->Scale(1.01f, 1.f, 1.f);


	pSpriteObject = AddChild(new GameObject());
	pSpriteObject->AddComponent(new SpriteComponent(L"Textures/Logo.png", { 0.5f, 0.5f }));
	pSpriteObject->GetTransform()->Translate(m_SceneContext.windowWidth / 2, 150.f, 0.f);
	pSpriteObject->GetTransform()->Rotate(0.f, 0.f, -3.f, true);

	pSpriteObject = AddChild(new GameObject());
	pSpriteObject->AddComponent(new SpriteComponent(L"Textures/Menu.png", { 0, 1 }));
	pSpriteObject->GetTransform()->Translate(0.f, m_SceneContext.windowHeight, 0.f);

	pSpriteObject = AddChild(new GameObject());
	pSpriteObject->AddComponent(new SpriteComponent(L"Textures/Tile1.png", { 0.5f, 0.5f }));
	pSpriteObject->GetTransform()->Translate(300.f, 460.f, 0.f);
	pSpriteObject->GetTransform()->Scale(1.12f);

	pSpriteObject = AddChild(new GameObject());
	pSpriteObject->AddComponent(new SpriteComponent(L"Textures/Tile2.png", { 0.5f, 0.5f }));
	pSpriteObject->GetTransform()->Translate(690.f, 460.f, 0.f);
	pSpriteObject->GetTransform()->Scale(1.12f);


	



	//startbutton
	GameObject* pStartButton{};
	pStartButton = AddChild(new GameObject());
	pStartButton->SetTag(L"Start");

	auto modComp = pStartButton->AddComponent(new ModelComponent(L"Meshes/Person.ovm"));
	m_StartModelAnimator = modComp->GetAnimator();
	m_StartModelAnimator->SetAnimation(L"idle");
	m_StartModelAnimator->Play();
	auto mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	mat->SetDiffuseTexture(L"Textures/Person.png");
	modComp->SetMaterial(mat);


	auto rigi = pStartButton->AddComponent(new RigidBodyComponent(true));
	PxMaterial* physMat = PxGetPhysics().createMaterial(0.f, 0.f, 0.f);
	const auto pMesh = ContentManager::Load<PxConvexMesh>(L"Meshes/Person.ovpc");
	rigi->AddCollider(PxConvexMeshGeometry(pMesh), *physMat, false);

	pStartButton->GetTransform()->Scale(0.04f);
	pStartButton->GetTransform()->Translate(-2.f, -2.f, 0.f);

	//endbutton
	GameObject* pQuitButton{};
	pQuitButton = AddChild(new GameObject());
	pQuitButton->SetTag(L"Quit");

	modComp = pQuitButton->AddComponent(new ModelComponent(L"Meshes/Person.ovm"));
	m_QuitModelAnimator = modComp->GetAnimator();
	m_QuitModelAnimator->SetAnimation(L"idle");
	m_QuitModelAnimator->Play();
	mat = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Skinned>();
	mat->SetDiffuseTexture(L"Textures/Person.png");
	modComp->SetMaterial(mat);




	rigi = pQuitButton->AddComponent(new RigidBodyComponent(true));
	rigi->AddCollider(PxConvexMeshGeometry(pMesh), *physMat, false);

	pQuitButton->GetTransform()->Scale(0.04f);
	pQuitButton->GetTransform()->Translate(2.f, -2.f, 0.f);


	m_pFont = ContentManager::Load<SpriteFont>(L"SpriteFonts/SuperMario_80.fnt");
	
}

void CrossyMenu::Update()
{
	GameObject* picked = m_SceneContext.pCamera->Pick();
	if (picked)
	{
		m_StartedHovered = picked->GetTag() == L"Start";
		m_QuitHovered = picked->GetTag() == L"Quit";
	}
	else
	{
		m_QuitHovered = false;
		m_StartedHovered = false;
	}


	if (m_StartedHovered && m_StartModelAnimator->GetClipName() != L"dance")
	{
		m_StartModelAnimator->SetAnimation(L"dance");
		m_StartModelAnimator->Play();
	}
	else if(!m_StartedHovered && m_StartModelAnimator->GetClipName() != L"idle")
	{
		m_StartModelAnimator->SetAnimation(L"idle");
		m_StartModelAnimator->Play();
	}

	if (m_QuitHovered && m_QuitModelAnimator->GetClipName() != L"dance")
	{
		m_QuitModelAnimator->SetAnimation(L"dance");
		m_QuitModelAnimator->Play();
	}
	else if (!m_QuitHovered && m_QuitModelAnimator->GetClipName() != L"idle")
	{
		m_QuitModelAnimator->SetAnimation(L"idle");
		m_QuitModelAnimator->Play();
	}

	if (m_SceneContext.pInput->IsMouseButton(InputState::down, VK_LBUTTON))
	{
		if (m_StartedHovered)
		{
			//start game
			SceneManager::Get()->NextScene();
		}

		if (m_QuitHovered)
		{
			PostQuitMessage(0);
		}
	}

	TextRenderer::Get()->DrawText(m_pFont, L"start", { 167.f, 520.f }, XMFLOAT4{Colors::Green});
	TextRenderer::Get()->DrawText(m_pFont, L"exit", { 600.f, 520.f }, XMFLOAT4{Colors::Red});
}

void CrossyMenu::PostDraw()
{

}


void CrossyMenu::OnGUI()
{
}
