#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include <iostream>

namespace kmint {
namespace pigisland {

//namespace {

//math::vector2d random_vector() {
  // auto x = random_scalar(150, 874);
  // auto y = random_scalar(100, 678);
  //return {x, y};
//}
//} // namespace

pig::pig(math::vector2d location, play::stage& s, chromosome chromosome,
         pigisland::shark& shark, pigisland::boat& boat)
	: free_roaming_actor{ location }, drawable_{ *this, pig_image() }, stage_(s), chromosome_(chromosome), shark(shark), boat(boat)
{
	behaviors_ = properties::steering_behaviors();
	velocity_ = math::vector2d(behaviors_.fRand(-0.0008, 0.0008), behaviors_.fRand(-0.0008, 0.00080));
	mass_ = 1;
	maxSpeed_ = 40;
	maxForce_ = 100;
	//NOTE: these weight modifiers are used to tweak
	weightWallAvoidance_ = 10000;
	weightSeek_ = 35;
	weightFlee_ = 35;
	weightWander_ = 8;
	weightSeparation_ = 10;
	weightCohesion_ = 0.125;
	weightAlignment_ = 7.5;
	neightborTag_ = false;
	boundingRadius_ = 25;

	walls = pigisland::walls();
}
      

void pig::act(delta_time dt) {
	kmint::math::vector2d force;
	math::vector2d steeringForce;

	//individual behaviours
	steeringForce = steeringForce += behaviors_.wander(*this) * weightWander_;

	force = behaviors_.seek(boat.location(), *this) * weightSeek_ * chromosome_.get()[1];

	behaviors_.accumulate_force(steeringForce, force, *this);

	force = behaviors_.flee(shark.location(), *this) * weightFlee_ * chromosome_.get()[0];

	behaviors_.accumulate_force(steeringForce, force, *this);

	force = behaviors_.wall_avoidance(walls, *this) * weightWallAvoidance_;

	behaviors_.accumulate_force(steeringForce, force, *this);

	std::vector<pig*> neighbor_vector{};
	for (play::actor& a : stage_)
	{
		if (a.name() == "pig")
		{
			pig* p = static_cast<pig*>(&a);
			neighbor_vector.push_back(p);
		}
	}

	//group behaviour
	this->tagNeighbors(*this, neighbor_vector, 25);

	force = behaviors_.separation(*this, neighbor_vector) * weightSeparation_ * chromosome_.get()[3];

	behaviors_.accumulate_force(steeringForce, force, *this);

	force = behaviors_.alignment(*this, neighbor_vector) * weightAlignment_ * chromosome_.get()[4];

	behaviors_.accumulate_force(steeringForce, force, *this);
	
	force = behaviors_.cohesion(*this, neighbor_vector) * weightCohesion_ * chromosome_.get()[2];
	
	behaviors_.accumulate_force(steeringForce, force, *this);

	//Acceleration = Force/Mass
	math::vector2d acceleration = steeringForce / mass_;

	//update velocity_
	velocity_ += acceleration * to_seconds(dt);

	//make sure vehicle does not exceed maximum velocity_
	velocity_ = truncate(velocity_, maxSpeed_);

	//update the position
	move(velocity_ * to_seconds(dt));

	//update the heading if the vehicle has a non zero velocity_
	if (dot(velocity_, velocity_) > 0.00000001)
	{
		//generate setters of these two
		heading(behaviors_.normalize(velocity_));
		side(perp(heading()));
	}
}
} // namespace pigisland

} // namespace kmint
