#include "kmint/pigisland/properties/steering_behaviors.h"
#include "kmint/play/free_roaming_actor.hpp"
#include "kmint/random.hpp"
#include <valarray>

kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::wander(play::free_roaming_actor& actor)
{
	float r = ((rand()) / (RAND_MAX + 1.0));
	//first, add a small random vector to the target’s position (RandomClamped
	//returns a value between -1 and 1)
	wander_target += kmint::math::vector2d(r * wander_jitter, r * wander_jitter);

	//reproject this new vector back onto a unit circle
	normalize(wander_target);

	//increase the length of the vector to the same as the radius
	//of the wander circle
	wander_target *= wander_radius;

	//move the target into a position WanderDist in front of the agent
	kmint::math::vector2d targetLocal = wander_target + kmint::math::vector2d(wander_distance, 0);

	//project the target into world space
	// kmint::math::vector2d targetWorld = PointToWorldSpace(targetLocal,
	// 	actor.Heading(),
	// 	actor.Side(),
	// 	actor.Pos());

	//and steer toward it
	return targetLocal- actor.location();
}

void kmint::pigisland::properties::steering_behaviors::normalize(kmint::math::vector2d target)
{ 
	double vector_length = std::sqrt(std::pow(target.x(), 2) * std::pow(target.y(), 2));

	if (vector_length > std::numeric_limits<double>::epsilon())
	{
		target.x(target.x() / vector_length);
		target.y(target.y() / vector_length);
	}
}
