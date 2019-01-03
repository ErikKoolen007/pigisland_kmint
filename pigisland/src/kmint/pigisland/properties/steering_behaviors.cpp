#include "kmint/pigisland/properties/steering_behaviors.h"
#include "kmint/play/free_roaming_actor.hpp"
#include "kmint/random.hpp"
#include <valarray>
#include "kmint/pigisland/properties/C2DMatrix.h"
#include "kmint/pigisland/properties/Wall2D.h"

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
	kmint::math::vector2d targetWorld = PointToWorldSpace(targetLocal,
		actor.heading(),
		actor.side(),
		actor.location());

	//and steer toward it
	return targetWorld- actor.location();
}

kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::wall_avoidance(const std::vector<Wall2D>& walls, play::free_roaming_actor& actor)
{
	//the feelers are contained in a std::vector, m_Feelers
	CreateFeelers(actor);

	double DistToThisIP = 0.0;
	double DistToClosestIP = DBL_MAX;

	//this will hold an index into the vector of walls
	int ClosestWall = -1;

	kmint::math::vector2d SteeringForce,
		point,         //used for storing temporary info
		ClosestPoint;  //holds the closest intersection point

//examine each feeler in turn
	for (unsigned int flr = 0; flr < m_Feelers.size(); ++flr)
	{
		//run through each wall checking for any intersection points
		for (unsigned int w = 0; w < walls.size(); ++w)
		{
			if (line_intersection2D(actor.location(),
				m_Feelers[flr],
				walls[w].From(),
				walls[w].To(),
				DistToThisIP,
				point))
			{
				//is this the closest found so far? If so keep a record
				if (DistToThisIP < DistToClosestIP)
				{
					DistToClosestIP = DistToThisIP;

					ClosestWall = w;

					ClosestPoint = point;
				}
			}
		}//next wall


		//if an intersection point has been detected, calculate a force  
		//that will direct the agent away
		if (ClosestWall >= 0)
		{
			//calculate by what distance the projected position of the agent
			//will overshoot the wall
			kmint::math::vector2d overShoot = m_Feelers[flr] - ClosestPoint;

			//create a force in the direction of the wall normal, with a 
			//magnitude of the overshoot
			double overshootLength = calcVLength(overShoot);
			SteeringForce = walls[ClosestWall].Normal() * overshootLength;
		}

	}//next feeler

	return SteeringForce;
}

kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::Seek(kmint::math::vector2d TargetPos, kmint::play::free_roaming_actor& actor)
{
	kmint::math::vector2d DesiredVelocity = normalize(TargetPos - actor.location())
		* actor.maxSpeed();
	return (DesiredVelocity - actor.velocity());
}

double kmint::pigisland::properties::steering_behaviors::calcVLength(kmint::math::vector2d target) {
	return std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
}

kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::normalize(kmint::math::vector2d target)
{ 
	double vector_length = calcVLength(target);

	if (vector_length > std::numeric_limits<double>::epsilon())
	{
		target.x(target.x() / vector_length);
		target.y(target.y() / vector_length);
	}
	return target;
}

 kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::PointToWorldSpace(const kmint::math::vector2d &point,
	const kmint::math::vector2d &AgentHeading,
	const kmint::math::vector2d &AgentSide,
	const kmint::math::vector2d &AgentPosition)
{
	//make a copy of the point
	 kmint::math::vector2d TransPoint = point;

	//create a transformation matrix
	C2DMatrix matTransform;

	//rotate
	matTransform.Rotate(AgentHeading, AgentSide);

	//and translate
	matTransform.Translate(AgentPosition.x(), AgentPosition.y());

	//now transform the vertices
	matTransform.TransformVector2Ds(TransPoint);

	return TransPoint;
}

 kmint::math::vector2d kmint::pigisland::properties::steering_behaviors::truncate(double max, kmint::math::vector2d& target)
 {
	 double vector_length = std::sqrt(std::pow(target.x(), 2) + std::pow(target.y(), 2));
	 
	 if (vector_length > max)
	 {
		 target = normalize(target);

		 target *= max;
	 }
	 return target;
 }

 double kmint::pigisland::properties::steering_behaviors::fRand(double fMin, double fMax)
 {
	 double f = (double)rand() / RAND_MAX;
	 return fMin + f * (fMax - fMin);
 }

 void kmint::pigisland::properties::steering_behaviors::CreateFeelers(play::free_roaming_actor& actor)
 {
	 const double   HalfPi = 3.14159 / 2;
	//may be needed to tweak
	 float wallDetectionLength = 100;
	 //feeler pointing straight in front
	 m_Feelers[0] = actor.location() + wallDetectionLength * actor.heading();

	 //feeler to left
	 math::vector2d temp = actor.heading();
	 vec2D_rotate_around_origin(temp, HalfPi * 3.5f);
	 m_Feelers[1] = actor.location() + wallDetectionLength / 2.0f * temp;

	 //feeler to right
	 temp = actor.heading();
	 vec2D_rotate_around_origin(temp, HalfPi * 0.5f);
	 m_Feelers[2] = actor.location() + wallDetectionLength / 2.0f * temp;
 }

 void kmint::pigisland::properties::steering_behaviors::vec2D_rotate_around_origin(kmint::math::vector2d& v, double ang)
 {
	 //create a transformation matrix
	 C2DMatrix mat;

	 //rotate
	 mat.Rotate(ang);

	 //now transform the object's vertices
	 mat.TransformVector2Ds(v);
 }

 bool kmint::pigisland::properties::steering_behaviors::line_intersection2D(
	 kmint::math::vector2d A, 
	 kmint::math::vector2d B,
	 kmint::math::vector2d C,
	 kmint::math::vector2d D,
	 double&     dist,
	 kmint::math::vector2d&  point)
 {

	 double rTop = (A.y() - C.y())*(D.x() - C.x()) - (A.x() - C.x())*(D.y() - C.y());
	 double rBot = (B.x() - A.x())*(D.y() - C.y()) - (B.y() - A.y())*(D.x() - C.x());

	 double sTop = (A.y() - C.y())*(B.x() - A.x()) - (A.x() - C.x())*(B.y() - A.y());
	 double sBot = (B.x() - A.x())*(D.y() - C.y()) - (B.y() - A.y())*(D.x() - C.x());

	 if ((rBot == 0) || (sBot == 0))
	 {
		 //lines are parallel
		 return false;
	 }

	 double r = rTop / rBot;
	 double s = sTop / sBot;

	 if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	 {
		 dist = distance(A, B) * r;

		 point = A + r * (B - A);

		 return true;
	 }
	dist = 0;

	return false;
 }

 bool kmint::pigisland::properties::steering_behaviors::accumulate_force(kmint::math::vector2d &RunningTot,
	 kmint::math::vector2d ForceToAdd, play::free_roaming_actor& actor)
 {

	 //calculate how much steering force the vehicle has used so far
	 double MagnitudeSoFar = calcVLength(RunningTot);

	 //calculate how much steering force remains to be used by this vehicle
	 double MagnitudeRemaining = actor.maxForce() - MagnitudeSoFar;

	 //return false if there is no more force left to use
	 if (MagnitudeRemaining <= 0.0) return false;

	 //calculate the magnitude of the force we want to add
	 double MagnitudeToAdd = calcVLength(ForceToAdd);

	 //if the magnitude of the sum of ForceToAdd and the running total
	 //does not exceed the maximum force available to this vehicle, just
	 //add together. Otherwise add as much of the ForceToAdd vector is
	 //possible without going over the max.
	 if (MagnitudeToAdd < MagnitudeRemaining)
	 {
		 RunningTot += ForceToAdd;
	 }

	 else
	 {
		 //add it to the steering force
		 RunningTot += (normalize(ForceToAdd) * MagnitudeRemaining);
	 }

	 return true;
 }