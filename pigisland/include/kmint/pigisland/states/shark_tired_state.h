#pragma once
#include "state.h"
#include "../shark.hpp"
#include "kmint/pigisland/a_star.h"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class shark_tired_state : public state<shark>
			{
				std::queue<const kmint::map::map_node*> path_to_rest_;
				a_star a_star_;
				pigisland::signals::new_round_signal* new_round_signal_;

			public:
				shark_tired_state(kmint::map::map_graph& g, pigisland::signals::new_round_signal& new_round_signal) :
					a_star_{g}, new_round_signal_(&new_round_signal)
				{
				}

				void on_enter(shark& shark) override;

				void execute(shark& shark) override;

				void on_exit(shark& shark) override;

				std::string name() override;
			};
		}
	}
}
