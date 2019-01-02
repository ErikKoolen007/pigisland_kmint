#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"

namespace kmint {
	namespace play {
		class free_roaming_actor;
	}
}

namespace kmint
{
	namespace pigisland
	{
		namespace properties {
			class steering_behaviors
			{
			public: 
				steering_behaviors() = default;
				kmint::math::vector2d wander(play::free_roaming_actor& actor);
			private:
				kmint::math::vector2d wander_target;
				double wander_radius = 1.2;
				double wander_distance = 2.0;
				double wander_jitter = 80.0;
				//math::vector2d steering_force = wander();
				void normalize(kmint::math::vector2d target);
			};

		}
	}
}
