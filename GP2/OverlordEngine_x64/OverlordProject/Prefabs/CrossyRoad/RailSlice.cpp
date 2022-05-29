#include "stdafx.h"
#include "RailSlice.h" 

#include "Materials/CrossyRoad/TerrainSliceMaterial.h"
#include "Materials/Shadow/DiffuseMaterial_Shadow.h"
#include "CrossyCar.h"

#include "Prefabs/CrossyRoad/CrossyTrain.h"
#include "Prefabs/CrossyRoad/CrossyCharacter.h"

RailSlice::RailSlice(int width, float speed, float minSpawnTime, float maxSpawnTime, CrossyCharacter* trackedCharacter)
	: m_Width{ width }
	, m_TrainSpeed{ speed }
	, m_SpawnTimer{ 0.f }
	, m_pTrackedCharacter{ trackedCharacter }
{
	m_SpawnTime = MathHelper::randF(minSpawnTime, maxSpawnTime);
	m_TrainDir = rand() % 2 ? (int)TrainDir::Left : (int)TrainDir::Right;
	m_RestX = -m_TrainDir * m_Width * 3.f;


}

void RailSlice::Initialize(const SceneContext&)
{
	//ground
	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	TerrainSliceMaterial* mat = MaterialManager::Get()->CreateMaterial<TerrainSliceMaterial>();

	float greyVal{ 0.4f };
	mat->SetColor(XMFLOAT4{ greyVal , greyVal, greyVal, 1.f });
	mat->SetWidth(m_Width + 0.5f);
	mc->SetMaterial(mat);

	//tracks
	mc = AddComponent(new ModelComponent(L"Meshes/Railway.ovm", false));
	DiffuseMaterial_Shadow* mat2 = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();

	mat2->SetDiffuseTexture(L"Textures/Railway.png");
	mc->SetMaterial(mat2);

	//sign
	mc = AddComponent(new ModelComponent(L"Meshes/TrainSign.ovm"));
	m_SignMaterial = MaterialManager::Get()->CreateMaterial<DiffuseMaterial_Shadow>();

	m_SignMaterial->SetDiffuseTexture(L"Textures/TrainSign.png");
	mc->SetMaterial(m_SignMaterial);


	XMFLOAT3 pos = GetTransform()->GetPosition();
	GetTransform()->Translate(pos.x, -0.08f, pos.z);



	for (int i{}; i < m_NrCarriages; ++i)
	{
		m_pTrains.emplace_back(AddChild(new CrossyTrain(m_TrainSpeed, m_TrainDir, m_RestX - (m_TrainDir * m_CarriageLength * i))));
	}

	//sound
	auto pSound = SoundManager::Get()->GetSystem();
	pSound->createStream("Resources/Sounds/TrainWarning.wav", FMOD_DEFAULT, nullptr, &m_pWarningSound);
	pSound->createStream("Resources/Sounds/TrainToot.wav", FMOD_DEFAULT, nullptr, &m_pTrainSound);




}

void RailSlice::Update(const SceneContext& sceneContext)
{

	//only activate the timer when the character is close enough
	if (abs(m_pTrackedCharacter->GetScore() - GetTransform()->GetPosition().z) < 5)
	{
		m_SpawnTimer += sceneContext.pGameTime->GetElapsed();
	}

	if (!m_WarningSet && m_SpawnTimer >= m_SpawnTime - 1.f )
	{
		m_SignMaterial->SetDiffuseTexture(L"Textures/TrainSignLit.png");
		m_WarningSet = true;
		SoundManager::Get()->GetSystem()->playSound(m_pWarningSound, nullptr, false, &m_pWarningChannel);
		m_pWarningChannel->setVolume(.4f);
	}


	if (m_WarningSet && m_LightTimer > 0.f)
	{
		int number = (int)(m_LightTimer * 4.f);
		m_LightTimer -= sceneContext.pGameTime->GetElapsed();

		if (m_LightOn && number % 2 == 0)
		{
			m_SignMaterial->SetDiffuseTexture(L"Textures/TrainSign.png");
			m_LightOn = false;
		}
		if (!m_LightOn && number % 2 == 1)
		{
			m_SignMaterial->SetDiffuseTexture(L"Textures/TrainSignLit.png");
			m_LightOn = true;
		}

		if (!m_TootPlayed && m_LightTimer < 1.f)
		{
			SoundManager::Get()->GetSystem()->playSound(m_pTrainSound, nullptr, false, &m_pTootChannel);
			m_pTootChannel->setVolume(.4f);
			m_TootPlayed = true;
		}


	}

	


	if (m_SpawnTimer >= m_SpawnTime)
	{
		for (CrossyTrain* pTrain : m_pTrains)
		{
			pTrain->SetDriving(true);
		}

		m_SpawnTimer = -1000000.f;
	}

}
