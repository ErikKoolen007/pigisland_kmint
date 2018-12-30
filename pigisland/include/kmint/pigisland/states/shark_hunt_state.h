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
			class shark_hunt_state : public state<shark>
			{
				std::queue<const kmint::map::map_node*> path_to_pig_;
				kmint::map::map_graph& graph_;
				a_star a_star_;

			public:
				shark_hunt_state(kmint::map::map_graph& g) : graph_(g), a_star_{g}
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
