#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"

namespace kmint {
	namespace pigisland {
		class pig;
	}
}

class steeringbehaviours
{
	kmint::math::vector2d wander(kmint::pigisland::pig& agent);
};
