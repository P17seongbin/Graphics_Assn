#include "RenderChannel.h"

/**
 * @brief 현재까지 Queue에 등록된 모든 요청을 RenderManger에게 전달하고 Queue를 비웁니다. 
 * @return 정상적으로 요청이 RM에게 전달 되었는지를 나타냅니다.
 */
bool RenderChannel::DrawAll()
{
	int reqc = Draw_Queue.size();
	for (int i = 0; i < reqc; i++)
	{
		renderer->drawObject(Draw_Queue[i]);
	}
	Draw_Queue.clear();
	return true;
}
bool RenderChannel::EnqueueRequest(unsigned int ID, glm::vec3 pos, float dir)
{
	glm::mat4  I(1.0f);
	UnitRequest r;
	r.PolygonID = ID;
	r.PositionMatrix = glm::translate(I, pos);
	r.RotationMatrix = glm::rotate(I, dir, glm::vec3(0.0f, 1.0f, 0.0f));
	Draw_Queue.push_back(r);
	return true;
}
/**
 * @brief 단일 오브젝트 Render 요청을 등록합니다.
 * @param UnitRequest req : Render 요청에 필요한 정보를 담고 있는 Struct입니다. 
 * @return 정상적으로 Queue에 들어갔는지를 나타냅니다.
 */
bool RenderChannel::EnqueueRequest(UnitRequest req)
{
	Draw_Queue.push_back(req);
	return true;
}
/**
 * @param RenderManager* render : Render 요청을 전달할 RenderManager Object를 가리키는 포인터입니다.
 */
RenderChannel::RenderChannel(RenderManager * render)
{
	renderer = render;
}
