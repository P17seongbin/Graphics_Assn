#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "RenderManager.h"


/**
 * @brief: �� Object�� �ڽ��� �׸� ���� Request�ϴµ� ���Ǵ� Object�Դϴ�
 */
class RenderChannel
{
public:
	bool DrawAll();
	bool EnqueueRequest(UnitRequest req);
	RenderChannel(RenderManager* render);
private:
	std::vector<UnitRequest> Draw_Queue;
	RenderManager* renderer;
};