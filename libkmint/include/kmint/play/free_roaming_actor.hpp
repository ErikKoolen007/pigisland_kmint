#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/pigisland/properties/steering_behaviors.h"
#include "kmint/play/actor.hpp"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor {
public:
  free_roaming_actor(math::vector2d location) : actor{}, location_{location} {}

  math::vector2d location() const override { return location_; }
  math::vector2d heading() const override { return heading_; }
  math::vector2d side() const { return side_; }
  math::vector2d velocity() const { return velocity_; }

  double mass() const { return mass_; }
  double maxSpeed() const { return maxSpeed_; }
  double maxForce() const { return maxForce_; }
  double weightWallAvoidance() const { return weightWallAvoidance_; }
  double weightSeek() const { return weightSeek_; }

  void velocity(math::vector2d v) { velocity_ = v; }
  void mass(double mass) { mass_ = mass; }
  void maxSpeed(double maxSpeed) { maxSpeed_ = maxSpeed; }
  void maxForce(double maxForce) { maxForce_ = maxForce; }
  void weightWallAvoidance(double weight) { weightWallAvoidance_ = weight; }
  void weightSeek(double weight) { weightSeek_ = weight;  }

  void act(delta_time dt) override {}

protected:
  pigisland::properties::steering_behaviors behaviors_;
  kmint::math::vector2d velocity_;
  double mass_;
  double maxSpeed_;
  double maxForce_;
  double weightWallAvoidance_;
  double weightSeek_;
  void location(math::vector2d loc) { location_ = loc; }
  void heading(math::vector2d heading) { heading_ = heading; }
  void side(math::vector2d side) { side_ = side; }

private:
  math::vector2d location_;
  math::vector2d heading_;
  math::vector2d side_;
};
} // namespace kmint::play

#endif
