#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/pigisland/properties/KinematicUnit.h"
#include "kmint/play/actor.hpp"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor, public KinematicUnit {
public:
  free_roaming_actor(math::vector2d location)
      : actor{}, KinematicUnit(location_, 0.5f, this->location(), 0.2f, 1.0f,
                               1.0f, 1.0f, 5.0f),
        location_{location} {}

  math::vector2d location() const override { return location_; }

  void act(delta_time dt) override {
    this->location() = update(to_seconds(dt));

  }

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  math::vector2d location_;
};
} // namespace kmint::play

#endif
