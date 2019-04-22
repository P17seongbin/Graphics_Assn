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

void GameManager::update(GLFWwindow* window, float ball_x)
{
	std::map<string, IObject*>::iterator it = ObjectQueue.begin();
		//map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);
	if (it != ObjectQueue.end())
	{
		it->second->update(window,ball_x);
		it++;
	}
}

void GameManager :: AddObject(IObject * obj) {
	string tag = obj->getTag();
	ObjectQueue.insert(std::pair<string, IObject*>(tag, obj));
}

GameManager::GameManager(GLFWwindow* win, RenderChannel* channel)
{
	Ball* ball = new Ball(channel);
	Player* eevee = new Player(channel);
	AIPlayer* opponent = new AIPlayer(channel);

	AddObject(eevee);
	AddObject(opponent);
	AddObject(ball);

	window = win;
}