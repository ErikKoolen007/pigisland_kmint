#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  explicit pig(math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceivable() const override { return true; }
  bool perceptive() const override { return true; }
  scalar range_of_perception() const override { return 30.0f; }
  bool incorporeal() const override { return false; }
  std::string name() const override { return "pig"; }

private:
  play::image_drawable drawable_;
  properties::steering_behaviors behaviors_;
  double mass = 1;
  math::vector2d velocity = math::vector2d(behaviors_.fRand(-0.001, 0.001), behaviors_.fRand(-0.001, 0.001));
  //the maximum speed at which this entity may travel.
  double maxSpeed = 0.01;
  //the maximum force this entity can produce to power itself
  //(think rockets and thrust)
  //double maxForce = 100;
  //the maximum rate (radians per
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
