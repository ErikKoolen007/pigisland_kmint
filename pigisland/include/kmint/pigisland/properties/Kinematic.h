#pragma once
#include <cmath>
#include "kmint/math/vector2d.hpp"

/*Kinematic - c++ implementation of algorithms described in "Artificial Intelligence for Games", Millington and Funge
Dean Lawson
Champlain College
2011
*/

const double PI = std::atan(1.0) * 4;//could proved useful!

//forward declarations
class Steering;

class Kinematic
{
public:
	Kinematic(const kmint::math::vector2d& position, float orientation, const kmint::math::vector2d& velocity, float rotationVel);
	~Kinematic();

	//move and rotate based on current velocities
	kmint::math::vector2d update(float time);

	//modify current velocities based on passed in Steering for the specified time interval and max speeds
	void calcNewVelocities(const Steering& theSteering, float time, float maxSpeed, float maxRotationalVelocity);

	//static al_fixed getRotationFromRadians(float radians);//useful conversion function

	//make sure that we're not exceeding a provided max speed
	void capVelocity(float maxSpeed);

	//accessors
	//al_fixed getRotation() const;
	static float getOrientationFromVelocity(float currentOrientation, const kmint::math::vector2d& velocity);
	virtual void setNewOrientation() { mOrientation = getOrientationFromVelocity(mOrientation, mVelocity); };
	kmint::math::vector2d getOrientationAsVector();
	float getOrientation() const { return mOrientation; };
	void setOrientation(float orientation) { mOrientation = orientation; };
	void setRotationalVelocity(float rotVel) { mRotationVel = rotVel; };
	float getRotationalVelocity() { return mRotationVel; };


protected:
	kmint::math::vector2d mPosition;//where am I?
	kmint::math::vector2d mVelocity;//how fast am I moving?
	float mOrientation;//where am I facing?
	float mRotationVel;//how fast am I turning?
};