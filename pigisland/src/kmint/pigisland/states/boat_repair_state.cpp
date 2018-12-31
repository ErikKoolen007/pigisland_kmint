#include <kmint/pigisland/states/boat_repair_state.h>
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void boat_repair_state::on_enter(boat& boat)
			{
				const int random_number = random_int(1, 100);

				if(random_number <= score_card_->dock_1_chance())
				{
					path_to_repair_ = a_star_.a_star_search(boat.node(), find_node_of_kind(graph_, '1'));
				}
				else if(random_number > score_card_->dock_1_chance() 
					&& random_number <= score_card_->dock_1_chance() + score_card_->dock_2_chance())
				{
					path_to_repair_ = a_star_.a_star_search(boat.node(), find_node_of_kind(graph_, '2'));
				}
				else
				{
					path_to_repair_ = a_star_.a_star_search(boat.node(), find_node_of_kind(graph_, '3'));
				}
			}

			void boat_repair_state::execute(boat& boat)
			{
				if (!path_to_repair_.empty())
				{
					boat.node(*path_to_repair_.front());

					path_to_repair_.pop();
				}
				else
				{
					boat.get_fsm().change_state("boat_wander_state");
				}
			}

			void boat_repair_state::on_exit(boat& boat)
			{
				//TODO repair the boat
				//TODO evaluate effectiveness
			}

			std::string boat_repair_state::name()
			{
				return "boat_repair_state";
			}
		}
	}
}
