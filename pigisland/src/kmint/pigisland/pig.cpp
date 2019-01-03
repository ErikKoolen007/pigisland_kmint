#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint {
namespace pigisland {

pig::pig(math::vector2d location, chromosome chromosome)
	: free_roaming_actor{ location }, drawable_{ *this, pig_image() }, chromosome_(chromosome) {}
      

void pig::act(delta_time dt) {
  free_roaming_actor::act(dt);
}
} // namespace pigisland

} // namespace kmint
