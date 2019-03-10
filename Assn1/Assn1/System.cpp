#include "System.h"
#include <algorithm>

void GameManager::calCollide()
{
	//모든 오브젝트의 충돌 판정을 검사합니다.
	for (std::map<std::string, Object*>::iterator lhs = ObjectList.begin();lhs != ObjectList.end(); lhs++)
	{
		for (std::map<std::string, Object*>::iterator rhs = ObjectList.begin(); rhs != ObjectList.end(); rhs++)
		{
			if (lhs->first != rhs->first)//두 오브젝트가 다른건가요?
			{
				if (lhs->second->collidebox->IsCollide(rhs->second->collidebox))//두 오브젝트가 충돌하나요?
				{
					lhs->second->onCollide(rhs->second);//ㅇㅇㅇ
				}
			}
		}
	}
}

bool GameManager::removeObject(std::string tag)
{
	if (ObjectList.find(tag) != ObjectList.end())
	{
		ObjectList.erase(tag);
		l--;
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