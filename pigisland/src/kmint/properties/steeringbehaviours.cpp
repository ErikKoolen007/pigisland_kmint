#include "kmint/play/free_roaming_actor.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/properties/steeringbehaviours.h"


kmint::math::vector2d steeringbehaviours::wander(kmint::pigisland::pig& agent)
{
	//this behavior is dependent on the update rate, so this line must
	//be included when using time independent framerate.
	double JitterThisTimeSlice = 80.0 * agent.TimeElapsed();

	//first, add a small random vector to the target's position
	m_vWanderTarget += kmint::math::vector2d(RandomClamped() * JitterThisTimeSlice,
		RandomClamped() * JitterThisTimeSlice);

	//reproject this new vector back on to a unit circle
	m_vWanderTarget.Normalize();

	//increase the length of the vector to the same as the radius
	//of the wander circle
	m_vWanderTarget *= m_dWanderRadius;

	//move the target into a position WanderDist in front of the agent
	kmint::math::vector2d target = m_vWanderTarget + Vector2D(m_dWanderDistance, 0);

	//project the target into world space
	kmint::math::vector2d Target = PointToWorldSpace(target,
		agent.Heading(),
		agent.Side(),
		agent.Pos());

	//and steer towards it
	return Target - agent.location();
}

