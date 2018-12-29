#ifndef KMINT_PLAY_ACTOR_HPP
#define KMINT_PLAY_ACTOR_HPP

#include "kmint/math/vector2d.hpp"
#include "kmint/primitives.hpp"
#include "kmint/util/wrapped_iterator.hpp"
#include <cstdint>
#include <functional>
#include <iterator>
#include <vector>

namespace kmint::ui {
class drawable;
}

namespace kmint::play {

using actor_id = std::size_t;

/*! \brief Base class for all actors on the stage.
 *
 * This class provides the interface and some state that is common
 * to all actors that may interact on a stage.
 *
 * Actors should not be constructed directly but rather through \ref stage::build_actor
 */
class actor {
public:
  actor() = default;
  virtual ~actor() = default;

  // remove copy and move operators and constructors
  actor(const actor &) = delete;
  actor(actor &&) = delete;
  actor &operator=(const actor &) = delete;
  actor &operator=(actor &&) = delete;

  /*!
   * Called every tick
   * \param dt the time that has passed since the previous tick
   */
  virtual void act(delta_time dt) { }
  /*!
   * Returns a drawable that determines how this actor is drawn
   */
  virtual const ui::drawable &drawable() const = 0;
  /*!
   * Checks if the actor must be drawn.
   *
   * This determines if an actor must be drawn in a frame. If this function
   * returns false, the drawable method should not be called.
   *
   
* \return true if the actor must be drawn in the next frame. False otherwise.
   */
  virtual bool must_draw() const { return true; }
  virtual math::vector2d location() const = 0;
  /*!
   * Return the collision radius.
   *
   * Each actor has a collision radius. It determines a circular area
   * around the actors location. If another actor comes within this area,
   * it is said to collide with this actor.
   *
   * \return The collision radius of an actor in pixels
   */
  virtual scalar radius() const { return {}; }
  /*!
   * Check if the actor participates in collisions.
   *
   * If an actor is incorporeal (does not have a physical presence), it
   * should not participate in collision detection.
   *
   * \return True if the actor does not participate in collisions. False
   * otherwise.
   */
  virtual bool incorporeal() const { return true; }

  /*!
   * Check if the actor can be seen.
   *
   * If an actor is perceivable then it can be seen by other actors.
   *
   * \return True if the actor can be seen. False otherwise.
   */
  virtual bool perceivable() const { return true; }
  /*!
   * Check if the actor can see.
   *
   * If an actor is perceptive then it may see other perceivable actors.
   *
   * \return True if the actor can see other actor. False otherwise.
   */
  virtual bool perceptive() const { return false; }

  virtual math::vector2d heading() const { return {1.0, 0.0}; }
  virtual scalar range_of_perception() const { return {}; }
  virtual scalar field_of_perception() const { return {}; }

  /*! \brief Calls \a f for every other actor that this actor is in collision
   * with
   *
   * This function will iterate over all actors in the collision set and pass
   * them to its argument \a f. \a f must
   *
   * \param f a callable object that accepts a pointer to an actor
   */
  template <typename F> void handle_collisions(F &&f) const {
    for (auto a : collision_set_) {
      f(*a);
    }
  }

  /*! \brief Registers an actor in the collision set.
   *
   * This method registers another actor in this actor's collision set.
   * \param p The actor with which this actor is colliding
   */
  void register_collision(actor &p);
  /*! \brief Registers an actor in the perceived set.
   *
   * \param p The actor that this actor is perceiving
   */
  void register_perceived(actor &p);

  /*! \brief Clears the collision set
   */
  void empty_collisions() { collision_set_.clear(); }
  /*! \brief Clears the perceived set
   */
  void empty_perceived() { perceived_set_.clear(); }
  using interaction_iterator =
      util::wrapped_iterator<actor, typename std::vector<actor *>::iterator>;
  using const_interaction_iterator =
      util::wrapped_iterator<actor const,
                             typename std::vector<actor *>::const_iterator>;

