#include "System.h"
#include <algorithm>

void GameManager::calCollide()
{
	//��� ������Ʈ�� �浹 ������ �˻��մϴ�.
	for (std::map<std::string, Object*>::iterator lhs = ObjectList.begin();lhs != ObjectList.end(); lhs++)
	{
		for (std::map<std::string, Object*>::iterator rhs = ObjectList.begin(); rhs != ObjectList.end(); rhs++)
		{
			if (lhs->first != rhs->first)//�� ������Ʈ�� �ٸ��ǰ���?
			{
				if (lhs->second->collidebox->IsCollide(rhs->second->collidebox))//�� ������Ʈ�� �浹�ϳ���?
				{
					lhs->second->onCollide(rhs->second);//������
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