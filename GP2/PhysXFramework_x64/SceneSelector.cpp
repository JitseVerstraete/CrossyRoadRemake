#include "stdafx.h"
#include "SceneSelector.h"
#include "SceneManager.h"

//Change this define to activate/deactive the corresponding scenes
// W01 - W02  (#define ...)

#define W01
//#define W02

#ifdef W01
#include "TestScene.h"
#include "BouncingBallsScene.h"
#include "FrictionTestScene.h"
#include "ForceTestScene.h"
#include "TorqueTestScene.h"
#endif

#ifdef W02

#endif

namespace dae
{
	void AddScenes(SceneManager * pSceneManager)
	{

#ifdef W01
		pSceneManager->AddGameScene(new TestScene());
		pSceneManager->AddGameScene(new BouncingBallsScene());
		pSceneManager->AddGameScene(new FrictionTestScene());
		pSceneManager->AddGameScene(new ForceTestScene());
		pSceneManager->AddGameScene(new TorqueTestScene());
#endif

#ifdef W02

#endif

	}
}

