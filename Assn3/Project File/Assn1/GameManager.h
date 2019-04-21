#pragma once
#include "RenderChannel.h"
#include "IObject.h"
using namespace std;
class GameManager
{
public:
	GameManager(GLFWwindow* win,RenderChannel* channel);
	void Terminate_Game();
	vector<IObject*> getCollideList(string tag);
	//void Update();
	void Update(GLFWwindow* window);
	void AddObject(IObject* obj);
private:
	map<string, IObject*> ObjectQueue;//(tag,object)
	GLFWwindow* window;
};