#include "kmint/pigisland/a_star.h"
#include "kmint/pigisland/priority_queue.h"
#include <stack>

std::queue<const kmint::map::map_node*> a_star::a_star_search(const kmint::map::map_node& start,
                                                              const kmint::map::map_node& goal) const
{
	PriorityQueue<const kmint::map::map_node*, double> queue;
	std::map<const kmint::map::map_node*, const kmint::map::map_node*> came_from;
	std::map<const kmint::map::map_node*, double> cost_so_far;
	queue.put(&start, 0);
	graph_.untag_all();

	came_from[&start] = &start;
	cost_so_far[&start] = 0;

	while (!queue.empty())
	{
		const kmint::map::map_node& current = *queue.get();		

		if (current.node_id() == goal.node_id())
		{
			break;
		}

		for (size_t i = 0; i < current.num_edges(); i++)
		{
			const float weight = current[i].weight();
			const double new_cost = cost_so_far[&current] + weight;
			const kmint::map::map_node& neighbor = current[i].to();

			graph_[neighbor.node_id()].tag(kmint::graph::node_tag::visited);

			if (cost_so_far.find(&neighbor) == cost_so_far.end()
				|| new_cost < cost_so_far[&neighbor])
			{
				cost_so_far[&neighbor] = new_cost;
				const double priority = new_cost + heuristic(neighbor, goal);
				queue.put(&neighbor, priority);
				came_from[&neighbor] = &current;
			}
		}
	}

	return reconstruct_path(&start, &goal, came_from);
}

std::queue<const kmint::map::map_node*> a_star::reconstruct_path(const kmint::map::map_node* start,
                                                                 const kmint::map::map_node* goal,
                                                                 std::map<const kmint::map::map_node*, const kmint::map
                                                                          ::map_node*> came_from) const
{
	//Fill queue
	std::queue<const kmint::map::map_node*> path;
	const kmint::map::map_node* current = goal;
	while (current != start)
	{
		path.push(current);
		current = came_from[current];
	}

	//Reverse queue
	std::stack<const kmint::map::map_node*> stack;
	while (!path.empty())
	{
		graph_[path.front()->node_id()].tag(kmint::graph::node_tag::path);
		stack.push(path.front());
		path.pop();
	}
	while (!stack.empty())
	{
		path.push(stack.top());
		stack.pop();
	}

	return path;
}

double a_star::heuristic(const kmint::map::map_node& a, const kmint::map::map_node& b) const
{
	return std::abs(a.location().x() - b.location().x()) + std::abs(a.location().y() - b.location().y());
}
