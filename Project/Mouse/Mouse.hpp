#ifndef Mouse_HPP
#define Mouse_HPP

#include <SFML\Window\Mouse.hpp>
#include "../Vector.h"
#include <vector>


class GameObject;
class Mouse
{

public:
	Mouse();
	std::vector<GameObject*> list;
	//mousebox;
	Vector2 pos;
	Vector2 offset;
	void update();

	int deltaScrolls = 0;
	float scrollSpeed = 0.05;



	
private:



};

#endif //Mouse_HPP