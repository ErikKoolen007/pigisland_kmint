#pragma once
#include "kmint/play/stage.hpp"
#include "shark.hpp"
#include "boat.hpp"
#include "pig.hpp"

namespace kmint
{
	namespace pigisland
	{
		class genetic_algorithm
		{
			play::stage* stage_;

			static math::vector2d random_location();
		public:
			genetic_algorithm(play::stage& s) : stage_(&s)
			{
				
			}

			std::vector<kmint::pigisland::pig*>& create_generation_0(shark& shark, boat& boat);
			std::vector<kmint::pigisland::pig*> new_generation(shark& shark, boat& boat);
		private:
			std::vector< pig*> pigs = std::vector<pig*>();
		};
	}
}
