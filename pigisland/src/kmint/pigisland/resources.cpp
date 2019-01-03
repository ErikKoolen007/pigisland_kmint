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

	//screen edges
	math::vector2d A = math::vector2d(0, 513);
	math::vector2d B = math::vector2d(0, 255);
	Wall2D edgeW = Wall2D(A, B);
	walls.push_back(edgeW);
	
	A = math::vector2d(1024, 255);
	B = math::vector2d(1024, 513);
	Wall2D edgeE = Wall2D(A, B);
	walls.push_back(edgeE);
	
	A = math::vector2d(718, 768);
	B = math::vector2d(306, 768);
	Wall2D edgeN = Wall2D(A, B);
	walls.push_back(edgeN);
	
	A = math::vector2d(306, 0);
	B = math::vector2d(718, 0);
	Wall2D edgeS = Wall2D(A, B);
	walls.push_back(edgeS);

	//Island North-West
	A = math::vector2d(305, 514);
	B = math::vector2d(0, 514);
	Wall2D nwS = Wall2D(A, B);
	walls.push_back(nwS);

	A = math::vector2d(305, 768);
	B = math::vector2d(305, 514);
	Wall2D nwE = Wall2D(A, B);
	walls.push_back(nwE);

	//Island North-East
	A = math::vector2d(1024, 514);
	B = math::vector2d(719, 514);
	Wall2D neS = Wall2D(A, B);
	walls.push_back(neS);

	A = math::vector2d(719, 514);
	B = math::vector2d(719, 768);
	Wall2D neW = Wall2D(A, B);
	walls.push_back(neW);

	//Island South-East
	A = math::vector2d(719, 254);
	B = math::vector2d(1024, 254);
	Wall2D seN = Wall2D(A, B);
	walls.push_back(seN);

	A = math::vector2d(719, 0);
	B = math::vector2d(719, 254);
	Wall2D seW = Wall2D(A, B);
	walls.push_back(seW);

	//Island South-west
	A = math::vector2d(0, 254);
	B = math::vector2d(305, 254);
	Wall2D swN = Wall2D(A, B);
	walls.push_back(swN);

	A = math::vector2d(305, 254);
	B = math::vector2d(305, 0);
	Wall2D swE = Wall2D(A, B);
	walls.push_back(swE);

	return walls;
}

graphics::image shark_image() { return graphics::image{"resources/shark.png"}; }
graphics::image pig_image() { return graphics::image{"resources/pig.png"}; }

graphics::image boat_image() { return graphics::image{"resources/boat.png"}; }

} // namespace pigisland

} // namespace kmint
