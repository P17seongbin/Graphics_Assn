#include "GameManager.h"
#include "Ball.h"
#include "AIPlayer.h"
#include "Player.h"


void GameManager::Terminate_Game()
{
}

vector<IObject*> GameManager::getCollideList(string tag)
{
	return vector<IObject*>();
}

void GameManager::Update(GLFWwindow* window)
{
	bool IsPressed = false;
	float x = 0;
	do {
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
	//AddObject(opponent);
	AddObject(ball);

	window = win;
	Channel = channel;
	StateMachine = state;
}