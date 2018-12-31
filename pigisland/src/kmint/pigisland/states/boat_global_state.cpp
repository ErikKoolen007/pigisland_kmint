#include <kmint/pigisland/states/boat_global_state.h>
namespace kmint
{
	namespace pigisland
	{
		namespace states
		{
			void boat_global_state::execute(boat& boat)
			{
				if (boat.paint_damage() >= 100 && !boat.get_fsm().is_in_state("boat_repair_state"))
				{
					boat.get_fsm().change_state("boat_repair_state");
				}

				if (!boat.get_fsm().is_in_state("boat_repair_state"))
					boat.add_paint_damage();
			}

			std::string boat_global_state::name()
			{
				return "boat_global_state";
			}
		}
	}
}