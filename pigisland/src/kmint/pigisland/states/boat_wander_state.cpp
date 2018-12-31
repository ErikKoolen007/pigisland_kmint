#include <kmint/pigisland/states/boat_wander_state.h>
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states {
			void boat_wander_state::on_enter(boat& boat)
			{
			}

			void boat_wander_state::execute(boat& boat)
			{
				boat.node(random_adjacent_node(boat.node()));
			}

			void boat_wander_state::on_exit(boat& boat)
			{
			}

			std::string boat_wander_state::name()
			{
				return "boat_wander_state";
			}
		}
	}
}
