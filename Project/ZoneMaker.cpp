#include "ZoneMaker.hpp"
void ZoneMap::addBackground(Tile &t) {
	backgrounds.push_back(t);
}
void ZoneMap::addGameObject(GameObject& go) {
	objects.push_back(go);
}
ZoneMap::ZoneMap() {
	name = "Test";
	ID = 1;
}