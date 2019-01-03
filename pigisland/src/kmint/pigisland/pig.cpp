#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include <iostream>

namespace kmint {
namespace pigisland {

namespace {

math::vector2d random_vector() {
  auto x = random_scalar(100, 924);
  auto y = random_scalar(50, 728);
  return {x, y};
}
} // namespace

pig::pig(math::vector2d location)
	: free_roaming_actor{ random_vector() }, drawable_{ *this, pig_image() }
{
	behaviors_ = properties::steering_behaviors();
}
      

void pig::act(delta_time dt) {

	math::vector2d SteeringForce;
	SteeringForce = SteeringForce += behaviors_.wander(*this);

	//Acceleration = Force/Mass
	math::vector2d acceleration = SteeringForce / mass;

	//update velocity
	velocity += acceleration * to_seconds(dt);

	//make sure vehicle does not exceed maximum velocity
	truncate(velocity, maxSpeed);

	//update the position
	move(velocity * to_seconds(dt));

	//update the heading if the vehicle has a non zero velocity
	if (dot(velocity, velocity) > 0.00000001)
	{
		//generate setters of these two
		heading(behaviors_.normalize(velocity));
		side(perp(heading()));
	}
}
} // namespace pigisland

} // namespace kmint
