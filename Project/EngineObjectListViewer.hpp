#ifdef _DEBUG
#ifndef EngineEditorObjectViewer_HPP
#define EngineEditorObjectViewer_HPP
#include <Windows.h>
#include <vector>
class GameObject;
class EngineObjectListViewer
{
public:
	~EngineObjectListViewer();
	void start();
	void remove(GameObject* t);
	void add(GameObject* entity);
	void set(GameObject* t);
	void getSelection();
	void update();


private:
	HWND hWnd;
	std::vector<GameObject*> order;


};


#endif
#endif