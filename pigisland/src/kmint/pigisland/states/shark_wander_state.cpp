#include <kmint/pigisland/states/shark_wander_state.h>
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states {

			void shark_wander_state::on_enter(shark& shark)
			{
			}

			void shark_wander_state::execute(shark& shark)
			{
				if(shark.num_perceived_actors() != 0)
				{
					for (std::size_t i = 0; i < shark.num_perceived_actors(); ++i) {
						auto& a = shark.perceived_actor(i);
						if (a.name() == "pig")
						{
							shark.get_fsm().change_state("shark_hunt_state");
							return;
						}
						if(a.name() == "boat" && math::distance(a.location(), shark.location()) < 50.0f)
						{
							shark.get_fsm().change_state("shark_scared_state");
							return;
						}
					}
				}
				shark.node(random_adjacent_node(shark.node()));
			}

			void shark_wander_state::on_exit(shark& shark)
			{
			}

			std::string shark_wander_state::name()
			{
				return "shark_wander_state";
			}
		}
	}
}
