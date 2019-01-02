#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/pigisland/properties/steering_behaviors.h"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor {
public:
  free_roaming_actor(math::vector2d location)
      : actor{}, location_{location} {}

  math::vector2d location() const override { return location_; }

  void act(delta_time dt) override {  
  }

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  math::vector2d location_;
};
} // namespace kmint::play

#endif
