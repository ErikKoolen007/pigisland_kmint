#include "kmint/pigisland/genetic_algorithm.h"
#include "kmint/pigisland/pig.hpp"
#include "kmint/random.hpp"

void kmint::pigisland::genetic_algorithm::create_generation_0(shark& shark, boat& boat) const
{
	for (int i = 0; i < 100; ++i)
	{
		stage_->build_actor<pigisland::pig>(random_location(), chromosome{}, shark, boat);
	}
}

void kmint::pigisland::genetic_algorithm::new_generation(shark& shark, boat& boat)
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
		stage_->build_actor<pigisland::pig>(random_location(), chromosome{}, shark, boat);
	}
}

kmint::math::vector2d kmint::pigisland::genetic_algorithm::random_location()
{
	const float random_y = random_scalar(32.0f, 736.0f);
	float random_x;

	//Rough boundaries so pigs won't spawn on the 4 grass islands
	if(random_y >= 32.0f && random_y <= 145.0f)
	{
		random_x = random_scalar(320.0f, 864.0f);
	}
	else if(random_y >= 512.0f && random_y <= 736.0f)
	{
		random_x = random_scalar(256.0f, 768.0f);
	}
	else
	{
		random_x = random_scalar(32.0f, 992.0f);
	}

	return math::vector2d{ random_x, random_y };
}
