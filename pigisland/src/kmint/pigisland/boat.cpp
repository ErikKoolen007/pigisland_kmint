#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/boat_global_state.h"
#include "kmint/pigisland/states/boat_wander_state.h"
#include "kmint/pigisland/states/boat_repair_state.h"

namespace kmint
{
	namespace pigisland
	{
		boat::boat(kmint::map::map_graph& g, score_card& score_card)
			: play::map_bound_actor{g, find_random_mooring_place(g)},
			  drawable_{*this, boat_image()}, score_card_(&score_card) /*, map_{&g}*/
		{
			state_machine_ = std::make_unique<states::state_machine<boat>>(*this);
			state_machine_->addState(std::make_unique<states::boat_global_state>());
			state_machine_->addState(std::make_unique<states::boat_wander_state>());
			state_machine_->addState(std::make_unique<states::boat_repair_state>(g, score_card));

			state_machine_->set_current_state("boat_wander_state");
			state_machine_->set_global_state("boat_global_state");
		}

		void boat::act(delta_time dt)
		{
			t_since_move_ += dt;
			if (to_seconds(t_since_move_) >= waiting_time(node()))
			{
				state_machine_->update();
				t_since_move_ = from_seconds(0);
			}
		}
	} // namespace pigisland
} // namespace kmint
