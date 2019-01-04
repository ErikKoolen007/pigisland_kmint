#pragma once
#include <unordered_map>
#include "chromosome.h"

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

			std::unordered_map<int, std::vector<int>> repair_history_ = 
			{
				{1,{}},
				{2,{}},
				{3,{}}
			};

			std::vector<chromosome> saved_chromosomes_{};

		public:
			score_card() = default;

			int current_round() const { return current_round_; }
			int dock_chance(int dock) const;
			int pigs_eaten() const { return pigs_eaten_; }
			int pigs_saved() const { return pigs_saved_; }
			std::unordered_map<int, std::vector<int>>& repair_history() { return repair_history_; }
			std::vector<chromosome> get_saved_chromosomes() const { return saved_chromosomes_; }

			void new_round();
			void change_dock_chance(int dock_nr, int chance);
			void pig_eaten() { pigs_eaten_++; }
			void pig_saved() { pigs_saved_++; }
			void reset_pigs_eaten() { pigs_eaten_ = 0; }
			void reset_pigs_saved() { pigs_saved_ = 0; }
			void add_repair(int dock, int amount);
			void reset_repair_history();
			void save_chromosome(chromosome& chromosome) { saved_chromosomes_.push_back(chromosome); }
			void reset_saved_chromosomes() {saved_chromosomes_.clear(); }

			void print_score() const;
			void print_dock_chances() const;
		};
	}
}
