#include <kmint/pigisland/states/boat_global_state.h>
namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void boat_global_state::execute(boat& boat)
			{
				std::cout << paint_damage_ << "\n";
				if (paint_damage_ >= 100)
				{
					paint_damage_ = 0;
					boat.get_fsm().change_state("boat_repair_state");
				}

				if (!boat.get_fsm().is_in_state("boat_repair_state"))
					paint_damage_++;
			}

			std::string boat_global_state::name()
			{
				return "boat_global_state";
			}
		}
	}
}