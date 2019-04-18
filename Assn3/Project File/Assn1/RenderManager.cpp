#include "RenderManager.h"


/**
 * @brief ObjLoader에서 Load하고 VAO에 등록까지 마친 mesh의 Offset과 ID를 입력하는 함수
 * @param GLuint ID : Mesh의 ID, 각 오브젝트에 사전에 정의한 ID를 입력해야 합니다.
 * @param GLuint offset : Mesh의 Offset, 지금은 vertex offset만.
 * @return 정상적으로 등록 되었는가를 나타냅니다.
 */
bool RenderManager::enqueueMesh(GLuint ID, GLuint offset)
{
	return false;
}
/**
* @brief 생성자
* @param State* state: 현재 '상태'를 참고할 State 클래스를 가리키는 포인터.
*/
RenderManager::RenderManager(State * state)
{
}
/**
* @brief 단일 오브젝트를 Render하는 함수입니다.
* @param UnitRequest reqinfo: 오브젝트의 ID, 좌표, 회전 방향 정보를 담고 있습니다.
* @return 정상적으로 Render 되었는지를 나타냅니다.
*/
bool RenderManager::drawObject(UnitRequest reqinfo)
{
	return false;
}
