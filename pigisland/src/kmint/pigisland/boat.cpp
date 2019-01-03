#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/boat_global_state.h"
#include "kmint/pigisland/states/boat_wander_state.h"
#include "kmint/pigisland/states/boat_repair_state.h"
#include "kmint/pigisland/pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		boat::boat(kmint::map::map_graph& g, score_card& score_card)
			: play::map_bound_actor{g, find_random_mooring_place(g)},
			  drawable_{*this, boat_image()}, score_card_(&score_card) /*, map_{&g}*/
		{
			state_machine_ = std::make_unique<states::state_machine<boat>>(*this);
			state_machine_->addState(std::make_unique<states::boat_global_state>());
			state_machine_->addState(std::make_unique<states::boat_wander_state>());
			state_machine_->addState(std::make_unique<states::boat_repair_state>(g, score_card));

			state_machine_->set_current_state("boat_wander_state");
			state_machine_->set_global_state("boat_global_state");
		}

		void boat::act(delta_time dt)
		{
			for (std::size_t i = 0; i < num_colliding_actors(); ++i)
			{
				actor& a = colliding_actor(i);

				if (a.name() == "pig" && state_machine_->is_in_state("boat_wander_state"))
				{
					a.set_actor_removable();
					score_card_->pig_saved();
					auto* pig = dynamic_cast<pigisland::pig*>(&a);
					std::cout << pig->get_chromosome().get()[0] << "\n";
 					break;
				}
			}

			t_since_move_ += dt;
			if (to_seconds(t_since_move_) >= waiting_time(node()))
			{
				state_machine_->update();
				t_since_move_ = from_seconds(0);
			}
		}

		void boat::repair_paint_damage(int dock, int amount)
		{
			times_repaired_++;

			paint_damage_ -= amount;
			score_card_->add_repair(dock, amount);
			std::cout << "Repair nr: " << times_repaired_ << " -> repaired " << amount << " at dock " << dock << ", current damage is: " << paint_damage() << "\n";

			if(times_repaired_ >= 10)
			{
				times_repaired_ = 0;
				evaluate_dock_effectiveness();
			}
		}

		//Best dock will get higher chance, worst dock will be lowered by same amount
		void boat::evaluate_dock_effectiveness() const
		{
			const int effectiveness_percentage = 3;
			int max_repair_amount = 0;
			int min_repair_amount = 100;
			int best_dock = 0;
			int worst_dock = 0;

			for(auto& n : score_card_->repair_history())
			{
				if (!n.second.empty()) {
					const int repair_amount_max = *std::max_element(n.second.begin(), n.second.end());
					const int repair_amount_min = *std::min_element(n.second.begin(), n.second.end());

					if (repair_amount_max > max_repair_amount)
					{
						max_repair_amount = repair_amount_max;
						best_dock = n.first;
					}

					if (repair_amount_min < min_repair_amount)
					{
						min_repair_amount = repair_amount_min;
						worst_dock = n.first;
					}
				}
			}

			const int previous_dock_1_chance = score_card_->dock_chance(1);
			const int previous_dock_2_chance = score_card_->dock_chance(2);
			const int previous_dock_3_chance = score_card_->dock_chance(3);

			score_card_->change_dock_chance(best_dock, score_card_->dock_chance(best_dock) + effectiveness_percentage);
			score_card_->change_dock_chance(worst_dock, score_card_->dock_chance(worst_dock) - effectiveness_percentage);

			if (score_card_->dock_chance(1) + score_card_->dock_chance(2) + score_card_->dock_chance(3) != 99)
			{
				score_card_->change_dock_chance(1, previous_dock_1_chance);
				score_card_->change_dock_chance(2, previous_dock_2_chance);
				score_card_->change_dock_chance(3, previous_dock_3_chance);
			}

			score_card_->reset_repair_history();
			score_card_->print_dock_chances();
		}

		void boat::set_color_tint(std::uint8_t r, std::uint8_t g, std::uint8_t b)
		{
			graphics::color color{ r, g, b };
			drawable_.set_tint(color);
		}
	} // namespace pigisland
} // namespace kmint
