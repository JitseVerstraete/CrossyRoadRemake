#include "stdafx.h"
#include "CrossyRoadScene.h"


#include "Materials/ColorMaterial.h"
#include "Materials/DiffuseMaterial.h"

#include "Prefabs/CrossyRoad/Terrain.h"
#include "Prefabs/CrossyRoad/CrossyCharacter.h"


void CrossyRoadScene::Initialize()
{
	const auto pDefaultMaterial = PxGetPhysics().createMaterial(0.5f, 0.5f, 0.5f);
	GameSceneExt::CreatePhysXGroundPlane(*this, pDefaultMaterial);

	AddChild(new Terrain(50));
	AddChild(new CrossyCharacter());
	
	
}

void CrossyRoadScene::OnGUI()
{
}
