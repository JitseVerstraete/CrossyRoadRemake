#include "stdafx.h"
#include "AudioTestScene.h"

#include "SoundManager.h"

void AudioTestScene::Initialize()
{
	auto pFmodSystem = SoundManager::GetInstance()->GetSystem();
	FMOD_RESULT fmodResult{};

	//2D sound
	FMOD::Sound* pSound2D{};
	fmodResult = pFmodSystem->createStream("Resources/Sounds/wave.mp3", FMOD_DEFAULT, nullptr, &pSound2D);
	SoundManager::GetInstance()->ErrorCheck(fmodResult);

	pSound2D->setMode(FMOD_LOOP_NORMAL);

	fmodResult = pFmodSystem->playSound(pSound2D, nullptr, true, &m_pChannel2D);
	SoundManager::GetInstance()->ErrorCheck(fmodResult);

	//3D sound
	FMOD::Sound* pSound3D{};
	fmodResult = pFmodSystem->createStream("Resources/Sounds/Thrones.mp3", FMOD_3D | FMOD_3D_LINEARROLLOFF, nullptr, &pSound3D);
	SoundManager::GetInstance()->ErrorCheck(fmodResult);

	pSound3D->setMode(FMOD_LOOP_NORMAL);
	pSound3D->set3DMinMaxDistance(0.f, 100.f);

	fmodResult = pFmodSystem->playSound(pSound3D, nullptr, true, &m_pChannel3D);
	SoundManager::GetInstance()->ErrorCheck(fmodResult);


	//sound effect
	fmodResult = pFmodSystem->createStream("Resources/Sounds/bell.mp3", FMOD_DEFAULT, nullptr, &m_pSoundEffect);
	SoundManager::GetInstance()->ErrorCheck(fmodResult);

	fmodResult = pFmodSystem->createChannelGroup("effectChannel", &m_pEffectGroup);

	m_pEffectGroup->setVolume(0.5f);




}

inline FMOD_VECTOR ToFmodVector(XMFLOAT3 v)
{
	return FMOD_VECTOR{ v.x, v.y, v.z };
}


void AudioTestScene::Update()
{

	//GLOBAL LISTENER SETTINGS (3D SOUNDS)
	auto pCamera = m_SceneContext.GetCamera();
	auto forward = ToFmodVector(pCamera->GetForward());
	auto up = ToFmodVector(pCamera->GetUp());
	auto pos = ToFmodVector(pCamera->GetPosition());

	FMOD_VECTOR velocity{};
	auto dt = m_SceneContext.GetGameTime()->GetElapsed();
	velocity.x = ((pos.x - m_PreviousCameraPostition.x) / dt);
	velocity.y = ((pos.y - m_PreviousCameraPostition.y) / dt);
	velocity.z = ((pos.z - m_PreviousCameraPostition.z) / dt);
	m_PreviousCameraPostition = pos;

	SoundManager::GetInstance()->GetSystem()->set3DListenerAttributes(0, &pos, &velocity, &forward, &up);

	//================================================================================

	



	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::pressed, VK_SPACE))
	{
		bool paused{};
		m_pChannel2D->getPaused(&paused);

		m_pChannel2D->setPaused(!paused);
	}

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::pressed, 'B'))
	{
		bool paused{};
		m_pChannel3D->getPaused(&paused);

		m_pChannel3D->setPaused(!paused);
	}

	if (m_SceneContext.GetInput()->IsKeyboardKey(InputTriggerState::pressed, 'V'))
	{
		SoundManager::GetInstance()->GetSystem()->playSound(m_pSoundEffect, m_pEffectGroup, false, nullptr);
	}
}

void AudioTestScene::Draw() const
{
}
