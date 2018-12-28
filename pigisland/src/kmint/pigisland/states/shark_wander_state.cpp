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
