#pragma once
#include "kmint/play/stage.hpp"

namespace kmint
{
	namespace pigisland
	{
		class genetic_algorithm
		{
			play::stage* stage_;
		public:
			genetic_algorithm(play::stage& s) : stage_(&s)
			{
				
			}
			void create_generation_0() const;
			void new_generation();
		};
	}
}
