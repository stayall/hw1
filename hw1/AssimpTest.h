#include "testGraphics.h"

class AssTest :  public TestGraphics<AssTest>
{
public:
	AssTest(Graphics& ghs, const char* filepath, 
		std::mt19937& mt,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& cdist);

	virtual void update(float dt) noexcept override;

	virtual DirectX::XMMATRIX getMatrix() const noexcept override;


};
