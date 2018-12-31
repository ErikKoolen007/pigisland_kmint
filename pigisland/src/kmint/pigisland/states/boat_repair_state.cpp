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

				if(random_number <= score_card_->dock_chance(1))
				{
					chosen_dock = 1;
					path_to_repair_ = a_star_.a_star_search(boat.node(), find_node_of_kind(graph_, '1'));
				}
				else if(random_number > score_card_->dock_chance(1) 
					&& random_number <= score_card_->dock_chance(1) + score_card_->dock_chance(2))
				{
					chosen_dock = 2;
					path_to_repair_ = a_star_.a_star_search(boat.node(), find_node_of_kind(graph_, '2'));
				}
				else
				{
					chosen_dock = 3;
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
				switch (chosen_dock)
				{
				case 1:
					boat.repair_paint_damage(1, random_int(30, 51));
					break;
				case 2:
					boat.repair_paint_damage(2, random_int(20, 101));
					break;
				case 3:
					boat.repair_paint_damage(3, 50);
					break;
				default:
					break;
				}

				a_star_.untag_nodes();
				chosen_dock = 0;
			}

			std::string boat_repair_state::name()
			{
				return "boat_repair_state";
			}
		}
	}
}
