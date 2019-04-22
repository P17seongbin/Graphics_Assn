#include "State.h"

glm::mat4 State::getLookAt()
{
	switch (CameraID)
	{
	case 1://1인칭 시점
		break;
	case 2://캐릭터 통수 시점
		break;
	case 3://자유 이동
		break;
	}
	return glm::mat4();
}

/**
* @brief 카메라가 움직일 수 있을 때, 카메라의 좌표를 이동하는 명령을 수행합니다.
* @param CameraMovement dir 카메라 이동 방향을 나타냅니다.
* @return 명령이 전달 되었는지를 나타냅니다(카메라가 움직일 수 없어서 명령이 무시되는 경우에도 true가 리턴됩니다)
*/
bool State::CameraControl(CameraMovement dir)
{

}