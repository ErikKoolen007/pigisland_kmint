#pragma once
#include "state.h"
#include "../boat.hpp"

namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			class boat_global_state : public state<boat>
			{
			public:
				boat_global_state() = default;

				void on_enter(boat& boat) override{}

				void execute(boat& boat) override;

				void on_exit(boat& boat) override{}

				std::string name() override;
			};
		}
	}
}
