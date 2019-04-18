#include "RenderManager.h"


/**
 * @brief ObjLoader���� Load�ϰ� VAO�� ��ϱ��� ��ģ mesh�� Offset�� ID�� �Է��ϴ� �Լ�
 * @param GLuint ID : Mesh�� ID, �� ������Ʈ�� ������ ������ ID�� �Է��ؾ� �մϴ�.
 * @param GLuint offset : Mesh�� Offset, ������ vertex offset��.
 * @return ���������� ��� �Ǿ��°��� ��Ÿ���ϴ�.
 */
bool RenderManager::enqueueMesh(GLuint ID, GLuint offset)
{
	return false;
}
/**
* @brief ������
* @param State* state: ���� '����'�� ������ State Ŭ������ ����Ű�� ������.
*/
RenderManager::RenderManager(State * state)
{
}
/**
* @brief ���� ������Ʈ�� Render�ϴ� �Լ��Դϴ�.
* @param UnitRequest reqinfo: ������Ʈ�� ID, ��ǥ, ȸ�� ���� ������ ��� �ֽ��ϴ�.
* @return ���������� Render �Ǿ������� ��Ÿ���ϴ�.
*/
bool RenderManager::drawObject(UnitRequest reqinfo)
{
	return false;
}
