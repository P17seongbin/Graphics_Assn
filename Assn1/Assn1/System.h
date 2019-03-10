#pragma once
#include "AABB.h"
#include "Object.h"
#include <vector>
#include <string>
class GameManager
{
public:
	GameManager();
	void addObject(std::string tag, Object* t);
	bool removeObject(std::string tag);

	void calCollide();
	void Step(float dt);
	const std::vector<std::pair<std::string, Object*>> getObjectList() { return ObjectList; }
private:
	std::vector<std::pair<std::string, Object*>> ObjectList;
	int l;

};