#include <kmint/pigisland/states/shark_global_state.h>
#include "kmint/pigisland/states/shark_tired_state.h"

namespace kmint 
{
	namespace pigisland 
	{
		namespace states {

			void shark_global_state::execute(shark& shark)
			{
				if (steps_ >= 99) 
				{
					steps_ = 0;
					shark.get_fsm().change_state("shark_tired_state");
				}

				if(!shark.get_fsm().is_in_state("shark_tired_state"))
					steps_++;
			}

			std::string shark_global_state::name()
			{
				return "shark_global_state";
			}
		}
	}
}
