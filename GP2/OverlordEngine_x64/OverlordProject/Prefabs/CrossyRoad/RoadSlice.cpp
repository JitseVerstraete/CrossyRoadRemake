#include "stdafx.h"
#include "RoadSlice.h" 

#include "Materials/CrossyRoad/TerrainSliceMaterial.h"
#include "CrossyCar.h"
#include "Terrain.h"

int RoadSlice::m_LeftWeight = 1;
int RoadSlice::m_RightWeight = 1;

RoadSlice::RoadSlice(int width, float minSpeed, float maxSpeed, float minDist, float maxDist)
	: m_Width{ width }
	, m_CarSpeed{}
	, m_SpawnInterval{}
	, m_SpawnTimer{ 0.f }
{
	//calculate car speed & interval variations
	m_CarSpeed = MathHelper::randF(minSpeed, maxSpeed);
	m_SpawnInterval = MathHelper::randF(minDist, maxDist) / m_CarSpeed;
	m_SpawnTimer = m_SpawnInterval;


	//calculate car direction
	if (rand() % (m_LeftWeight + m_RightWeight) < m_LeftWeight)
	{
		//direction is left (increace the chance for right direction for the next slice & reset the chance for the left direction)
		m_CarDir = static_cast<int>(CarDir::Left);
		m_RightWeight++;
		m_LeftWeight = 1;
	}
	else
	{
		//direction is right
		m_CarDir = static_cast<int>(CarDir::Right);
		m_LeftWeight++;
		m_RightWeight = 1;
	}

}

void RoadSlice::Initialize(const SceneContext& sceneContext)
{
	//initialzie stripes shader
	m_pStripesEffect = ContentManager::Load<ID3DX11Effect>(L"Effects/CrossyRoad/RoadStripes.fx");
	m_pStripesTechnique = m_pStripesEffect->GetTechniqueByIndex(0);
	EffectHelper::BuildInputLayout(sceneContext.d3dContext.pDevice, m_pStripesTechnique, &m_pStripesInputLayout);

	VertexStripe stripe{};
	stripe.WidthLength.x = m_StripeWidth;
	stripe.WidthLength.y = m_StripeLength;
	for (float i{ -2.f * m_Width }; i < m_Width * 2.f; i += m_StripesInterval)
	{
		stripe.color = MathHelper::HSLtoRGB(50.f / 360, 0.6f, 0.4f, 1.f);
		stripe.Position = XMFLOAT3{ i, 0.f, -0.5f };
		m_Stripes.emplace_back(stripe);
	}


	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm", false));
	TerrainSliceMaterial* mat = MaterialManager::Get()->CreateMaterial<TerrainSliceMaterial>();

	float greyVal{ 0.4f };
	mat->SetColor(XMFLOAT4{ greyVal , greyVal, greyVal, 1.f });
	mat->SetWidth(m_Width + 0.5f);
	mc->SetMaterial(mat);

	XMFLOAT3 pos = GetTransform()->GetPosition();
	GetTransform()->Translate(pos.x, -0.08f, pos.z);
}

void RoadSlice::Update(const SceneContext& sceneContext)
{
	m_SpawnTimer += sceneContext.pGameTime->GetElapsed();


	//spawn car if the interval has passed
	if (m_SpawnTimer >= m_SpawnInterval)
	{
		m_SpawnTimer = 0.f;
		CrossyCar* pCar = new CrossyCar(m_CarSpeed, m_CarDir);
		m_pCars.emplace_back(pCar);
		float startX = m_Width * -2.f * m_CarDir;
		pCar->GetTransform()->Translate(startX, 0.f, 0.f);
		AddChild(pCar);
	}


	//despawn the cars that crossed the playfield
	auto it = m_pCars.begin();
	while (it != m_pCars.end())
	{
		if (((*it)->GetTransform()->GetPosition().x * m_CarDir) > (m_Width * 2.f))
		{
			//delte Car
			RemoveChild((*it), true);
			m_pCars.erase(std::remove(m_pCars.begin(), m_pCars.end(), *it));
			continue;
		}

		++it;
	}
}

