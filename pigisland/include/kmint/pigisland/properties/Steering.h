#pragma once
/*Steering - implementation of Steering class from "Artificial Intelligence for Games" - Millington and Funge
	Mostly modified by adding the mApplyDirectly bool variable to indicate if this Steering should operate as an override on the Kinematic's velocities
	or if it should be additive with those velocities.  Arrive (amoung others) requires direct application to work where as Seek operates by influencing
	the Kinematic's velocities rather than over-riding them.
	Steering is a base class for the various types of steering behaviors which require their own algorithms.  Those algorithms are encoded in the
	subclass's getSteering function.
	Dean Lawson
	Champlain College
	2011
*/

#include "Kinematic.h"
#include "kmint/math/vector2d.hpp"
#include "kmint/ui/events/event.hpp"

class Steering
{
public:
	//constructors and destructors
	Steering(const kmint::math::vector2d theLinear = kmint::math::vector2d(), float theAngular = 0.0f, bool applyDirectly = false) :mLinear(theLinear), mAngular(theAngular) {};
	Steering(const Steering& rhs) :mLinear(rhs.mLinear), mAngular(rhs.mAngular), mApplyDirectly(rhs.mApplyDirectly) {};
	virtual ~Steering() {};

	//accessors
	const kmint::math::vector2d& getLinear() const { return mLinear; };
	float getAngular() const { return mAngular; };
	void setLinear(const kmint::math::vector2d& linear) { mLinear = linear; };
	void setAngular(float angular) { mAngular = angular; };
	bool shouldApplyDirectly() const { return mApplyDirectly; };

	virtual Steering* getSteering() { return this; };//overridden by sub-classes
	float mapToRange(float orientation);

protected:
	kmint::math::vector2d mLinear;//linear velocity
	float mAngular;//angular velocity
	bool mApplyDirectly;

};
