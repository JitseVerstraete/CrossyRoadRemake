#include "stdafx.h"
#include "CrossyRoadScene.h"
#include "Prefabs/CubePrefab.h"

void CrossyRoadScene::Initialize()
{
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	m_pTerrainSlice = AddChild(new CubePrefab());


}

void CrossyRoadScene::OnGUI()
{
}
