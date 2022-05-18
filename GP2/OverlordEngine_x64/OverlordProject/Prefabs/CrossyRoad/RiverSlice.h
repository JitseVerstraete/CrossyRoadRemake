#pragma once


class RiverSlice final : public GameObject
{

public:
	RiverSlice();
	~RiverSlice() override = default;

	RiverSlice(const RiverSlice& other) = delete;
	RiverSlice(RiverSlice&& other) noexcept = delete;
	RiverSlice& operator=(const RiverSlice& other) = delete;
	RiverSlice& operator=(RiverSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

};
