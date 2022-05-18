#pragma once




class GrassSlice final : public GameObject
{

public:
	GrassSlice();
	~GrassSlice() override = default;

	GrassSlice(const GrassSlice& other) = delete;
	GrassSlice(GrassSlice&& other) noexcept = delete;
	GrassSlice& operator=(const GrassSlice& other) = delete;
	GrassSlice& operator=(GrassSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

};

