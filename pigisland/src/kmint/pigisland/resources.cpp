#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/properties/Wall2D.h"

namespace kmint {
namespace pigisland {
namespace {
constexpr const char *graph_description = R"graph(32 24 32
resources/pigisland.png
W 1 1
1 1 1
2 1 1
3 1 1
R 1 4
L 0 0
S 0 0
K 1 1

LLLLLLWW1WWWWRWWWWWWWWWWRWWWLLLL
LLLLLLLLLWWWWRWWWWWWWWWWRWWWLLLL
LLLLLLWWWWWWRRWWWWWWWWWWRRWWWWWL
WWWWWWWWWWWRRWWWWWWWWWWWWRRWWW2L
WWWWWWWWWWRRWWWWWWWWWWWWWRRRWWWW
WRRRRRRRRRRWWWWWWWWWWWWWWWRRWWWW
WWRRRRRRRRWWWWWWWWWWWWWWWRRRRWWW
WRRWWWRWWWWWWWWWWWWWWWWWWWWRRRRW
WWWWWWWWWWWWWLLLLLWWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLWWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLLWWWWWWWWWWWW
WWWWWWWWWWWWWLLLLLLLWWWWWWWWWWWW
WWWWWWWWWWWWWWLLLLLWWWWWWRRRRRWW
WWWWWWWWWWWWWWWWWWWWWWWWRRWRRRRW
WWWWWRRRWWWWWWWWWWWWWWWWRRRWWWWW
WWWWWWWWRWWWWWWWWWWWWWWWWRWWWWWW
WWLLLLLWWRWWWWWWWWWWWWWRRWWWL3WW
WWLLLLLWWRRWWWWWWWWWWWRRWWWWLWLL
WWLLLLLWWWRRWWWWWWWWWWRWWWLLLLLL
SSLLLLWWWWWRRRWWWWWWWWWWWLLLLLLL
SSLLLLWWWWWWWRRRRWWWWWWWWLLLLLLL
SSWWWWWWWWWWWWWWWWWWWWWWWLLLLLLL
KWWWWWWWWWWWWWWWWWWWWWWWWLLLLLLL
)graph";
}

map::map map() { return map::read_map(graph_description); }

std::vector<Wall2D> walls()
{
	std::vector<Wall2D> walls;

	math::vector2d A = math::vector2d(0, 0);
	math::vector2d B = math::vector2d(1024, 0);
	Wall2D edgeN = Wall2D(A, B);
	walls.push_back(edgeN);

	//edges
	// math::vector2d A = math::vector2d(0, 23);
	// math::vector2d B = math::vector2d(31, 23);
	// Wall2D edgeN = Wall2D(A, B);
	// walls.push_back(edgeN);
	//
	// A = math::vector2d(0, 0);
	// B = math::vector2d(0, 23);
	// Wall2D edgeW= Wall2D(A, B);
	// walls.push_back(edgeW);
	//
	// A = math::vector2d(31, 0);
	// B = math::vector2d(31, 23);
	// Wall2D edgeE = Wall2D(A, B);
	// walls.push_back(edgeE);
	//
	// A = math::vector2d(0, 0);
	// B = math::vector2d(31, 0);
	// Wall2D edgeS = Wall2D(A, B);
	// walls.push_back(edgeS);
	//
	// //island north west
	// A = math::vector2d(22, 23);
	// B = math::vector2d(22, 20);
	// Wall2D islandNW_E = Wall2D(A, B);
	// walls.push_back(islandNW_E);
	//
	// A = math::vector2d(0, 20);
	// B = math::vector2d(22, 20);
	// Wall2D islandNW_S = Wall2D(A, B);
	// walls.push_back(islandNW_S);
	//
	// //island north east
	// A = math::vector2d(27, 23);
	// B = math::vector2d(27, 19);
	// Wall2D islandNE_W = Wall2D(A, B);
	// walls.push_back(islandNE_W);
	//
	// A = math::vector2d(27, 19);
	// B = math::vector2d(31, 19);
	// Wall2D islandNE_S = Wall2D(A, B);
	// walls.push_back(islandNE_S);
	//
	// //island south west
	// A = math::vector2d(0, 6);
	// B = math::vector2d(6, 6);
	// Wall2D islandSW_N = Wall2D(A, B);
	// walls.push_back(islandSW_N);
	//
	// A = math::vector2d(6, 0);
	// B = math::vector2d(6, 6);
	// Wall2D islandSW_E = Wall2D(A, B);
	// walls.push_back(islandSW_E);
	//
	// //island south east
	// A = math::vector2d(25, 17);
	// B = math::vector2d(31, 17);
	// Wall2D islandSE_N = Wall2D(A, B);
	// walls.push_back(islandSE_N);
	//
	// A = math::vector2d(25, 17);
	// B = math::vector2d(25, 23);
	// Wall2D islandSE_W = Wall2D(A, B);
	// walls.push_back(islandSE_W);

	return walls;
}

graphics::image shark_image() { return graphics::image{"resources/shark.png"}; }
graphics::image pig_image() { return graphics::image{"resources/pig.png"}; }

graphics::image boat_image() { return graphics::image{"resources/boat.png"}; }

} // namespace pigisland

} // namespace kmint
