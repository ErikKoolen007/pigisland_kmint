#include "kmint/pigisland/properties/KinematicWanderSteering.h"
#include "kmint/pigisland/properties/KinematicUnit.h"

KinematicWanderSteering::KinematicWanderSteering(KinematicUnit *pMover)
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