  /*! \brief Gets an actor from the collision set
   * 
   * The index must be less than the value returned by num_colliding_actors.
   * Otherwise, the behavior of this method is undefined.
   *
   * \param index A valid index into the collision set
   */
  actor &colliding_actor(std::size_t index) {
    auto i = begin_collision() + index;
    return *i;
  }
  /*! \brief Gets an actor from the collision set
   * 
   * The index must be less than the value returned by num_colliding_actors.
   * Otherwise, the behavior of this method is undefined.
   *
   * \param index A valid index into the collision set
   */
  actor const &colliding_actor(std::size_t index) const {
    auto i = begin_collision() + index;
    return *i;
  }
  /*! \brief Gets the number of actors in the collision set
   */
  std::size_t num_colliding_actors() const {
    return end_collision() - begin_collision();
  }
  /*! \brief Gets an iterator to the beginning of the collision set
   *
   * If the collision set is empty, the iterator returned is equal to
   * that returned by end_collision()
   */
  interaction_iterator begin_collision() {
    return util::wrap_iterator<actor>(collision_set_.begin(), deref_actor);
  }
  /*! \brief Gets a  const iterator to the beginning of the collision set
   *
   * If the collision set is empty, the iterator returned is equal to
   * that returned by end_collision()
   */
  const_interaction_iterator begin_collision() const {
    return util::wrap_iterator<actor const>(collision_set_.begin(),
                                            deref_actor_const);
  }

  /*! \brief Gets an iterator at one-past-the-end of the collision set
   */
  interaction_iterator end_collision() {
    return util::wrap_iterator<actor>(collision_set_.end(), deref_actor);
  }

  /*! \brief Gets a  const iterator at one-past-the-end of the collision set
   */
  const_interaction_iterator end_collision() const {
    return util::wrap_iterator<actor const>(collision_set_.end(),
                                            deref_actor_const);
  }

  /*! \brief Gets the number of actors in the perceived set
   */
  std::size_t num_perceived_actors() const {
    return end_perceived() - begin_perceived();
  }

  /*! \brief Gets an actor from the perceived set
   * 
   * The index must be less than the value returned by num_perceived_actors.
   * Otherwise, the behavior of this method is undefined.
   *
   * \param index A valid index into the perceived set
   */
  actor &perceived_actor(std::size_t index) {
    auto i = begin_perceived() + index;
    return *i;
  }

  /*! \brief Gets an actor from the perceived set
   * 
   * The index must be less than the value returned by num_perceived_actors.
   * Otherwise, the behavior of this method is undefined.
   *
   * \param index A valid index into the perceived set
   */
  actor const &perceived_actor(std::size_t index) const {
    auto i = begin_perceived() + index;
    return *i;
  }

  /*! \brief Gets an iterator to the beginning of the perceived set
   *
   * If the perceived set is empty, the iterator returned is equal to
   * that returned by end_perceived()
   */
  interaction_iterator begin_perceived() {
    return util::wrap_iterator<actor>(perceived_set_.begin(), deref_actor);
  }
  /*! \brief Gets a  const iterator to the beginning of the perceived set
   *
   * If the perceived set is empty, the iterator returned is equal to
   * that returned by end_perceived()
   */
  const_interaction_iterator begin_perceived() const {
    return util::wrap_iterator<actor const>(perceived_set_.begin(),
                                            deref_actor_const);
  }
  /*! \brief Gets a iterator at one-past-the-end of the collision set
   */
  interaction_iterator end_perceived() {
    return util::wrap_iterator<actor>(perceived_set_.end(), deref_actor);
  }
  /*! \brief Gets a const iterator at one-past-the-end of the collision set
   */
  const_interaction_iterator end_perceived() const {
    return util::wrap_iterator<actor const>(perceived_set_.end(),
                                            deref_actor_const);
  }

private:
  std::vector<actor *> collision_set_;
  std::vector<actor *> perceived_set_;
  static actor &deref_actor(actor *ptr) { return *ptr; }
  static actor const &deref_actor_const(actor const *ptr) { return *ptr; }
};

/*!
 * Determine if two actors have collided
 * \param a1 One of the actors potentially participating in the collision
 * \param a2 The other actor potentially participating in the collision
 * \return true if the collision radii of the two actors overlap
 */
inline bool collision(actor const &a1, actor const &a2) {
  return !a1.incorporeal() && !a2.incorporeal() &&
         math::distance(a1.location(), a2.location()) <
             a1.radius() + a2.radius();
}

/*!
 * Determine if an observer can see a candidate actor.
 * \param observer The actor that is observing its environment
 * \param candidate An actor the observer may or may not see.
 * \return true if candidate is within the range of perception of observer
 */
inline bool sees(actor const &observer, actor const &candidate) {
  if (!observer.perceptive() || !candidate.perceivable())
    return false;
  auto dist2 = math::distance2(observer.location(), candidate.location());
  auto rop = observer.range_of_perception();
  return dist2 < (rop * rop);
}
} // namespace kmint::play

#endif /* KMINT_PLAY_ACTOR_HPP */
