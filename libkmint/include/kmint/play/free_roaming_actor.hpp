#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor {
public:
  free_roaming_actor(math::vector2d location) : actor{}, location_{location} {}
  math::vector2d location() const override { return location_; }
  void act(delta_time dt) override
  {
    auto dt_s = to_seconds(dt);
    // calculate the combined force from each steering behavior in the
    // vehicle’s list
    math::vector2d SteeringForce = m_pSteering->Calculate();

    // Acceleration = Force/Mass
    math::vector2d acceleration = SteeringForce / mass_;

    // update velocity
    velocity_ += acceleration * dt_s /*time_elapsed*/;

    // make sure vehicle does not exceed maximum velocity
    velocity_.Truncate(max_speed_);
    // update the position
    location() += velocity_ * dt_s/*time_elapsed*/;

    // update the heading if the vehicle has a velocity greater than a very
    // small
    // value
    if (velocity_.LengthSq() > 0.00000001) {
      heading_ = Vec2DNormalize(velocity_);
      side_ = heading_.Perp();
    }

    // treat the screen as a toroid
    WrapAround(location_, m_pWorld->cxClient(), m_pWorld->cyClient());
  }

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  math::vector2d location_;
  math::vector2d velocity_;
  // a normalized vector pointing in the direction the entity is heading.
  math::vector2d heading_;
  // a vector perpendicular to the heading vector
  math::vector2d side_;
  double mass_;
  // the maximum speed at which this entity may travel.
  double max_speed_;
  // the maximum rate (radians per second) at which this vehicle can rotate
  double max_turnrate_;
  // the maximum force this entity can produce to power itself
  double max_force;


};
} // namespace kmint::play

#endif
