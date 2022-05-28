#include "stdafx.h"
#include "RiverSlice.h"

#include "Terrain.h"

#include "Materials/CrossyRoad/ColorMaterial_Shadow.h"
#include "Prefabs/CrossyRoad/Lily.h"

RiverSlice::RiverSlice(int nrLilys, int width)
	: m_NrLilys{ nrLilys }
	, m_MaxWidth{ width }
{

}

bool RiverSlice::HasLily(int x)
{
	if (m_pLilyPads.find(x) != m_pLilyPads.end()) return true;
	else return false;
}

void RiverSlice::Initialize(const SceneContext&)
{
	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	ColorMaterial_Shadow* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial_Shadow>();

	mat->SetColor(XMFLOAT4(MathHelper::HSLtoRGB(0.55f, 0.7f, 0.5f, 1.f)));

	mc->SetMaterial(mat);

	XMFLOAT3 pos = GetTransform()->GetPosition();
	GetTransform()->Translate(pos.x, -0.16f, pos.z);




	std::vector<int> usedNumbers{};
	Terrain* pTerrain = dynamic_cast<Terrain*>(GetParent());

	//if previous slice is a grass, don't spawn lilypads behind trees (so it never blocks the path)
	GrassSlice* pGrass = dynamic_cast<GrassSlice*>(pTerrain->GetPreviousSlice());
	if (pGrass)
	{
		for (int i{ -m_MaxWidth }; i <= m_MaxWidth; ++i)
		{
			if (!pGrass->IsPassable(i))
			{
				usedNumbers.emplace_back(i);
			}
		}
	}



	GameObject* pLily{ nullptr };
	if (m_NrLilys < (m_MaxWidth * 2) + 1 - (int)usedNumbers.size())
	{
		//spawn obstacles at random locations
		for (int i{}; i < m_NrLilys; ++i)
		{
			int randomNumber{};
			while (true)
			{
				randomNumber = (rand() % (m_MaxWidth * 2 + 1)) - m_MaxWidth;
				if (std::find(usedNumbers.begin(), usedNumbers.end(), randomNumber) == usedNumbers.end())
				{
					//spawn tree at this x pos
					pLily = AddChild(new Lily());
					m_pLilyPads.insert({ randomNumber, pLily });
					pLily->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(randomNumber), 0.f, 0.f });


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
			pLily = AddChild(new Lily());
			m_pLilyPads.insert({ i, pLily });
			pLily->GetTransform()->Translate(XMFLOAT3{ static_cast<float>(i), 0.f, 0.f });
		}

	}

}

void RiverSlice::Update(const SceneContext&)
{

}
