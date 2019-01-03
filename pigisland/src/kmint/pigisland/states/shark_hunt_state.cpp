#include <kmint/pigisland/states/shark_hunt_state.h>

namespace kmint
{
	namespace pigisland
	{
		namespace states {

			void shark_hunt_state::on_enter(shark& shark)
			{
				shark.set_color_tint(255, 0, 0);
				for (std::size_t i = 0; i < shark.num_perceived_actors(); ++i) {
					auto& a = shark.perceived_actor(i);
					if (a.name() == "pig")
					{
						map::map_node* node = &graph_[0];
						std::for_each(graph_.begin(), graph_.end(), [&](map::map_node &n)
						{
							if (math::distance(n.location(), a.location()) < math::distance(node->location(), a.location()))
							{
								node = &n;
							}
						});
						path_to_pig_ = a_star_.a_star_search(shark.node(), *node);
						return;
					}
				}
			}

			void shark_hunt_state::execute(shark& shark)
			{
				for (std::size_t i = 0; i < shark.num_perceived_actors(); ++i) {
					auto& a = shark.perceived_actor(i);
					if (a.name() == "boat" && math::distance(a.location(), shark.location()) < 50.0f)
					{
						shark.get_fsm().change_state("shark_scared_state");
						return;
					}
				}
				if (!path_to_pig_.empty())
				{
					shark.node(*path_to_pig_.front());

					path_to_pig_.pop();
				}
				else
				{
					shark.get_fsm().change_state("shark_wander_state");
				}
			}

			void shark_hunt_state::on_exit(shark& shark)
			{
				shark.remove_color_tint();
				a_star_.untag_nodes();
			}

			std::string shark_hunt_state::name()
			{
				return "shark_hunt_state";
			}
		}
	}
}