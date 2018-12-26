#pragma once
#include "kmint/map/map.hpp"
#include <queue>
#include <map>

class a_star
{
	kmint::map::map_graph& graph_;

	std::queue<const kmint::map::map_node*> reconstruct_path(
		const kmint::map::map_node* start, const kmint::map::map_node* goal,
		std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from) const;

	double heuristic(const kmint::map::map_node& a, const kmint::map::map_node& b) const;
public:
	a_star(kmint::map::map_graph& graph) : graph_(graph)
	{
	}

	std::queue<const kmint::map::map_node*> a_star_search(
		const kmint::map::map_node& start, const kmint::map::map_node& goal) const;
};
