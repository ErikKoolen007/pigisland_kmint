#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/state_machine.h"
#include "score_card.h"

namespace kmint
{
	namespace pigisland
	{
		class boat : public play::map_bound_actor
		{
		public:
			boat(kmint::map::map_graph& g, score_card& score_card);
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			bool perceivable() const override { return true; }
			scalar radius() const override { return 16.0; }
			void act(delta_time dt) override;
			std::string name() const override { return "boat"; }

			states::state_machine<boat>& get_fsm() const { return *state_machine_; }

		private:
			play::image_drawable drawable_;
			//[[maybe_unused]] map::map_graph *map_;
			delta_time t_since_move_{};

			std::unique_ptr<states::state_machine<boat>> state_machine_;
			score_card* score_card_;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
