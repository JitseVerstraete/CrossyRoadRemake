#include "stdafx.h"
#include "GrassSlice.h"

#include "Terrain.h"

#include "Materials/CrossyRoad/TerrainSliceMaterial.h"
#include "Prefabs/CrossyRoad/Tree.h"
#include "Prefabs/CrossyRoad/RiverSlice.h"

int GrassSlice::m_GrassCounter = 0;

GrassSlice::GrassSlice(int obstacles, int maxWidth)
	:m_NrObstacles{ obstacles }, m_MaxWidth{ maxWidth }
{
	++m_GrassCounter;
}



bool GrassSlice::IsPassable(int x)
{
	if (m_Obstacles.find(x) == m_Obstacles.end()) return true;
	else return false;
}

void GrassSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	TerrainSliceMaterial* mat = MaterialManager::Get()->CreateMaterial<TerrainSliceMaterial>();
	mat->SetColor(m_GrassCounter % 2 == 0 ? m_LightGrassColor : m_DarkGrassColor);
	mat->SetWidth(m_MaxWidth + 0.5f);
	mc->SetMaterial(mat);



	//add obstacles to the left & right edges of the slice
	GameObject* pObstacle = AddChild(new Tree());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 1), 0.f, 0.f });
	pObstacle = AddChild(new Tree());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 2), 0.f, 0.f });
	pObstacle = AddChild(new Tree());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 3), 0.f, 0.f });
	pObstacle = AddChild(new Tree());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(m_MaxWidth + 1), 0.f, 0.f });
	pObstacle = AddChild(new Tree());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(m_MaxWidth + 2), 0.f, 0.f });



	std::vector<int> usedNumbers{};
	Terrain* pTerrain = dynamic_cast<Terrain*>(GetParent());

	//if previous slice is a river slice, don't spawn trees behind lilypads (so you never block the way)
	RiverSlice* pRiver = dynamic_cast<RiverSlice*>(pTerrain->GetPreviousSlice());
	if (pRiver)
	{
		for (int i{ -m_MaxWidth }; i <= m_MaxWidth; ++i)
		{
			if (pRiver->HasLily(i))
			{
				usedNumbers.emplace_back(i);
			}
		}
	}

	GrassSlice* pGrass = dynamic_cast<GrassSlice*>(pTerrain->GetPreviousSlice());
	if (pGrass)
	{
		if (!pGrass->IsPassable(-m_MaxWidth) && std::find(usedNumbers.begin(), usedNumbers.end(), -m_MaxWidth + 1) == usedNumbers.end())
		{
			usedNumbers.emplace_back(-m_MaxWidth + 1);
		}

		if (!pGrass->IsPassable(-m_MaxWidth + 1) && std::find(usedNumbers.begin(), usedNumbers.end(), -m_MaxWidth) == usedNumbers.end())
		{
			usedNumbers.emplace_back(-m_MaxWidth);
		}

		if (!pGrass->IsPassable(-m_MaxWidth + 1) && std::find(usedNumbers.begin(), usedNumbers.end(), -m_MaxWidth + 2) == usedNumbers.end())
		{
			usedNumbers.emplace_back(-m_MaxWidth + 2);
		}

		if (!pGrass->IsPassable(m_MaxWidth) && std::find(usedNumbers.begin(), usedNumbers.end(), m_MaxWidth - 1) == usedNumbers.end())
		{
			usedNumbers.emplace_back(m_MaxWidth - 1);
		}

		if (!pGrass->IsPassable(m_MaxWidth - 1) && std::find(usedNumbers.begin(), usedNumbers.end(), m_MaxWidth) == usedNumbers.end())
		{
			usedNumbers.emplace_back(m_MaxWidth);
		}

		if (!pGrass->IsPassable(m_MaxWidth - 1) && std::find(usedNumbers.begin(), usedNumbers.end(), m_MaxWidth - 2) == usedNumbers.end())
		{
			usedNumbers.emplace_back(m_MaxWidth - 2);
		}
	}

	if (m_NrObstacles < m_MaxWidth * 2 + 1)
	{

		//spawn obstacles at random locations
		for (int i{}; i < m_NrObstacles; ++i)
		{
			int randomNumber{};
			while (true)
			{
				randomNumber = (rand() % (m_MaxWidth * 2 + 1)) - m_MaxWidth;
				if (std::find(usedNumbers.begin(), usedNumbers.end(), randomNumber) == usedNumbers.end())
				{
					//spawn tree at this x pos
					pObstacle = AddChild(new Tree());
					m_Obstacles.insert({ randomNumber, pObstacle });
					pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(randomNumber), 0.f, 0.f });

					//ad number to used numbers :)
					usedNumbers.emplace_back(randomNumber);
					break;
				}


			}
		}


	}
	else
	{
		//spawn obstacles at all locations
		for (int i{ -m_MaxWidth }; i < m_MaxWidth + 1; ++i)
		{
			//spawn tree at this x pos
			pObstacle = AddChild(new Tree());
			m_Obstacles.insert({ i, pObstacle });
			pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(i), 0.f, 0.f });
		}
	}
}

void GrassSlice::Update(const SceneContext&)
{

}
