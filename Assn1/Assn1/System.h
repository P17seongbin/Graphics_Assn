#pragma once
#include "Object.h"
#include "Ball.h"
#include "Player.h"
#include <vector>
#include <string>
#define SPEED 0.1
#define TIMEPERFRAME 16//����:ms

class GameManager
{
public:
	GameManager();
	void addObject(std::string tag, Object* t) ;
	bool removeObject(std::string tag);
	void calCollide();
	void Step(int dt);
	void Draw();
	const std::vector<std::pair<std::string, Object*>> getObjectList() { return ObjectList; }
/*==========================================================*/
	void setKey(int x) { keyinput = x; }//key input
	int getKey() { return keyinput; }
private:
	std::vector<std::pair<std::string, Object*>> ObjectList;
	int l;
	int keyinput;

};