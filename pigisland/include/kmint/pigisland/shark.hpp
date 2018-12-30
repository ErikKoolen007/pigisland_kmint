#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/state_machine.h"

namespace kmint
{
	namespace pigisland
	{
		class shark : public play::map_bound_actor
		{
		public:
			shark(kmint::map::map_graph& g);
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			scalar radius() const override { return 22.7; }
			bool perceptive() const override { return true; }
			scalar range_of_perception() const override { return 100.0f; }
			void act(delta_time dt) override;
			std::string name() const override { return "shark"; }

			states::state_machine<shark>& get_fsm() const { return *state_machine_; }
			map::map_node const* get_resting_place() const { return resting_place_; }

		private:
			play::image_drawable drawable_;
			map::map_graph* map_;
			map::map_node const* resting_place_;
			delta_time t_since_move_{};

			std::unique_ptr<states::state_machine<shark>> state_machine_;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
