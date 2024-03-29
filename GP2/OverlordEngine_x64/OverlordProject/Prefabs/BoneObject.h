#pragma once

class BoneObject : public GameObject
{
public:
	BoneObject(BaseMaterial* pMaterial, float length = 5.f);
	~BoneObject() override = default;

	BoneObject(const BoneObject& other) = delete;
	BoneObject(BoneObject&& other) noexcept = delete;
	BoneObject& operator=(const BoneObject& other) = delete;
	BoneObject& operator=(BoneObject&& other) noexcept = delete;

	void AddBone(BoneObject* pBone);

	const XMFLOAT4X4& GetBindPose() const { return m_BindPose; }
	void CalculateBindPose();

protected:
	void Initialize(const SceneContext&) override;

private:

	BaseMaterial* m_pMaterial{};
	float m_Length{};

	XMFLOAT4X4 m_BindPose;

};

