#include "GameManager.h"
#include "Ball.h"
#include "AIPlayer.h"
#include "Player.h"
#include<GL/glut.h>

void GameManager::Terminate_Game()
{
	//Restart
	Score1 = 0;
	Score2 = 0;
}

vector<IObject*> GameManager::getCollideList(string tag)
{
	vector<IObject*> CollideList;

	float collision_dist =2;
	IObject* Obj = FindObjectWithTag(tag);
	glm::vec3 a_pos=Obj->getPos();
	glm::vec3 b_pos;
	std::map<string, IObject*>::iterator it = ObjectQueue.begin();


	while (it != ObjectQueue.end())
	{
		b_pos = it->second->getPos();
		if (float(distance(a_pos, b_pos)) < collision_dist)
			CollideList.push_back(it->second);
		it++;
	}
	return CollideList;
}

float distance(glm::vec3 a,glm::vec3 b) {
	glm::vec3 diff = a - b;
	return sqrt(int(diff[0])^2+int(diff[1])^2+int(diff[2])^2);
}
void GameManager::Update(GLFWwindow* window)
{
	std::map<int, CameraMovement>::iterator cit;
	IObject* Player = FindObjectWithTag("player1");
	IObject* AIPlayer = FindObjectWithTag("player2");
	IObject* Ball = FindObjectWithTag("ball");
	glm::vec3 BallPos = Ball->getPos();
	bool IsPressed = false;
	float x = 0;

	do {


		BallPos = Ball->getPos();
		AIPlayer->setBallPos(BallPos[0]);//공의 좌표 aiplayer에게 넘겨줌

		if (getCollideList("ball").size() > 1)
		{
			//printf("collision");
			Ball->setSpeed(glm::vec3(-(Ball->getSpeed()[0]), 0, Ball->getSpeed()[2]));
			//printf("%d %d\n", Score1, Score2);
		}

		if (BallPos[2] > FIELD_LENGTH / 2)
		{
			Score2++;
			printf("score2: %d\n", Score2);
			Ball->setPos(glm::vec3(0, 0, 0));
		}
		else if (BallPos[2] < -FIELD_LENGTH / 2) 
		{
			Ball->setPos(glm::vec3(0, 0, 0)); 
			Score1++;
			printf("score1: %d\n", Score1);
		}
		std::map<string, IObject*>::iterator it = ObjectQueue.begin();
		//map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);
		while (it != ObjectQueue.end())
		{
			//printf("1");
			it->second->update(window,(1/30.0));
			it->second->DrawSelf();
			it++;
		}
		Channel->DrawAll();
		
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !IsPressed)
		{
			IsPressed = true;
			StateMachine->ToggleHiddenLineRemovalMode();
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
			IsPressed = false;

		//State Machine에 플레이어의 위치와 방향 정보를 업로드.
		StateMachine->UpdatePlayerPos(Player->getPos());
		StateMachine->UpdatePlayerDir(Player->getDir());

		//카메라 전환 키가 눌렸는지 확인
		for (int k = 1; k <= 3; k++)
		{
			if (glfwGetKey(window, GLFW_KEY_0 + k) == GLFW_PRESS)
				StateMachine->setCameraID(k);
		}
		//카메라 이동 키가 눌렸는지 확인
		for (cit = control_map.begin(); cit != control_map.end(); cit++)
		{
			if (glfwGetKey(window, cit->first) == GLFW_PRESS)
				StateMachine->CameraControl(cit->second);
		}

	} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}

void GameManager :: AddObject(IObject * obj) {

	string tag = obj->getTag();
	ObjectQueue.insert(std::pair<string, IObject*>(tag, obj));

}

IObject* GameManager::FindObjectWithTag(string Tag)
{
	if (ObjectQueue.find(Tag) != ObjectQueue.end())
		return (ObjectQueue[Tag]);
	else return nullptr;
}

GameManager::GameManager(GLFWwindow* win, RenderChannel* channel, State* state)
{
	Player* eevee = new Player(channel);
	AIPlayer* opponent = new AIPlayer(channel);
	Ball* ball = new Ball(channel);
	
	AddObject(eevee);
	AddObject(opponent);
	AddObject(ball);

	window = win;
	Channel = channel;
	StateMachine = state;

	control_map.insert(std::pair<int,CameraMovement>(GLFW_KEY_W, CameraMovement::CAM_FRONT));
	control_map.insert(std::pair<int, CameraMovement>(GLFW_KEY_A, CameraMovement::CAM_LEFT));
	control_map.insert(std::pair<int, CameraMovement>(GLFW_KEY_S, CameraMovement::CAM_BACK));
	control_map.insert(std::pair<int, CameraMovement>(GLFW_KEY_D, CameraMovement::CAM_RIGHT));

	Score1 = 0;
	Score2 = 0;
}