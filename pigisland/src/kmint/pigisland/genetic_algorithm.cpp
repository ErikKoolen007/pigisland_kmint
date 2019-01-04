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
	std::vector<chromosome> new_generation_chromosomes;

	//Pigs that got saved are automatically added to new generation because of elitism
	for(chromosome& ch : score_card_->get_saved_chromosomes())
	{
		new_generation_chromosomes.push_back(ch);
	}

	const int number_of_pigs_to_generate = 100 - score_card_->get_saved_chromosomes().size();

	//Get left over pigs
	std::vector<play::actor*> left_over_pigs{};
	for (play::actor& a : *stage_)
	{
		if (a.name() == "pig")
			left_over_pigs.push_back(&a);
	}

	//If the shark ate all the pigs -> restart
	if(left_over_pigs.empty() && score_card_->get_saved_chromosomes().empty())
	{
		create_generation_0(shark, boat);
		return;
	}

	bool mutate = false;
	if(random_int(0, 100) == 67)
	{
		mutate = true;
	}

	//Fitness = boat reached is good
	//Get a parent from the boat and pair it with a left over pig(left over pig survived too so should have something good(or luck))
	for(int i = 0; i < number_of_pigs_to_generate; ++i)
	{
		chromosome random_parent_a;
		chromosome random_parent_b;

		if (!score_card_->get_saved_chromosomes().empty())
			random_parent_a = score_card_->get_saved_chromosomes().at(random_int(0, score_card_->get_saved_chromosomes().size()));
		else
			random_parent_a = dynamic_cast<pigisland::pig*>(left_over_pigs.at(random_int(0, left_over_pigs.size())))->get_chromosome();

		if(!left_over_pigs.empty())
			random_parent_b = dynamic_cast<pigisland::pig*>(left_over_pigs.at(random_int(0, left_over_pigs.size())))->get_chromosome();
		else
			random_parent_b = score_card_->get_saved_chromosomes().at(random_int(0, score_card_->get_saved_chromosomes().size()));

		const int splice_point = random_int(1, 5);
		chromosome child{};

		for(int j = 0; j < splice_point; ++j)
		{
			child.get().at(j) = random_parent_a.get().at(j);
		}
		for(int k = splice_point; k < 5; ++k)
		{
			child.get().at(k) = random_parent_b.get().at(k);
		}

		if(mutate)
		{
			const int random_gene = random_int(0, 5);
			if (random_gene > 1)
				child.get().at(random_gene) = random_scalar(0.0f, 1.0f);
			else
				child.get().at(random_gene) = random_scalar(-1.0f, 1.0f);
		}

		new_generation_chromosomes.push_back(child);
	}

	//Remove old still living pigs
	for (auto actor : left_over_pigs)
	{
		stage_->remove_actor(*actor);
	}
	left_over_pigs.clear();

	//Build new generation
	for (int i = 0; i < 100; ++i)
	{
		stage_->build_actor<pigisland::pig>(random_location(), new_generation_chromosomes[i], shark, boat);
	}

	score_card_->reset_saved_chromosomes();
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
