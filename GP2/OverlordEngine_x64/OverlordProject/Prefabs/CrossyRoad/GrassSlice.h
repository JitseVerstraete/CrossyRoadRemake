#pragma once

class GrassSlice final : public GameObject
{

public:
	GrassSlice(int obstacles, int maxWidth,unsigned int grassAmount = 0);
	~GrassSlice() override = default;

	GrassSlice(const GrassSlice& other) = delete;
	GrassSlice(GrassSlice&& other) noexcept = delete;
	GrassSlice& operator=(const GrassSlice& other) = delete;
	GrassSlice& operator=(GrassSlice&& other) noexcept = delete;

	bool IsPassable(int x);

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;
	void Draw(const SceneContext& sceneContext) override;

private:

	//stores an obstacle &it's x value
	std::map<int, GameObject*> m_Obstacles{};
	int m_NrObstacles{};
	int m_MaxWidth{};

	static int m_GrassSliceCounter;
	const XMFLOAT4 m_DarkGrassColor = MathHelper::HSLtoRGB(100.f / 360, 0.6f, 0.46f, 1.f);
	const XMFLOAT4 m_LightGrassColor = MathHelper::HSLtoRGB(100.f / 360, 0.6f, 0.5f, 1.f);

	//grass shader
	ID3DX11Effect* m_pGrassEffect{};
	ID3DX11EffectTechnique* m_pGrassTechnique{};
	ID3D11InputLayout* m_pGrassInputLayout{};

	bool m_BufferMade{};

	ID3D11Buffer* m_pGrassVertexBuffer{};
	unsigned int m_NrGrassBlades{};
	std::vector<VertexGrass> m_GrassPoints{};
};

