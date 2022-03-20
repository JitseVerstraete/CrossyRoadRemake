#include "stdafx.h"
#include "SceneSelector.h"
#include "SceneManager.h"

//Change this define to activate/deactive the corresponding scenes
// W01 - W02  (#define ...)

//#define W01
#define MILESTONE

#ifdef W01
#include "TestScene.h"
#include "BouncingBallsScene.h"
#include "FrictionTestScene.h"
#include "ForceTestScene.h"
#include "TorqueTestScene.h"
#include "CubeWallScene.h"
#endif

#ifdef W02
#include "PhysXMeshTestScene.h"
#include "AudioTestScene.h"
#include "W02_AssignmentScene.h"
#endif

#ifdef MILESTONE
#include "CubeWallScene.h"
#include "W02_AssignmentScene.h"
#endif


namespace dae
{
	void AddScenes(SceneManager* pSceneManager)
	{

#ifdef W01
		pSceneManager->AddGameScene(new TestScene());
		pSceneManager->AddGameScene(new BouncingBallsScene());
		pSceneManager->AddGameScene(new FrictionTestScene());
		pSceneManager->AddGameScene(new ForceTestScene());
		pSceneManager->AddGameScene(new TorqueTestScene());
		pSceneManager->AddGameScene(new CubeWallScene());
#endif

#ifdef W02
		pSceneManager->AddGameScene(new W02_AssignmentScene());
		pSceneManager->AddGameScene(new AudioTestScene());
		pSceneManager->AddGameScene(new PhysXMeshTestScene());
#endif

#ifdef MILESTONE
		pSceneManager->AddGameScene(new CubeWallScene());
		pSceneManager->AddGameScene(new W02_AssignmentScene());
#endif


	}
}

