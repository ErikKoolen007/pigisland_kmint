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
	move(behaviors_.wander(*this));
}
} // namespace pigisland

} // namespace kmint
