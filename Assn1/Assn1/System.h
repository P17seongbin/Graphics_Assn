#pragma once
#include "AABB.h"
#include "Object.h"
#include <map>
#include <string>
class GameManager
{
public:
	GameManager();
	void addObject(std::string tag, Object* t) {
		if (ObjectList.find(tag) == ObjectList.end())
		{
			ObjectList[tag] = t;
			l++;
		}
	}
	bool removeObject(std::string tag);

	void calCollide();
	void Step(float dt);
private:
	std::map<std::string, Object*> ObjectList;
	int l;

};