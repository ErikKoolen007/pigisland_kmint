#include <kmint/pigisland/score_card.h>
#include <iostream>
#include <algorithm>

namespace kmint
{
	namespace pigisland
	{
		int score_card::dock_chance(int dock) const
		{
			switch (dock)
			{
			case 1:
				return dock_1_chance_;
			case 2:
				return dock_2_chance_;
			case 3:
				return dock_3_chance_;
			default:
				return 0;
			}
		}

		void score_card::new_round()
		{
			current_round_++;
			reset_pigs_eaten();
			reset_pigs_saved();
		}

		void score_card::change_dock_chance(int dock_nr, int chance)
		{
			const int max_chance = 69;
			const int min_chance = 15;

			switch (dock_nr)
			{
			case 1:
				if(chance <= max_chance)
					dock_1_chance_ = std::max(min_chance, chance);
				break;
			case 2:
				if (chance <= max_chance)
					dock_2_chance_ = std::max(min_chance, chance);
				break;
			case 3:
				if (chance <= max_chance)
					dock_3_chance_ = std::max(min_chance, chance);
				break;
			default:
				break;
			}
		}

		void score_card::add_repair(int dock, int amount)
		{
			repair_history_[dock].push_back(amount);
		}

		void score_card::reset_repair_history()
		{
			for (auto& n : repair_history_)
			{
				n.second.clear();
			}
		}

		void score_card::print_score() const
		{
			std::cout << "Round number: " << current_round_ << "\n" <<
				"Pigs eaten: " << pigs_eaten_ << "\n" <<
				"Pigs saved: " << pigs_saved_ << "\n";
			
		}

		void score_card::print_dock_chances() const
		{
			std::cout << "Dock 1 chance: " << dock_1_chance_ << "\n" <<
				"Dock 2 chance: " << dock_2_chance_ << "\n" <<
				"Dock 3 chance: " << dock_3_chance_ << "\n";
		}
	}
}
