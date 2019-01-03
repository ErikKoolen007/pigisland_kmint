#include "kmint/pigisland/genetic_algorithm.h"
#include "kmint/pigisland/pig.hpp"
#include "kmint/random.hpp"

void kmint::pigisland::genetic_algorithm::create_generation_0() const
{
	for (int i = 0; i < 100; ++i)
	{
		stage_->build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f), 
			chromosome{random_scalar(-1.0f, 1.0f), random_scalar(-1.0f, 1.0f), 
				random_scalar(0.0f, 1.0f), random_scalar(0.0f, 1.0f), random_scalar(0.0f, 1.0f) });
	}
}

void kmint::pigisland::genetic_algorithm::new_generation()
{
	//Remove all left over pigs
	std::vector<play::actor*> remove_vector{};
	for (play::actor& a : *stage_)
	{
		if (a.name() == "pig")
			remove_vector.push_back(&a);
	}
	for (auto actor : remove_vector)
	{
		stage_->remove_actor(*actor);
	}
	remove_vector.clear();

	//Create 100 new ones
	for (int i = 0; i < 100; ++i)
	{
		stage_->build_actor<pigisland::pig>(math::vector2d(i * 10.0f, i * 6.0f), chromosome{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f });
	}
}
