#include "System.h"

GameManager::GameManager()
{
	//Init AABB's Collider Function Point map
	l = 0;
}

void GameManager::calCollide()
{
	for (int i = 0; i < l; i++)
	{
		for (int j = i + 1; j < l; j++)
		{
			if (ObjectList[i].collidebox->IsCollide(ObjectList[j].collidebox))
			{
				ObjectList[i].onCollide(&ObjectList[j]);
			}
		}
	}
}

bool GameManager::removeObject(std::string tag)
{
	if (ObjectList.find(tag) != ObjectList.end())
	{
		ObjectList.erase(tag);
		return true;
	}
	return false;
}
void GameManager::addObject(std::string tag, Object* t) {
	if (ObjectList.find(tag) == ObjectList.end())
	{
		ObjectList[tag] = t;
		l++;
	}
}