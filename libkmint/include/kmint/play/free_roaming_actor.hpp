#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/pigisland/properties/KinematicUnit.h"

namespace kmint::play {
/*! \brief Base class for actors that can move freely across the stage.
 */
class free_roaming_actor : public actor, public KinematicUnit {
public:
  free_roaming_actor(math::vector2d location)
    : actor{},
      KinematicUnit(location_, 0.5f, math::vector2d(), 0.2f, 1.0f, 1.0f, 1.0f, 5.0f),
      location_{location} {
  }

  math::vector2d location() const override { return location_; }
  void act(delta_time dt) override
  {


    // auto dt_s = to_seconds(dt);
    // // calculate the combined force from each steering behavior in the
    // // vehicle’s list
    // math::vector2d SteeringForce = calculate();
    //
    // // Acceleration = Force/Mass
    // math::vector2d acceleration = SteeringForce / mass_;
    //
    // // update velocity
    // velocity_ += acceleration * dt_s /*time_elapsed*/;
    //
    // // make sure vehicle does not exceed maximum velocity
    // velocity_.Truncate(max_speed_);
    // // update the position
    // location() += velocity_ * dt_s/*time_elapsed*/;
    //
    // // update the heading if the vehicle has a velocity greater than a very
    // // small
    // // value
    // if (velocity_.LengthSq() > 0.00000001) {
    //   heading_ = Vec2DNormalize(velocity_);
    //   side_ = heading_.Perp();
    // }
    //
    // // treat the screen as a toroid
    // WrapAround(location_, m_pWorld->cxClient(), m_pWorld->cyClient());
  }

  // math::vector2d calculate()
  // {
  //   // reset the steering force
  //   steering_force_ = steering_force_.
  //   // use space partitioning to calculate the neighbours of this vehicle
  //   // if switched on. If not, use the standard tagging system
  //   if (!isSpacePartitioningOn()) {
  //     // tag neighbors if any of the following 3 group behaviors are switched on
  //     if (On(separation) || On(allignment) || On(cohesion)) {
  //       m_pVehicle->World()->TagVehiclesWithinViewRange(m_pVehicle,
  //                                                       m_dViewDistance);
  //     }
  //   } else {
  //     // calculate neighbours in cell-space if any of the following 3 group
  //     // behaviors are switched on
  //     if (On(separation) || On(allignment) || On(cohesion)) {
  //       m_pVehicle->World()->CellSpace()->CalculateNeighbors(m_pVehicle->Pos(),
  //                                                            m_dViewDistance);
  //     }
  //   }
  //
  //   switch (m_SummingMethod) {
  //   case weighted_average:
  //
  //     steering_force_ = CalculateWeightedSum();
  //     break;
  //
  //   case prioritized:
  //
  //     steering_force_ = CalculatePrioritized();
  //     break;
  //
  //   case dithered:
  //
  //     steering_force_ = CalculateDithered();
  //     break;
  //
  //   default:
  //     steering_force_ = Vector2D(0, 0);
  //
  //   } // end switch
  //
  //   return steering_force_;
  // }

protected:
  void location(math::vector2d loc) { location_ = loc; }

private:
  math::vector2d location_;
};
} // namespace kmint::play

#endif
