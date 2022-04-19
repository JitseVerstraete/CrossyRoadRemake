#pragma once


class BoneObject;
class SoftwareSkinningScene_2 : public GameScene
{
public:
	SoftwareSkinningScene_2() :GameScene(L"SoftwareSkinningScene 2"), m_pBone0{ nullptr }, m_pBone1{ nullptr } {}
	~SoftwareSkinningScene_2() override = default;

	SoftwareSkinningScene_2(const SoftwareSkinningScene_2& other) = delete;
	SoftwareSkinningScene_2(SoftwareSkinningScene_2&& other) noexcept = delete;
	SoftwareSkinningScene_2& operator=(const SoftwareSkinningScene_2& other) = delete;
	SoftwareSkinningScene_2& operator=(SoftwareSkinningScene_2&& other) noexcept = delete;



protected:
	void Initialize() override;
	void Update() override;
	void OnGUI() override;

private:
	BoneObject* m_pBone0, * m_pBone1;
	float m_BoneRotation{};
	int m_RotationSign{ 1 };

	struct VertexSoftwareSkinned
	{
		VertexSoftwareSkinned(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT4 color) :
			transformedVertex{ pos, normal, color },
			originalVertex{ pos, normal, color }{}
		VertexPosNormCol transformedVertex{};
		VertexPosNormCol originalVertex{};
	};

	void InitializeVertices(float length);

	MeshDrawComponent* m_pMeshDrawer{};
	std::vector<VertexSoftwareSkinned> m_SkinnedVertices{};
};
