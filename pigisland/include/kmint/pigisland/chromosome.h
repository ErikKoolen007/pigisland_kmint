#pragma once
#include <array>
#include "kmint/random.hpp"

namespace kmint
{
	namespace pigisland
	{
		class chromosome
		{
			std::array<float, 5> chromosome_array_{};
		public:
			chromosome()
			{
				chromosome_array_[0] = random_scalar(-1.0f, 1.0f);
				chromosome_array_[1] = random_scalar(-1.0f, 1.0f);
				chromosome_array_[2] = random_scalar(0.0f, 1.0f);
				chromosome_array_[3] = random_scalar(0.0f, 1.0f);
				chromosome_array_[4] = random_scalar(0.0f, 1.0f);
			}

			//[0] = shark_attraction
			//[1] = boat_attraction
			//[2] = cohesion
			//[3] = separation
			//[4] = alignment
			std::array<float, 5>& get() { return chromosome_array_; }
		};
	}
}
