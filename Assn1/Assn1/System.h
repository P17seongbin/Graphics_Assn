#pragma once
#include "AABB.h"
#include "Object.h"
#include <map>
#include <string>
class GameManager
{
public:
	GameManager();
	void addObject(std::string tag, Object* t);
	bool removeObject(std::string tag);

	void calCollide();
	void Step(float dt);
	const std::map<std::string, Object*> getObjectList() { return ObjectList; }
private:
	std::map<std::string, Object*> ObjectList;
	int l;

};