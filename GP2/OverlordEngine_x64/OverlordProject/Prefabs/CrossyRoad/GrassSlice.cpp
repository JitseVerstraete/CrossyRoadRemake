#include "stdafx.h"
#include "GrassSlice.h"

#include "Terrain.h"

#include "Materials/CrossyRoad/TerrainSliceMaterial.h"
#include "Prefabs/CrossyRoad/Tree.h"
#include "Prefabs/CrossyRoad/RiverSlice.h"

int GrassSlice::m_GrassSliceCounter = 0;

GrassSlice::GrassSlice(int obstacles, int maxWidth, unsigned int grassAmount)
	:m_NrObstacles{ obstacles }, m_MaxWidth{ maxWidth }, m_NrGrassBlades{ grassAmount }
{
	++m_GrassSliceCounter;
}



bool GrassSlice::IsPassable(int x)
{
	if (m_Obstacles.find(x) == m_Obstacles.end()) return true;
	else return false;
}

void GrassSlice::Initialize(const SceneContext& sceneContext)
{
	//grass effect setup
	m_pGrassEffect = ContentManager::Load<ID3DX11Effect>(L"Effects/CrossyRoad/Grass.fx");
	m_pGrassTechnique = m_pGrassEffect->GetTechniqueByIndex(0);
	EffectHelper::BuildInputLayout(sceneContext.d3dContext.pDevice, m_pGrassTechnique, &m_pGrassInputLayout);

	//fill the grass vector with random points
	VertexGrass vertex{};
	for (unsigned int i{}; i < m_NrGrassBlades; ++i)
	{
		vertex.Position = XMFLOAT3{ MathHelper::randF(-m_MaxWidth - 0.4f, m_MaxWidth + .4f), 0.f, MathHelper::randF(-0.48f, 0.48f) };
		vertex.color = MathHelper::HSLtoRGB(110.f/360, MathHelper::randF(0.5f, 0.6f), MathHelper::randF(0.45f, 0.55f), 1.f);
		m_GrassPoints.emplace_back(vertex);
	}



	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	TerrainSliceMaterial* mat = MaterialManager::Get()->CreateMaterial<TerrainSliceMaterial>();
	mat->SetColor(m_GrassSliceCounter % 2 == 0 ? m_LightGrassColor : m_DarkGrassColor);
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

void GrassSlice::Draw(const SceneContext& sceneContext)
{
	if (m_NrGrassBlades != 0)
	{



		//todo: only build the vertex buffer if it hasn't been done before!
		if (true)
		{
			//build buffer
			SafeRelease(m_pGrassVertexBuffer);
			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.ByteWidth = sizeof(VertexGrass) * m_NrGrassBlades;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags = 0;
			bufferDesc.StructureByteStride = 0;

			HRESULT result = sceneContext.d3dContext.pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pGrassVertexBuffer);
			HANDLE_ERROR(result);

			//fill buffer
			if (m_pGrassVertexBuffer)
			{
				// Finally fill the  buffer. You will need to create a D3D11_MAPPED_SUBRESOURCE
				// Next you will need to use the device context to map the vertex buffer to the mapped resource
				// use memcpy to copy all our sprite vertices (m_Sprites) to the mapped resource (D3D11_MAPPED_SUBRESOURCE::pData)
				// unmap the vertex buffer

				D3D11_MAPPED_SUBRESOURCE mappedResource{};
				sceneContext.d3dContext.pDeviceContext->Map(m_pGrassVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				memcpy(mappedResource.pData, m_GrassPoints.data(), sizeof(VertexGrass) * m_NrGrassBlades);
				sceneContext.d3dContext.pDeviceContext->Unmap(m_pGrassVertexBuffer, 0);
			}

		}

		//update variables
		XMMATRIX lightWVPmatrix = (XMLoadFloat4x4(&GetTransform()->GetWorld()) * XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
		XMFLOAT4X4 lightWVP{};
		XMStoreFloat4x4(&lightWVP, lightWVPmatrix);
		m_pGrassEffect->GetVariableByName("gWorldViewProj_Light")->AsMatrix()->SetMatrix((float*)&lightWVP);

		XMMATRIX wvpMatrix = (XMLoadFloat4x4(&GetTransform()->GetWorld()) * XMLoadFloat4x4(&sceneContext.pCamera->GetViewProjection()));
		XMFLOAT4X4 wvp{};
		XMStoreFloat4x4(&wvp, wvpMatrix);
		m_pGrassEffect->GetVariableByName("gWorldViewProj")->AsMatrix()->SetMatrix(&wvp._11);


		m_pGrassEffect->GetVariableByName("gShadowMap")->AsShaderResource()->SetResource(ShadowMapRenderer::Get()->GetShadowMap());


		//render pipeline
		const auto pDeviceContext = sceneContext.d3dContext.pDeviceContext;
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		constexpr UINT stride = sizeof(VertexGrass);
		constexpr UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &m_pGrassVertexBuffer, &stride, &offset);
		pDeviceContext->IASetInputLayout(m_pGrassInputLayout);

		D3DX11_TECHNIQUE_DESC techDesc{};
		m_pGrassTechnique->GetDesc(&techDesc);
		for (unsigned int i{}; i < techDesc.Passes; ++i)
		{
			m_pGrassTechnique->GetPassByIndex(i)->Apply(0, pDeviceContext);
			pDeviceContext->Draw(m_NrGrassBlades, 0);
		}

	}

}
