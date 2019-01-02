#include "kmint/pigisland/properties/Kinematic.h"
#include "kmint/pigisland/properties/Steering.h"

Kinematic::Kinematic(const kmint::math::vector2d &position, float orientation, const kmint::math::vector2d &velocity, float rotationVel)
	:mPosition(position)
	, mOrientation(orientation)
	, mVelocity(velocity)
	, mRotationVel(rotationVel)
{
}

Kinematic::~Kinematic()
{
}

kmint::math::vector2d Kinematic::update(float time)
{
	mPosition += mVelocity * time;
	mOrientation += mRotationVel * time;
	//heavily tweak mposition
	return mPosition;
}

void Kinematic::calcNewVelocities(const Steering& theSteering, float time, float maxSpeed, float maxRotationalVelocity)
{
	mVelocity += theSteering.getLinear() * time;
	mRotationVel += theSteering.getAngular() * time;

	//cap the velocities
	capVelocity(maxSpeed);
	if (mRotationVel > maxRotationalVelocity)
	{
		mRotationVel = maxRotationalVelocity;
	}
}

// al_fixed Kinematic::getRotation() const
// {
// 	return getRotationFromRadians(mOrientation);
// }

void Kinematic::capVelocity(float maxSpeed)
{
	// if (mVelocity.getLengthSquared() > (maxSpeed * maxSpeed))
	// {
	// 	mVelocity.normalize();
	// 	mVelocity *= maxSpeed;
	// }
}

kmint::math::vector2d Kinematic::getOrientationAsVector()
{
	//std::cout << mOrientation << " : " << sinf(mOrientation) << ", " << cosf(mOrientation) << std::endl;

	return kmint::math::vector2d(sinf(mOrientation), cosf(mOrientation));
}

//static
// al_fixed Kinematic::getRotationFromRadians(float radians)
// {
// 	al_fixed angle = al_ftofix(radians * 128 / PI);
// 	return angle;
// }

//static
float Kinematic::getOrientationFromVelocity(float currentOrientation, const kmint::math::vector2d& velocity)
{
	if (velocity.x() != 0 && velocity.y() != 0)
	{
		currentOrientation = atan2(velocity.x(), -velocity.y());
	}
	return currentOrientation;
}