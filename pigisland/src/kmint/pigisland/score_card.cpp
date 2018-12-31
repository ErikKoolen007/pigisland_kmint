#include <kmint/pigisland/score_card.h>
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		void score_card::new_round()
		{
			current_round_++;
			reset_pigs_eaten();
			reset_pigs_saved();
		}

		void score_card::change_dock_chance(int dock_nr, int chance)
		{
			switch (dock_nr)
			{
			case 1:
				dock_1_chance_ = chance;
				break;
			case 2:
				dock_2_chance_ = chance;
				break;
			case 3:
				dock_3_chance_ = chance;
				break;
			default:
				break;
			}
		}

		void score_card::print_score() const
		{
			std::cout << "Round number: " << current_round_ << "\n" <<
				"Pigs eaten: " << pigs_eaten_ << "\n" <<
				"Pigs saved: " << pigs_saved_ << "\n";
			
		}
	}
}
