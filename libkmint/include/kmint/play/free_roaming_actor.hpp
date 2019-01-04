#ifndef KMINT_PLAY_FREE_ROAMING_ACTOR_H
#define KMINT_PLAY_FREE_ROAMING_ACTOR_H

#include "kmint/math/vector2d.hpp"
#include "kmint/pigisland/properties/steering_behaviors.h"
#include "kmint/play/actor.hpp"
#include "stage.hpp"

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
  double weightFlee() const { return weightFlee_; }
  double weightWander() const { return weightWander_; }
  double boundingRadius() const { return boundingRadius_; }
  bool isTagged() const { return neightborTag_; }

  void velocity(math::vector2d v) { velocity_ = v; }
  void mass(double mass) { mass_ = mass; }
  void maxSpeed(double maxSpeed) { maxSpeed_ = maxSpeed; }
  void maxForce(double maxForce) { maxForce_ = maxForce; }
  void weightWallAvoidance(double weight) { weightWallAvoidance_ = weight; }
  void weightSeek(double weight) { weightSeek_ = weight;  }
  void weightFlee(double weight) { weightFlee_ = weight; }
  void weightWander(double weight) { weightWander_ = weight; }
  void unTag() { neightborTag_ = false; }
  void tag() { neightborTag_ = true; }
  void boundingRadius(double radius) { boundingRadius_ = radius; }

  void act(delta_time dt) override {}

protected:
  pigisland::properties::steering_behaviors behaviors_;
  kmint::math::vector2d velocity_;
  double mass_;
  double maxSpeed_;
  double maxForce_;
  double weightWallAvoidance_;
  double weightSeek_;
  double weightFlee_;
  double weightWander_;
  double neightborTag_;
  double boundingRadius_;
  void location(math::vector2d loc) { location_ = loc; }
  void heading(math::vector2d heading) { heading_ = heading; }
  void side(math::vector2d side) { side_ = side; }

  template <class T, class conT>
  void tagNeighbors(const T &entity, conT &ContainerOfEntities, double radius) {
    // iterate through all entities checking for range
    for (typename conT::iterator curEntity = ContainerOfEntities.begin();
         curEntity != ContainerOfEntities.end(); ++curEntity) {
        // first clear any current tag
        (*curEntity)->unTag();
        math::vector2d to = (*curEntity)->location() - entity.location();
        // the bounding radius of the other is taken into account by adding it
        // to the range
        double range = radius + (*curEntity)->boundingRadius();
        // if entity within range, tag for further consideration. (working in
        // distance-squared space to avoid sqrts)
        if ((/*(*curEntity) != entity) &&*/
            ((to.x() * to.x() + to.y() * to.y()) < range * range))) {
          (*curEntity)->tag();
        }
    } // next entity
  }

private:
  math::vector2d location_;
  math::vector2d heading_;
  math::vector2d side_;
};
} // namespace kmint::play
inline bool operator==(const kmint::play::free_roaming_actor &lhs,
                       const kmint::play::free_roaming_actor &rhs) {
  return (lhs.location().x() == rhs.location().x() &&
          lhs.location().y() == rhs.location().y() &&
          lhs.velocity().x() == rhs.velocity().x() &&
          lhs.velocity().y() == rhs.velocity().y());
}

inline bool operator!=(const kmint::play::free_roaming_actor &lhs,
                       const kmint::play::free_roaming_actor &rhs) {
  return !(lhs == rhs);
}
#endif
