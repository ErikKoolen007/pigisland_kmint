#include <kmint/pigisland/states/shark_tired_state.h>

namespace kmint
{
	namespace pigisland
	{
		namespace states {

			void shark_tired_state::on_enter(shark& shark)
			{
				path_to_rest_ = a_star_.a_star_search(shark.node(), *shark.get_resting_place());
			}

			void shark_tired_state::execute(shark& shark)
			{
				if (!path_to_rest_.empty())
				{
					for (size_t i = 0; i < shark.node().num_edges(); i++)
					{
						const auto neighbor = shark.node()[i].to().node_id();
						if (neighbor == path_to_rest_.front()->node_id())
						{
							shark.node(shark.node()[i].to());
							break;
						}
					}

					path_to_rest_.pop();
				}
				else
				{
					shark.get_fsm().change_state("shark_wander_state");
				}
			}

			void shark_tired_state::on_exit(shark& shark)
			{
				graph_.untag_all();
			}

			std::string shark_tired_state::name()
			{
				return "shark_tired_state";
			}
		}
	}
}