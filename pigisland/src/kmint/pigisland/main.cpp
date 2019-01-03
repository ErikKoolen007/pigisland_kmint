#include "kmint/main.hpp" // voor de main loop
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "kmint/pigisland/score_card.h"
#include "kmint/pigisland/signals/new_round_signal.h"
#include <windows.h>

using namespace kmint;

int main()
{
	// een app object is nodig om
	ui::app app{};

	//  maak een venster aan
	ui::window window{app.create_window({1024, 768}, "Kmint pig island Lennard Slabbekoorn en Erik Koolen")};

	// maak een podium aan
	play::stage s{};

	pigisland::score_card score_card{};
	pigisland::signals::new_round_signal new_round_signal;
	bool round_ended = false;

	auto map = pigisland::map();
	map.graph()[0].tagged(true);
	s.build_actor<play::background>(math::size(1024, 768),graphics::image{map.background_image()});
	s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
	for (int i = 0; i < 100; ++i)
	{
		s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f));
	}
	s.build_actor<pigisland::shark>(map.graph(), score_card, new_round_signal);
	s.build_actor<pigisland::boat>(map.graph(), score_card);

	// Maak een event_source aan (hieruit kun je alle events halen, zoals
	// toetsaanslagen)
	ui::events::event_source event_source{};

	//Add listeners
	new_round_signal.addListener([&]()
	{
		score_card.print_score();
		round_ended = true;
		score_card.new_round();
	});

	// main_loop stuurt alle actors aan.
	main_loop(s, window, [&](delta_time dt, loop_controls& ctl)
	{
		//Sleep(1000);
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.
		if(round_ended)
		{
			round_ended = false;
			//Remove all left over pigs
			std::vector<play::actor*> remove_vector{};
			for (play::actor& a : s)
			{
				if (a.name() == "pig")
					remove_vector.push_back(&a);
			}
			for (auto actor : remove_vector)
			{
				s.remove_actor(*actor);
			}
			remove_vector.clear();

			//Create 100 new ones
			for (int i = 0; i < 100; ++i)
			{
				s.build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f));
			}
		}
		for (ui::events::event& e : event_source)
		{
			// event heeft een methode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
		}
	});
}
