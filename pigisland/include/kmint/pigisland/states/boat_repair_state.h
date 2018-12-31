#pragma once
#include "state.h"
#include "../boat.hpp"
#include "kmint/pigisland/a_star.h"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class boat_repair_state : public state<boat>
			{
				std::queue<const kmint::map::map_node*> path_to_repair_;
				kmint::map::map_graph& graph_;
				a_star a_star_;
				score_card* score_card_;
				int chosen_dock = 0;

			public:
				boat_repair_state(kmint::map::map_graph& g, score_card& score_card) : graph_(g), a_star_{ g }, score_card_(&score_card)
				{
				}

				void on_enter(boat& boat) override;

				void execute(boat& boat) override;

				void on_exit(boat& boat) override;

				std::string name() override;
			};
		}
	}
}
