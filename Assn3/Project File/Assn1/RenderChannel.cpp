#include "RenderChannel.h"

/**
 * @brief ������� Queue�� ��ϵ� ��� ��û�� RenderManger���� �����ϰ� Queue�� ���ϴ�. 
 * @return ���������� ��û�� RM���� ���� �Ǿ������� ��Ÿ���ϴ�.
 */
bool RenderChannel::DrawAll()
{
	return false;
}
/**
 * @brief ���� ������Ʈ Render ��û�� ����մϴ�.
 * @param UnitRequest req : Render ��û�� �ʿ��� ������ ��� �ִ� Struct�Դϴ�. 
 * @return ���������� Queue�� �������� ��Ÿ���ϴ�.
 */
bool RenderChannel::EnqueueRequest(UnitRequest req)
{
	return false;
}
/**
 * @param RenderManager* render : Render ��û�� ������ RenderManager Object�� ����Ű�� �������Դϴ�.
 */
RenderChannel::RenderChannel(RenderManager * render)
{
}
