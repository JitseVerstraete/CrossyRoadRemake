#include "stdafx.h"
#include "GrassSlice.h"

#include "Materials/ColorMaterial.h"

GrassSlice::GrassSlice(int obstacles)
{

}

void GrassSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm"));
	ColorMaterial* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	mat->SetColor(XMFLOAT4(Colors::Green));

	mc->SetMaterial(mat);
}

void GrassSlice::Update(const SceneContext&)
{
	//todo: update the terrain slice (spawn cars, spawn logs on river...)
}
