#include "stdafx.h"
#include "ColorMaterial_Shadow.h"

ColorMaterial_Shadow::ColorMaterial_Shadow() : Material<ColorMaterial_Shadow>(L"Effects/CrossyRoad/PosNorm3D_Shadow.fx")
{
}


void ColorMaterial_Shadow::SetColor(const XMFLOAT4& color) const
{
	SetVariable_Vector(L"gColor", color);
}

void ColorMaterial_Shadow::OnUpdateModelVariables(const SceneContext& sceneContext, const ModelComponent* pModel) const
{

	XMMATRIX lightWVPmatrix = (XMLoadFloat4x4(&pModel->GetGameObject()->GetTransform()->GetWorld()) * XMLoadFloat4x4(&ShadowMapRenderer::Get()->GetLightVP()));
	XMFLOAT4X4 lightWVP{};
	XMStoreFloat4x4(&lightWVP, lightWVPmatrix);
	SetVariable_Matrix(L"gWorldViewProj_Light", (float*)&lightWVP);

	SetVariable_Texture(L"gShadowMap", ShadowMapRenderer::Get()->GetShadowMap());

	SetVariable_Vector(L"gLightDirection", sceneContext.pLights->GetDirectionalLight().direction);

}
