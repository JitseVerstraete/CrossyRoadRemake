#include "stdafx.h"
#include "RiverSlice.h"

#include "Materials/ColorMaterial.h"

RiverSlice::RiverSlice()

{

}

void RiverSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm"));
	ColorMaterial* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	mat->SetColor(XMFLOAT4(Colors::Blue));

	mc->SetMaterial(mat);
}

void RiverSlice::Update(const SceneContext&)
{
	//todo: update the terrain slice 
}
