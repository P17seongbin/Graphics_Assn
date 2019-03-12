#include "System.h"
#include <algorithm>

struct CollideInfo
{
public:
	bool collided;
	AABB* self;
	AABB* other;
};

void GameManager::calCollide()
{
	//모든 오브젝트의 충돌 판정을 검사합니다.
	for (std::vector<std::pair<std::string, Object*>>::iterator lhs = ObjectList.begin(); lhs != ObjectList.end(); lhs++)
	{
		
		for (std::vector<std::pair<std::string, Object*>>::iterator rhs = ObjectList.begin(); rhs != ObjectList.end(); rhs++)
		{
			if (lhs->first != rhs->first)//두 오브젝트가 다른건가요?
			{
				//두 오브젝트가 가지고 있는 AABB를 모두 검사합니다. 그리고 하나라도 겹치면 겹치는 AABB들을 리턴합니다.
				struct CollideInfo isCollide = [](std::vector<AABB*> &lhs, std::vector<AABB*> &rhs) {
					struct CollideInfo info {false,NULL,NULL};
					for (std::vector<AABB*>::iterator lc = lhs.begin(); lc != lhs.end(); lc++)
					{
						for (std::vector<AABB*>::iterator rc = rhs.begin(); rc != rhs.end(); rc++)
						{
							if ((*lc)->IsCollide((*rc)))
							{
								info.collided = true;
								info.self = *lc;
								info.other = *rc;
								return info;
							}
						}
					}
					return info;
				}(lhs->second->collidebox, rhs->second->collidebox);
				if (isCollide.collided)
					lhs->second->onCollide(rhs->second,isCollide.self,isCollide.other);//ㅇㅇㅇ
			}
		}
	}
}

bool GameManager::removeObject(std::string tag)
{
	for (std::vector<std::pair<std::string, Object*>>::iterator it = ObjectList.begin(); it != ObjectList.end(); it++)
	{
		if (it->first == tag)
		{
			ObjectList.erase(it);
			l--;
			break;
		}
	}
}

void GameManager::addObject(std::string tag, Object* t) {
	ObjectList.push_back(std::make_pair(tag, t));
	l++;
}