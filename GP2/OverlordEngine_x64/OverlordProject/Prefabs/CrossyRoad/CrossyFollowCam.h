#pragma once

class CrossyFollowCam : public GameObject
{
public:
	CrossyFollowCam(GameObject* objToFollow, float pitch, float yaw, float distance, int zOffset, float fovDegrees = 30.f);
	~CrossyFollowCam() override = default;

	CrossyFollowCam(const CrossyFollowCam& other) = delete;
	CrossyFollowCam(CrossyFollowCam&& other) noexcept = delete;
	CrossyFollowCam& operator=(const CrossyFollowCam& other) = delete;
	CrossyFollowCam& operator=(CrossyFollowCam&& other) noexcept = delete;

	void Reset() { GetTransform()->Translate(m_OriginalTransform); };

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

	GameObject* m_FollowObject{ nullptr };
	XMFLOAT3 m_OriginalTransform;
	CameraComponent* m_pCamComp = nullptr;

	float m_Pitch{};
	float m_Yaw{};
	float m_Distance{};
	float m_FovDegrees{};
	int m_zOffset{};

};

