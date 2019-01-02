#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/play/free_roaming_actor.hpp"

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
				void normalize(kmint::math::vector2d target);
			private:
				kmint::math::vector2d wander_target;
				double wander_radius;
				double wander_distance;
				double wander_jitter;
			};

		}
	}
}
