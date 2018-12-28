#pragma once
#include "kmint/map/map.hpp"
#include <queue>
#include <map>

namespace kmint 
{
	namespace pigisland 
	{
		class a_star
		{
			map::map_graph& graph_;

			std::queue<const map::map_node*> reconstruct_path(
				const map::map_node* start, const map::map_node* goal,
				std::map<const map::map_node*, const map::map_node*> came_from) const;

			double heuristic(const map::map_node& a, const map::map_node& b) const;
		public:
			a_star(map::map_graph& graph) : graph_(graph)
			{
			}

			std::queue<const map::map_node*> a_star_search(
				const map::map_node& start, const map::map_node& goal) const;
		};
	}
}
