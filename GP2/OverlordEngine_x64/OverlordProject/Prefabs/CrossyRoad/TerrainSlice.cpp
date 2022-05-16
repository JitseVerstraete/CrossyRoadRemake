#include "stdafx.h"
#include "TerrainSlice.h"

#include "Materials/ColorMaterial.h"

TerrainSlice::TerrainSlice(TerrainType type)
	: m_Type{ type }
{

}

void TerrainSlice::Initialize(const SceneContext&)
{
	
	ModelComponent* mc = AddComponent(new ModelComponent(L"Meshes/Slice.ovm"));
	ColorMaterial* mat = MaterialManager::Get()->CreateMaterial<ColorMaterial>();

	switch (m_Type)
	{
	case TerrainType::Grass:
		mat->SetColor(XMFLOAT4(Colors::Green));
		break;
	case TerrainType::Road:
		mat->SetColor(XMFLOAT4(Colors::Gray));
		break;
	case TerrainType::River:
		mat->SetColor(XMFLOAT4(Colors::Blue));
		break;
	default:
		break;
	}
	mc->SetMaterial(mat);
}

void TerrainSlice::Update(const SceneContext& )
{
	//todo: update the terrain slice (spawn cars, spawn logs on river...)
}
