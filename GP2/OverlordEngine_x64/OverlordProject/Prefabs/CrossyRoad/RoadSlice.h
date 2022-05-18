#pragma once


class RoadSlice final : public GameObject
{

public:
	RoadSlice();
	~RoadSlice() override = default;

	RoadSlice(const RoadSlice& other) = delete;
	RoadSlice(RoadSlice&& other) noexcept = delete;
	RoadSlice& operator=(const RoadSlice& other) = delete;
	RoadSlice& operator=(RoadSlice&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext& sceneContext) override;
	void Update(const SceneContext& sceneContext) override;

private:

};

