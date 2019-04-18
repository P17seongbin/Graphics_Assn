#include "RenderChannel.h"

/**
 * @brief 현재까지 Queue에 등록된 모든 요청을 RenderManger에게 전달하고 Queue를 비웁니다. 
 * @return 정상적으로 요청이 RM에게 전달 되었는지를 나타냅니다.
 */
bool RenderChannel::DrawAll()
{
	return false;
}
/**
 * @brief 단일 오브젝트 Render 요청을 등록합니다.
 * @param UnitRequest req : Render 요청에 필요한 정보를 담고 있는 Struct입니다. 
 * @return 정상적으로 Queue에 들어갔는지를 나타냅니다.
 */
bool RenderChannel::EnqueueRequest(UnitRequest req)
{
	return false;
}
/**
 * @param RenderManager* render : Render 요청을 전달할 RenderManager Object를 가리키는 포인터입니다.
 */
RenderChannel::RenderChannel(RenderManager * render)
{
}
