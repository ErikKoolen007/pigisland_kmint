#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include <queue>
#include "a_star.h"

namespace kmint
{
	namespace pigisland
	{
		class shark : public play::map_bound_actor
		{
		public:
			shark(kmint::map::map_graph& g);
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			scalar radius() const override { return 16.0; }
			void act(delta_time dt) override;

		private:
			play::image_drawable drawable_;
			map::map_graph* map_;
			map::map_node const* resting_place_;
			delta_time t_since_move_{};
			int steps_ = 0;
			std::queue<const kmint::map::map_node*> path_to_rest_;
			a_star a_star_;

			void set_path_to_rest();
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
