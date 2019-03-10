#include "System.h"
#include <algorithm>
GameManager::GameManager()
{
	//Init AABB's Collider Function Point vector
	l = 0;
}

void GameManager::Step(float dt)
{
	//1. ������Ʈ �浹 ����
	calCollide();
	//2. ������Ʈ ������ ����

	//3. ���� ������Ʈ�� ���� �����͸� ����
	ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(), [](std::pair<std::string, Object*> &v) { return v.second->isDestroy(); }));
	ObjectList.shrink_to_fit();
}
