#pragma once

#include "DynamicFaceSteering.h"
#include <math.h>
#include "kmint/math/matrix.hpp"
#include "kmint/math/vector2d.hpp"
#include "Steering.h"

class KinematicUnit;

class DynamicWanderSteering : public DynamicFaceSteering
{
public:
	//DynamicWanderSteering(KinematicUnit* pMover, float wanderOffset = 50.0f, float wanderRadius = 80.0f, float wanderRate = 0.5f, float wanderOrientation = 10.0f, float targetRadius = 5.0f, float slowRadius = 10.0f, float timeToTarget = 5.0f);
	DynamicWanderSteering(KinematicUnit* pMover, float wanderOffset = 0.0f, float wanderRadius = 80.0f, float wanderRate = 0.5f, float wanderOrientation = 10.0f, float targetRadius = 5.0f, float slowRadius = 10.0f, float timeToTarget = 5.0f);
	~DynamicWanderSteering() {};

	virtual Steering* getSteering();

	inline kmint::math::vector2d asVector(float orientation) { return kmint::math::vector2d(sinf(orientation), cosf(orientation)); };
private:
	KinematicUnit* mpMover;
	float mWanderOffset,
		mWanderRadius,
		mWanderRate,
		mWanderOrientation;

	int mFrameCount;
};