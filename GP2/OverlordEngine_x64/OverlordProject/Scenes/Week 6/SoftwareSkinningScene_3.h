#pragma once

class BoneObject;
class SoftwareSkinningScene_3 : public GameScene
{
public:
	SoftwareSkinningScene_3() :GameScene(L"SoftwareSkinningScene 3"), m_pBone0{ nullptr }, m_pBone1{ nullptr } {}
	~SoftwareSkinningScene_3() override = default;

	SoftwareSkinningScene_3(const SoftwareSkinningScene_3& other) = delete;
	SoftwareSkinningScene_3(SoftwareSkinningScene_3&& other) noexcept = delete;
	SoftwareSkinningScene_3& operator=(const SoftwareSkinningScene_3& other) = delete;
	SoftwareSkinningScene_3& operator=(SoftwareSkinningScene_3&& other) noexcept = delete;



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
		VertexSoftwareSkinned(XMFLOAT3 pos, XMFLOAT3 normal, XMFLOAT4 color, float weight0, float weight1) :
			transformedVertex{ pos, normal, color },
			originalVertex{ pos, normal, color },
			blendWeight0{ weight0 },
			blendWeight1{ weight1 } 
		{}


		VertexPosNormCol transformedVertex{};
		VertexPosNormCol originalVertex{};
		float blendWeight0{};
		float blendWeight1{};

	};

	void InitializeVertices(float length);

	MeshDrawComponent* m_pMeshDrawer{};
	std::vector<VertexSoftwareSkinned> m_SkinnedVertices{};

};