void RoadSlice::Draw(const SceneContext& sceneContext)
{
	Terrain* pTerrain = dynamic_cast<Terrain*>(GetParent());
	RoadSlice* pPrevRoad{};
	if (pTerrain)
	{
		pPrevRoad = dynamic_cast<RoadSlice*>(pTerrain->GetSlice((int)GetTransform()->GetPosition().z - 1));
	}

	if (pPrevRoad)
	{
		//todo: only build the vertex buffer if it hasn't been done before!
		if (true)
		{
			UINT nrStripes{ (UINT)m_Stripes.size() };

			//build buffer
			SafeRelease(m_pStripesVertexBuffer);
			D3D11_BUFFER_DESC bufferDesc{};
			bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			bufferDesc.ByteWidth = sizeof(VertexStripe) * nrStripes;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags = 0;
			bufferDesc.StructureByteStride = 0;

			HRESULT result = sceneContext.d3dContext.pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pStripesVertexBuffer);
			HANDLE_ERROR(result);

			//fill buffer
			if (m_pStripesVertexBuffer)
			{
				// Finally fill the  buffer. You will need to create a D3D11_MAPPED_SUBRESOURCE
				// Next you will need to use the device context to map the vertex buffer to the mapped resource
				// use memcpy to copy all our sprite vertices (m_Sprites) to the mapped resource (D3D11_MAPPED_SUBRESOURCE::pData)
				// unmap the vertex buffer

				D3D11_MAPPED_SUBRESOURCE mappedResource{};
				sceneContext.d3dContext.pDeviceContext->Map(m_pStripesVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
				memcpy(mappedResource.pData, m_Stripes.data(), sizeof(VertexStripe) * nrStripes);
				sceneContext.d3dContext.pDeviceContext->Unmap(m_pStripesVertexBuffer, 0);
			}

		}

		//update variables
		XMMATRIX lightWVPmatrix = (XMLoadFloat4x4(&GetTransform()->GetWorld()) * XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
		XMFLOAT4X4 lightWVP{};
		XMStoreFloat4x4(&lightWVP, lightWVPmatrix);
		m_pStripesEffect->GetVariableByName("gWorldViewProj_Light")->AsMatrix()->SetMatrix((float*)&lightWVP);

		XMMATRIX wvpMatrix = (XMLoadFloat4x4(&GetTransform()->GetWorld()) * XMLoadFloat4x4(&sceneContext.pCamera->GetViewProjection()));
		XMFLOAT4X4 wvp{};
		XMStoreFloat4x4(&wvp, wvpMatrix);
		m_pStripesEffect->GetVariableByName("gWorldViewProj")->AsMatrix()->SetMatrix(&wvp._11);


		m_pStripesEffect->GetVariableByName("gShadowMap")->AsShaderResource()->SetResource(ShadowMapRenderer::Get()->GetShadowMap());


		//render pipeline
		const auto pDeviceContext = sceneContext.d3dContext.pDeviceContext;
		pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

		constexpr UINT stride = sizeof(VertexStripe);
		constexpr UINT offset = 0;
		pDeviceContext->IASetVertexBuffers(0, 1, &m_pStripesVertexBuffer, &stride, &offset);
		pDeviceContext->IASetInputLayout(m_pStripesInputLayout);

		D3DX11_TECHNIQUE_DESC techDesc{};
		m_pStripesTechnique->GetDesc(&techDesc);
		for (unsigned int i{}; i < techDesc.Passes; ++i)
		{
			m_pStripesTechnique->GetPassByIndex(i)->Apply(0, pDeviceContext);
			pDeviceContext->Draw((UINT)m_Stripes.size(), 0);
		}





	}
}
