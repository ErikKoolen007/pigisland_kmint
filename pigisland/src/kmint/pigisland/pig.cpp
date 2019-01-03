#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include <iostream>

namespace kmint {
namespace pigisland {

namespace {

math::vector2d random_vector() {
  auto x = random_scalar(150, 874);
  auto y = random_scalar(100, 678);
  return {x, y};
}
} // namespace

pig::pig(math::vector2d location, chromosome chromosome, pigisland::shark& shark, pigisland::boat& boat)
	: free_roaming_actor{ random_vector() }, drawable_{ *this, pig_image() }, chromosome_(chromosome), shark(shark), boat(boat)
{
	behaviors_ = properties::steering_behaviors();
	velocity_ = math::vector2d(behaviors_.fRand(-0.0008, 0.0008), behaviors_.fRand(-0.0008, 0.0008));
	mass_ = 0.25;
	maxSpeed_ = 0.1;
	maxForce_ = 75;
	weightWallAvoidance_ = 1000;

	walls = pigisland::walls();
}
      

void pig::act(delta_time dt) {
	kmint::math::vector2d force;
	math::vector2d steeringForce;

	steeringForce = steeringForce += behaviors_.wander(*this);

	force = behaviors_.wall_avoidance(walls, *this) * weightWallAvoidance_;

	behaviors_.accumulate_force(steeringForce, force, *this);

	//force = behaviors_.seek();

	//Acceleration = Force/Mass
	math::vector2d acceleration = steeringForce / mass_;

	//update velocity_
	velocity_ += acceleration * to_seconds(dt);

	//make sure vehicle does not exceed maximum velocity_
	truncate(velocity_, maxSpeed_);

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
