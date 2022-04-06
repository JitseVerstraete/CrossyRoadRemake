#include "stdafx.h"
#include "SpikyMaterial.h"

SpikyMaterial::SpikyMaterial() : Material<SpikyMaterial>(L"Effects/SpikyShader.fx")
{
}

void SpikyMaterial::SetDiffuseColor(const XMFLOAT4& color)
{
	SetVariable_Vector(L"gColorDiffuse", color);
}

void SpikyMaterial::SetSpikeLength(float length)
{
	SetVariable_Scalar(L"gSpikeLength", length);
}

void SpikyMaterial::InitializeEffectVariables()
{
	SetDiffuseColor(XMFLOAT4(1.f, 0.5f, 0.5f, 1.f));
	SetSpikeLength(1.f);
}
