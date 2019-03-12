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
	//��� ������Ʈ�� �浹 ������ �˻��մϴ�.
	for (std::vector<std::pair<std::string, Object*>>::iterator lhs = ObjectList.begin(); lhs != ObjectList.end(); lhs++)
	{
		
		for (std::vector<std::pair<std::string, Object*>>::iterator rhs = ObjectList.begin(); rhs != ObjectList.end(); rhs++)
		{
			if (lhs->first != rhs->first)//�� ������Ʈ�� �ٸ��ǰ���?
			{
				//�� ������Ʈ�� ������ �ִ� AABB�� ��� �˻��մϴ�. �׸��� �ϳ��� ��ġ�� ��ġ�� AABB���� �����մϴ�.
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
					lhs->second->onCollide(rhs->second,isCollide.self,isCollide.other);//������
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