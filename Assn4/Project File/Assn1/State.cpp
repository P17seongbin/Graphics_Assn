#include "State.h"
#include "Const.h"
State::State()
{
	CameraID = 3;
	CamPos = glm::vec3(0, 10, -0.5 * FIELD_LENGTH);

	//광원 위치 초기화
	setPointLightPos(0, 0, 0);
	setDirLightPos(0, 0, 0);
}

glm::mat4 State::getLookAt()
{
	switch (CameraID)
	{
	case 1://1인칭 시점
		return lookAt(
			glm::vec3(PlayerPos.x, 2, PlayerPos.z),
			glm::vec3(PlayerPos.x + sinf(PlayerDir), 2 ,PlayerPos.z + cosf(PlayerDir)),
			//glm::vec3(PlayerPos.x * sinf(PlayerDir), 2, PlayerPos.z * cosf(PlayerDir)),
			glm::vec3(0, 1, 0)
		);
	case 2://캐릭터 통수 시점
		glm::vec3 Pos = (glm::vec3(PlayerPos.x, 2.5, PlayerPos.z)+glm::vec3(-2 * sinf(PlayerDir), 0, -2 * cosf(PlayerDir)));
		return lookAt(
			Pos,
			Pos + glm::vec3(sinf(PlayerDir),0,cosf(PlayerDir)),
			//glm::vec3(PlayerPos.x * sinf(PlayerDir), 2, PlayerPos.z * cosf(PlayerDir)),
			glm::vec3(0, 1, 0)
		);
	case 3://자유 이동
		return lookAt(
			CamPos, // 카메라는 (4,3,3) 에 있다. 월드 좌표에서
			glm::vec3(0, 0, 0), // 그리고 카메라가 원점을 본다
			glm::vec3(0, 1, 0)  // 머리가 위쪽이다 (0,-1,0 으로 해보면, 뒤집어 볼것이다)
		);
	}
}

/**
* @brief 카메라가 움직일 수 있을 때, 카메라의 좌표를 이동하는 명령을 수행합니다.
* @param CameraMovement dir 카메라 이동 방향을 나타냅니다.
* @return 명령이 전달 되었는지를 나타냅니다(카메라가 움직일 수 없어서 명령이 무시되는 경우에도 true가 리턴됩니다)
*/
bool State::CameraControl(CameraMovement dir)
{
	float dp = 0.1;
	switch (dir)
	{
	case CameraMovement::CAM_FRONT:
		CamPos.z += dp;

		break;
	case CameraMovement::CAM_BACK:
		CamPos.z -= dp;

		break;
	case CameraMovement::CAM_LEFT:
		CamPos.x += dp;

		break;
	case CameraMovement::CAM_RIGHT:
		CamPos.x -= dp;

		break;
	}
	//Regulate Camera boundary
	if (CamPos.z > 0) CamPos.z = 0;
	if (CamPos.z < (-0.5 * FIELD_LENGTH)) CamPos.z = (-0.5 * FIELD_LENGTH);
	if (CamPos.x > (0.5 * FIELD_WIDTH)) CamPos.x = (0.5 * FIELD_WIDTH);
	if (CamPos.x < (-0.5 * FIELD_WIDTH)) CamPos.x = (-0.5 * FIELD_WIDTH);

	return true;
}

void State::UpdatePlayerPos(glm::vec3 p)
{
	PlayerPos = p;
}
