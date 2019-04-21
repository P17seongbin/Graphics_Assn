#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "RenderManager.h"


/**
 * @brief: 각 Object가 자신을 그릴 것을 Request하는데 사용되는 Object입니다
 */
class RenderChannel
{
public:
	bool DrawAll();
	bool EnqueueRequest(unsigned int ID, glm::vec3 pos, float dir);
	bool EnqueueRequest(UnitRequest req);
	RenderChannel(RenderManager* render);
private:
	std::vector<UnitRequest> Draw_Queue;
	RenderManager* renderer;
};
