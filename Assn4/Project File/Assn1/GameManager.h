#pragma once
#include "RenderChannel.h"
#include "IObject.h"
#define DTIME (1/10.0)
#define ROTATEPERSEC 0.6
using namespace std;
class GameManager
{
public:
	GameManager(GLFWwindow* win,RenderChannel* channel,State* state);
	void Terminate_Game();
	void Ball_Replace(IObject* Ball);
	vector<IObject*> getCollideList(string tag);
	//void Update();
	void Update(GLFWwindow* window);
	void AddObject(IObject* obj);
	IObject* FindObjectWithTag(string Tag);
	bool finished =false;
private:
	map<string, IObject*> ObjectQueue;//(tag,object)
	GLFWwindow* window;
	RenderChannel* Channel;
	State* StateMachine;
	int Score1, Score2;
	int winner;
	std::map<int, CameraMovement> control_map;
};