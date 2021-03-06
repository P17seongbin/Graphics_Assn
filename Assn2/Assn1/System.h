#pragma once
#include "Object.hpp"
#include "Ball.h"
#include "Player.h"
#include "Net.h"
#include <vector>
#include <string>

#define TIMEPERFRAME 15//����:ms

class GameManager
{
public:
	GameManager();
	void addObject(std::string tag, Object* t);
	bool removeObject(std::string tag);
	Object* findObjectwithTag(std::string tag);
	void calCollide();
	void Step(int dt);
	void Draw();
	const std::vector<std::pair<std::string, Object*>> getObjectList() { return ObjectList; }
	void Restart();
	bool finished = false;
private:
	std::vector<std::pair<std::string, Object*>> ObjectList;
	int score_1=0;
	int score_2 = 0;
	int l;

};



