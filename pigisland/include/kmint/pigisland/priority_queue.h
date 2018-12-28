#pragma once
#include <queue>

namespace kmint 
{
	namespace pigisland 
	{
		template<typename T, typename priority_t>
		struct PriorityQueue {
			using PQElement = std::pair<priority_t, T>;
			std::priority_queue<PQElement, std::vector<PQElement>,
				std::greater<>> elements;

			bool empty() const {
				return elements.empty();
			}

			void put(T item, priority_t priority) {
				elements.emplace(priority, item);
			}

			T get() {
				T best_item = elements.top().second;
				elements.pop();
				return best_item;
			}
		};
	}
}