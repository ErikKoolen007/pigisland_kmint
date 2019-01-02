#include <kmint/pigisland/states/shark_scared_state.h>
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states {

			void shark_scared_state::on_enter(shark& shark)
			{
				shark.set_color_tint(255, 255, 0);
				scared_steps_ = 10;
			}

			void shark_scared_state::execute(shark& shark)
			{
				if(scared_steps_ >= 1)
				{
					shark.node(random_adjacent_node(shark.node()));
					scared_steps_--;
				}
				else
				{
					shark.get_fsm().change_state("shark_wander_state");
				}
			}

			void shark_scared_state::on_exit(shark& shark)
			{
				shark.remove_color_tint();
			}

			std::string shark_scared_state::name()
			{
				return "shark_scared_state";
			}
		}
	}
}
