
#include <iostream>
#include "kmint/pigisland/properties/KinematicUnit.h"
#include "kmint/math/vector2d.hpp"
#include "kmint/pigisland/properties/KinematicWanderSteering.h"

KinematicUnit::KinematicUnit(const kmint::math::vector2d &position, float orientation, const kmint::math::vector2d &velocity, float rotationVel, float maxVelocity = 1.0f, float maxAcceleration = 1.0f, float maxRotation = 1.0f, float maxRotationalVelocity = 5.0f)
	:Kinematic(position, orientation, velocity, rotationVel)
	, mpCurrentSteering(NULL)
	, mMaxVelocity(maxVelocity)
	, mMaxAcceleration(maxAcceleration)
	, mMaxRotation(maxRotation)
	, mMaxRotationalVelocity(maxRotationalVelocity)
{
}

KinematicUnit::~KinematicUnit()
{
	delete mpCurrentSteering;
}

// void KinematicUnit::draw(GraphicsBuffer* pBuffer)
// {
// 	mpSprite->draw(*pBuffer, mPosition.x(), mPosition.y(), mOrientation);
// }

kmint::math::vector2d KinematicUnit::update(float time)
{
	wander();
	Steering* steering;
	if (mpCurrentSteering != NULL)
		steering = mpCurrentSteering->getSteering();
	else
		steering = NULL;

	if (steering->shouldApplyDirectly())
	{
		//not stopped
		// if (getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
		// {
			setVelocity(steering->getLinear());
			setOrientation(steering->getAngular());
		// }

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		steering->setAngular(0.0f);
	}
	else
		setNewOrientation();

	//calculate new velocities
	calcNewVelocities(*steering, time, mMaxVelocity, mMaxRotationalVelocity);

	//move the unit using current velocities
	mPosition = Kinematic::update(time);

	//move to oposite side of screen if we are off
	//GRAPHICS_SYSTEM->wrapCoordinates(mPosition);

	//set the orientation to match the direction of travel
	//setNewOrientation();

	return mPosition;
}

//private - deletes old Steering before setting
void KinematicUnit::setSteering(Steering* pSteering)
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setNewOrientation()
{
	mOrientation = getOrientationFromVelocity(mOrientation, mVelocity);
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering(this);
	setSteering(pWanderSteering);
}


// void KinematicUnit::dynamicFlocking()
// {
// 	DynamicFlockingSteering* pDynamicFlockingSteering = new DynamicFlockingSteering(this);
// 	setSteering(pDynamicFlockingSteering);
// }