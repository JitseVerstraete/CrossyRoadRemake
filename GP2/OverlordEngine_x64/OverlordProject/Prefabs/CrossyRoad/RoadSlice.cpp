#include "stdafx.h"
#include "RoadSlice.h" 

#include "Materials/ColorMaterial.h"

RoadSlice::RoadSlice()
{

}

void RoadSlice::Initialize(const SceneContext&)
{

	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm"));
	ColorMaterial* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();


	mat->SetColor(XMFLOAT4(Colors::Gray));

	mc->SetMaterial(mat);
}

void RoadSlice::Update(const SceneContext&)
{
	//todo: update the terrain slice
}
