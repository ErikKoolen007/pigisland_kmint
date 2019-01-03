#pragma once
#include <array>

namespace kmint
{
	namespace pigisland
	{
		class chromosome
		{
			std::array<float, 5> chromosome_array_{};
		public:
			chromosome(float shark_attraction, float boat_attraction, float cohesion, float separation, float alignment)
			{
				chromosome_array_[0] = shark_attraction;
				chromosome_array_[1] = boat_attraction;
				chromosome_array_[2] = cohesion;
				chromosome_array_[3] = separation;
				chromosome_array_[4] = alignment;
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
