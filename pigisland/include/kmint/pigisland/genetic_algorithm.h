#pragma once
#include "kmint/play/stage.hpp"
#include "shark.hpp"
#include "boat.hpp"

namespace kmint
{
	namespace pigisland
	{
		class genetic_algorithm
		{
			play::stage* stage_;
			score_card* score_card_;

			static math::vector2d random_location();
		public:
			genetic_algorithm(play::stage& s, score_card& score_card) : stage_(&s), score_card_(&score_card)
			{
				
			}
			void create_generation_0(shark& shark, boat& boat) const;
			void new_generation(shark& shark, boat& boat);
		};
	}
}
