#pragma once
namespace kmint
{
	namespace pigisland
	{
		class score_card
		{
			int current_round_ = 1;
			int dock_1_chance_ = 33;
			int dock_2_chance_ = 33;
			int dock_3_chance_ = 33;
			int pigs_eaten_ = 0;
			int pigs_saved_ = 0;

		public:
			score_card() = default;

			int current_round() const { return current_round_; }
			int dock_1_chance() const { return dock_1_chance_; }
			int dock_2_chance() const { return dock_2_chance_; }
			int dock_3_chance() const { return dock_3_chance_; }
			int pigs_eaten() const { return pigs_eaten_; }
			int pigs_saved() const { return pigs_saved_; }

			void new_round();
			void change_dock_chance(int dock_nr, int chance);
			void pig_eaten() { pigs_eaten_++; }
			void pig_saved() { pigs_saved_++; }
			void reset_pigs_eaten() { pigs_eaten_ = 0; }
			void reset_pigs_saved() { pigs_saved_ = 0; }

			void print_score() const;
		};
	}
}
