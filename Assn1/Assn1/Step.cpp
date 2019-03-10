#include "System.h"
#include <algorithm>
GameManager::GameManager()
{
	//Init AABB's Collider Function Point vector
	l = 0;
}

void GameManager::Step(float dt)
{
	//1. 오브젝트 충돌 판정
	calCollide();
	//2. 오브젝트 움직임 판정

	//3. 죽은 오브젝트에 대한 데이터를 말소
	ObjectList.erase(std::remove_if(ObjectList.begin(), ObjectList.end(), [](std::pair<std::string, Object*> &v) { return v.second->isDestroy(); }));
	ObjectList.shrink_to_fit();
}
