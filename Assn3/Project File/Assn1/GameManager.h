#pragma once
#include "RenderChannel.h"
#include "IObject.h"
using namespace std;
class GameManager
{
public:
	GameManager(GLFWwindow* win,RenderChannel* channel,State* state);
	void Terminate_Game();
	vector<IObject*> getCollideList(string tag);
	//void Update();
	void Update(GLFWwindow* window);
	void AddObject(IObject* obj);
	IObject* FindObjectWithTag(string Tag);
private:
	map<string, IObject*> ObjectQueue;//(tag,object)
	GLFWwindow* window;
	RenderChannel* Channel;
	State* StateMachine;
	int Score1, Score2;
	std::map<int, CameraMovement> control_map;
};