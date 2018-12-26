#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		shark::shark(kmint::map::map_graph& g)
			: play::map_bound_actor{g, find_shark_resting_place(g)},
			  drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node()), a_star_{g}
		{
		}

		void shark::act(delta_time dt)
		{
			t_since_move_ += dt;
			if (to_seconds(t_since_move_) >= waiting_time(node()))
			{
				std::cout << steps_ << "\n";
				if (steps_ >= 100)
				{
					if(!path_to_rest_.empty())
					{
						for (size_t i = 0; i < this->node().num_edges(); i++)
						{
							const auto neighbor = this->node()[i].to().node_id();
							if (neighbor == path_to_rest_.front()->node_id())
							{
								this->node(node()[i].to());
								break;
							}
						}

						path_to_rest_.pop();
					}
					else
					{
						if (resting_place_->node_id() == node().node_id())
							steps_ = 1;
						else
							set_path_to_rest();
					}
				}
				else
				{
					node(random_adjacent_node(node()));
				}
				t_since_move_ = from_seconds(0);
				steps_++;
			}
		}

		void shark::set_path_to_rest()
		{
			path_to_rest_ = a_star_.a_star_search(node(), *resting_place_);
		}
	} // namespace pigisland
} // namespace kmint
