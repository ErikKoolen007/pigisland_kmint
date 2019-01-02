#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/shark_wander_state.h"
#include "kmint/pigisland/states/shark_global_state.h"
#include "kmint/pigisland/states/shark_hunt_state.h"
#include "kmint/pigisland/states/shark_scared_state.h"
#include "kmint/pigisland/states/shark_tired_state.h"

namespace kmint
{
	namespace pigisland
	{
		shark::shark(kmint::map::map_graph& g, score_card& score_card, pigisland::signals::new_round_signal& new_round_signal)
			: play::map_bound_actor{g, find_shark_resting_place(g)},
			  drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node()), score_card_(&score_card)
		{
			state_machine_ = std::make_unique<states::state_machine<shark>>(*this);
			state_machine_->addState(std::make_unique<states::shark_global_state>());
			state_machine_->addState(std::make_unique<states::shark_hunt_state>(g));
			state_machine_->addState(std::make_unique<states::shark_scared_state>());
			state_machine_->addState(std::make_unique<states::shark_tired_state>(g, new_round_signal));
			state_machine_->addState(std::make_unique<states::shark_wander_state>());

			state_machine_->set_current_state("shark_wander_state");
			state_machine_->set_global_state("shark_global_state");
		}

		void shark::act(delta_time dt)
		{
			for (std::size_t i = 0; i < num_colliding_actors(); ++i)
			{
				actor& a = colliding_actor(i);

				if (a.name() == "pig" && (state_machine_->is_in_state("shark_wander_state") || state_machine_->is_in_state("shark_hunt_state")))
				{
					a.set_actor_removable();
					score_card_->pig_eaten();
					break;
				}
			}
			
			t_since_move_ += dt;
			if (to_seconds(t_since_move_) >= waiting_time(node()))
			{
				state_machine_->update();
				t_since_move_ = from_seconds(0);
			}
		}

		void shark::set_color_tint(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		{
			graphics::color color{ r, g, b };
			drawable_.set_tint(color);
		}
	} // namespace pigisland
} // namespace kmint
