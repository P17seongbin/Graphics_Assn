#include "RenderChannel.h"

/**
 * @brief ������� Queue�� ��ϵ� ��� ��û�� RenderManger���� �����ϰ� Queue�� ���ϴ�. 
 * @return ���������� ��û�� RM���� ���� �Ǿ������� ��Ÿ���ϴ�.
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
 * @brief ���� ������Ʈ Render ��û�� ����մϴ�.
 * @param UnitRequest req : Render ��û�� �ʿ��� ������ ��� �ִ� Struct�Դϴ�. 
 * @return ���������� Queue�� �������� ��Ÿ���ϴ�.
 */
bool RenderChannel::EnqueueRequest(UnitRequest req)
{
	Draw_Queue.push_back(req);
	return true;
}
/**
 * @param RenderManager* render : Render ��û�� ������ RenderManager Object�� ����Ű�� �������Դϴ�.
 */
RenderChannel::RenderChannel(RenderManager * render)
{
	renderer = render;
}
