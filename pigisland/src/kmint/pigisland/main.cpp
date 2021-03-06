#include "kmint/main.hpp" // voor de main loop
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "kmint/pigisland/score_card.h"
#include "kmint/pigisland/signals/new_round_signal.h"
#include "kmint/pigisland/genetic_algorithm.h"

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
	pigisland::genetic_algorithm ga{s, score_card};
	pigisland::signals::new_round_signal new_round_signal;
	bool round_ended = false;

	auto map = pigisland::map();
	map.graph()[0].tagged(true);
	s.build_actor<play::background>(math::size(1024, 768),graphics::image{map.background_image()});
	s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
	pigisland::shark& shark = s.build_actor<pigisland::shark>(map.graph(), score_card, new_round_signal);
	pigisland::boat& boat = s.build_actor<pigisland::boat>(map.graph(), score_card);

	//Create first generation of pigs
	ga.create_generation_0(shark, boat);
	 
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
		// gebruik dt om te kijken hoeveel tijd versterken is
		// sinds de vorige keer dat deze lambda werd aangeroepen
		// loop controls is een object met eigenschappen die je kunt gebruiken om de
		// main-loop aan te sturen.
		if(round_ended)
		{
			round_ended = false;
			ga.new_generation(shark, boat);
		}

		for (ui::events::event& e : event_source)
		{
			// event heeft een methode handle_quit die controleert
			// of de gebruiker de applicatie wilt sluiten, en zo ja
			// de meegegeven functie (of lambda) aanroept om met het
			// bijbehorende quit_event
			//
			e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
			e.handle_key_up([&ctl](ui::events::key_event k)
			{
				switch (k.key)
				{
				case ui::events::key::p:
					if (ctl.pause)
						ctl.pause = false;
					else
						ctl.pause = true;
					break;
				case ui::events::key::r:
					if (ctl.render)
						ctl.render = false;
					else
						ctl.render = true;
					break;
				default:
					break;
				}
			});
		}
	});
}
