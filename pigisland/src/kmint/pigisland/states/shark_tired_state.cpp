#include <kmint/pigisland/states/shark_tired_state.h>
#include "kmint/pigisland/pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states {

			void shark_tired_state::on_enter(shark& shark)
			{
				shark.set_color_tint(0, 0, 0);
				path_to_rest_ = a_star_.a_star_search(shark.node(), *shark.get_resting_place());
			}

			void shark_tired_state::execute(shark& shark)
			{
				if (!path_to_rest_.empty())
				{
					shark.node(*path_to_rest_.front());

					path_to_rest_.pop();
				}
				else
				{
					shark.get_fsm().change_state("shark_wander_state");
				}
			}

			void shark_tired_state::on_exit(shark& shark)
			{
				shark.remove_color_tint();
				a_star_.untag_nodes();
				new_round_signal_->dispatch();
			}

			std::string shark_tired_state::name()
			{
				return "shark_tired_state";
			}
		}
	}
}
