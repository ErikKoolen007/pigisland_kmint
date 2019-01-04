#pragma once
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include "Wall2D.h"
#include <vector>

namespace kmint {
	namespace pigisland {
		class pig;
	}
}

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
				kmint::math::vector2d wall_avoidance(const std::vector<Wall2D>& walls, play::free_roaming_actor& actor);
				kmint::math::vector2d seek(kmint::math::vector2d TargetPos, kmint::play::free_roaming_actor& actor);
				kmint::math::vector2d flee(kmint::math::vector2d TargetPos, kmint::play::free_roaming_actor& actor);
				kmint::math::vector2d separation(kmint::play::free_roaming_actor& actor, std::vector<pigisland::pig*>& neighbors);
				kmint::math::vector2d alignment(kmint::play::free_roaming_actor& actor,
				                                std::vector<pigisland::pig*>& neighbors);
				kmint::math::vector2d cohesion(kmint::play::free_roaming_actor& actor,
				                               std::vector<pigisland::pig*>& neighbors);
				kmint::math::vector2d normalize(kmint::math::vector2d target);
				kmint::math::vector2d truncate(double max, kmint::math::vector2d & target);
				double fRand(double fMin, double fMax);
				double calcVLength(kmint::math::vector2d target);
				bool accumulate_force(kmint::math::vector2d& RunningTot, kmint::math::vector2d ForceToAdd,
					play::free_roaming_actor& actor);
			private:
				//a vertex buffer to contain the feelers rqd for wall avoidance  
				std::vector<math::vector2d> m_Feelers = std::vector<math::vector2d>(3);
				kmint::math::vector2d wander_target;
				double wander_radius = 0.0015;
				double wander_distance = 0.002;
				double wander_jitter = 1000.0;

				kmint::math::vector2d PointToWorldSpace(const kmint::math::vector2d& point,
				                                        const kmint::math::vector2d& AgentHeading,
				                                        const kmint::math::vector2d& AgentSide,
				                                        const kmint::math::vector2d& AgentPosition);
				void CreateFeelers(play::free_roaming_actor& actor);
				void vec2D_rotate_around_origin(kmint::math::vector2d& v, double ang);
				bool line_intersection2D(kmint::math::vector2d A, kmint::math::vector2d B, kmint::math::vector2d C,
				                         kmint::math::vector2d D, double& dist, kmint::math::vector2d& point);
			};

		}
	}
}
