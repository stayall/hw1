#include "DrawableBase.h"
#include <random>

template<class T>
class TestGraphics : public DrawableBase<T>
{
protected:
	TestGraphics(
		std::mt19937& mt,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		std::uniform_real_distribution<float>& cdist
	);
protected:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};

template<class T>
inline TestGraphics<T>::TestGraphics(std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist, std::uniform_real_distribution<float>& cdist)
: r(rdist(rng)),
droll(ddist(rng)),
dpitch(ddist(rng)),
dyaw(ddist(rng)),
dphi(odist(rng)),
dtheta(odist(rng)),
dchi(odist(rng)),
chi(adist(rng)),
theta(adist(rng)),
phi(adist(rng))
{
}
