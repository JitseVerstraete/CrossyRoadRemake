#include "stdafx.h"
#include "TerrainSliceMaterial.h"

TerrainSliceMaterial::TerrainSliceMaterial() : Material<TerrainSliceMaterial>(L"Effects/CrossyRoad/TerrainSlice.fx")
{
}


void TerrainSliceMaterial::SetColor(const XMFLOAT4& color) const
{
	SetVariable_Vector(L"gColor", color);
}

void TerrainSliceMaterial::SetWidth(float width) const
{
	SetVariable_Scalar(L"gWidth", width);

}

void TerrainSliceMaterial::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const
{

	XMMATRIX lightWVPmatrix = (XMLoadFloat4x4(&pModel->GetGameObject()->GetTransform()->GetWorld()) * XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
	XMFLOAT4X4 lightWVP{};
	XMStoreFloat4x4(&lightWVP, lightWVPmatrix);
	SetVariable_Matrix(L"gWorldViewProj_Light", (float*)&lightWVP);

	SetVariable_Texture(L"gShadowMap", ShadowMapRenderer::Get()->GetShadowMap());

	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);

}
