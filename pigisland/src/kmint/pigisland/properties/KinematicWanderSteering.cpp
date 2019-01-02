#include "kmint/properties/KinematicWanderSteering.h"
#include "kmint/properties/KinematicUnit.h"

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover, kmint::math::vector2d nullVector)
	: mpMover(pMover)
{
	mApplyDirectly = false;
}

float genRandomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

float genRandomBinomial()
{
	return genRandomFloat() - genRandomFloat();
}

Steering* KinematicWanderSteering::getSteering()
{
	mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);

	return this;
}


