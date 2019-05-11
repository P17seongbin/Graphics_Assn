#include "State.h"
#include "Const.h"
State::State()
{
	CameraID = 3;
	CamPos = glm::vec3(0, 10, -0.5 * FIELD_LENGTH);

	//���� ��ġ �ʱ�ȭ
	setPointLightPos(0, 0, 0);
	setDirLightPos(0, 0, 0);
}

glm::mat4 State::getLookAt()
{
	switch (CameraID)
	{
	case 1://1��Ī ����
		return lookAt(
			glm::vec3(PlayerPos.x, 2, PlayerPos.z),
			glm::vec3(PlayerPos.x + sinf(PlayerDir), 2 ,PlayerPos.z + cosf(PlayerDir)),
			//glm::vec3(PlayerPos.x * sinf(PlayerDir), 2, PlayerPos.z * cosf(PlayerDir)),
			glm::vec3(0, 1, 0)
		);
	case 2://ĳ���� ��� ����
		glm::vec3 Pos = (glm::vec3(PlayerPos.x, 2.5, PlayerPos.z)+glm::vec3(-2 * sinf(PlayerDir), 0, -2 * cosf(PlayerDir)));
		return lookAt(
			Pos,
			Pos + glm::vec3(sinf(PlayerDir),0,cosf(PlayerDir)),
			//glm::vec3(PlayerPos.x * sinf(PlayerDir), 2, PlayerPos.z * cosf(PlayerDir)),
			glm::vec3(0, 1, 0)
		);
	case 3://���� �̵�
		return lookAt(
			CamPos, // ī�޶�� (4,3,3) �� �ִ�. ���� ��ǥ����
			glm::vec3(0, 0, 0), // �׸��� ī�޶� ������ ����
			glm::vec3(0, 1, 0)  // �Ӹ��� �����̴� (0,-1,0 ���� �غ���, ������ �����̴�)
		);
	}
}

/**
* @brief ī�޶� ������ �� ���� ��, ī�޶��� ��ǥ�� �̵��ϴ� ����� �����մϴ�.
* @param CameraMovement dir ī�޶� �̵� ������ ��Ÿ���ϴ�.
* @return ����� ���� �Ǿ������� ��Ÿ���ϴ�(ī�޶� ������ �� ��� ����� ���õǴ� ��쿡�� true�� ���ϵ˴ϴ�)
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
