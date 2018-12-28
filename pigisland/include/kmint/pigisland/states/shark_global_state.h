#pragma once
#include "state.h"
#include "../shark.hpp"

namespace kmint
{
	namespace pigisland 
	{
		namespace states 
		{
			class shark_global_state : public state<shark>
			{
				int steps_ = 0;

			public:
				shark_global_state() = default;

				void on_enter(shark& shark) override {}

				void execute(shark& shark) override;

				void on_exit(shark& shark) override {}

				std::string name() override;
			};
		}
	}
}
