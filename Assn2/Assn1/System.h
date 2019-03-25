#pragma once
#include "Object.h"
#include "Ball.h"
#include "Player.h"
#include "Net.h"
#include <vector>
#include <string>

#define TIMEPERFRAME 5//¥‹¿ß:ms

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

private:
	std::vector<std::pair<std::string, Object*>> ObjectList;
	int score_1=0;
	int score_2 = 0;
	int l;

};

