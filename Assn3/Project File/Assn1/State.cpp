#include "State.h"

glm::mat4 State::getLookAt()
{
	switch (CameraID)
	{
	case 1://1��Ī ����
		break;
	case 2://ĳ���� ��� ����
		break;
	case 3://���� �̵�
		break;
	}
	return glm::mat4();
}

/**
* @brief ī�޶� ������ �� ���� ��, ī�޶��� ��ǥ�� �̵��ϴ� ����� �����մϴ�.
* @param CameraMovement dir ī�޶� �̵� ������ ��Ÿ���ϴ�.
* @return ����� ���� �Ǿ������� ��Ÿ���ϴ�(ī�޶� ������ �� ��� ����� ���õǴ� ��쿡�� true�� ���ϵ˴ϴ�)
*/
bool State::CameraControl(CameraMovement dir)
{

}