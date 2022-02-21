#pragma once
#include "GameScene.h"

class AudioTestScene : public GameScene
{
public:

	AudioTestScene() :GameScene(L"BouncingBallsScene") {}
	~AudioTestScene() override = default;
	AudioTestScene(const AudioTestScene& other) = delete;
	AudioTestScene(AudioTestScene&& other) noexcept = delete;
	AudioTestScene& operator=(const AudioTestScene& other) = delete;
	AudioTestScene& operator=(AudioTestScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() const override;

private:
	FMOD::Channel* m_pChannel2D{};
	FMOD::Channel* m_pChannel3D{};

	FMOD_VECTOR m_PreviousCameraPostition{};

	FMOD::Sound* m_pSoundEffect{};
	FMOD::ChannelGroup* m_pEffectGroup{};
};

