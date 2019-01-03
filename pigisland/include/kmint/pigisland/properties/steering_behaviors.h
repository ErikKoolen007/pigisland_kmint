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
				kmint::math::vector2d normalize(kmint::math::vector2d target);
				kmint::math::vector2d truncate(double max, kmint::math::vector2d & target);
				double fRand(double fMin, double fMax);
			private:
				kmint::math::vector2d wander_target;
				double wander_radius = 0.01;
				double wander_distance = 0.01;
				double wander_jitter = 1000.0;
				//math::vector2d steering_force = wander();
				kmint::math::vector2d PointToWorldSpace(const kmint::math::vector2d& point,
				                                        const kmint::math::vector2d& AgentHeading,
				                                        const kmint::math::vector2d& AgentSide,
				                                        const kmint::math::vector2d& AgentPosition);
			};

		}
	}
}
