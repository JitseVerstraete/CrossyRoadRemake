#include "stdafx.h"
#include "GrassSlice.h"

#include "Materials/ColorMaterial.h"
#include "Prefabs/CubePrefab.h"

GrassSlice::GrassSlice(int obstacles, int maxWidth)
	:m_NrObstacles{ obstacles }, m_MaxWidth{ maxWidth }
{
}



bool GrassSlice::IsPassable(int x)
{
	if (m_Obstacles.find(x) == m_Obstacles.end()) return true;
	else return false;
}

void GrassSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm"));
	ColorMaterial* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	mat->SetColor(XMFLOAT4(Colors::Green));

	mc->SetMaterial(mat);



	//add obstacles to the left & right edges of the slice
	GameObject* pObstacle = AddChild(new CubePrefab());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 1), 0.f, 0.f });
	pObstacle = AddChild(new CubePrefab());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 2), 0.f, 0.f });
	pObstacle = AddChild(new CubePrefab());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(-m_MaxWidth - 3), 0.f, 0.f });
	pObstacle = AddChild(new CubePrefab());
	pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(m_MaxWidth + 1), 0.f, 0.f });



	std::vector<int> usedNumbers{};

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
					pObstacle = AddChild(new CubePrefab());
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
			pObstacle = AddChild(new CubePrefab());
			m_Obstacles.insert({ i, pObstacle });
			pObstacle->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(i), 0.f, 0.f });
		}
	}
}

void GrassSlice::Update(const SceneContext&)
{
	//todo: update the terrain slice (spawn cars, spawn logs on river...)
}
