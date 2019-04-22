#include "RenderChannel.h"

/**
 * @brief ������� Queue�� ��ϵ� ��� ��û�� RenderManger���� �����ϰ� Queue�� ���ϴ�. 
 * @return ���������� ��û�� RM���� ���� �Ǿ������� ��Ÿ���ϴ�.
 */
bool RenderChannel::DrawAll()
{
	renderer->drawObject(Draw_Queue);
	Draw_Queue.clear();


	return true;
}
bool RenderChannel::EnqueueRequest(unsigned int ID, glm::vec3 pos, float dir)
{
	glm::mat4  I(1.0f);
	UnitRequest r;
	r.PolygonID = ID;
	r.PositionMatrix = glm::translate(I, pos);
	r.RotationMatrix = glm::rotate(I, dir, glm::vec3(0,1,0));
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
RenderChannel::RenderChannel(RenderManager * render,GLFWwindow* Window)
{
	window = Window;
	renderer = render;
}
