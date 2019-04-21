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
	std::map<string, IObject*>::iterator it = ObjectQueue.begin();
		//map<GLuint, UnitMesh>::iterator it = Meshqueue.find((GLuint)reqinfo.PolygonID);
	if (it != ObjectQueue.end())
	{
		it->second->update(window);
		it++;
	}
}

void GameManager :: AddObject(IObject * obj) {
	string tag = obj->getTag();
	ObjectQueue.insert(std::pair<string, IObject*>(tag, obj));
}

GameManager::GameManager( GLFWwindow* &win)
{
	Player* eevee = new Player();
	AIPlayer* opponent = new AIPlayer();
	Ball* ball = new Ball();

	AddObject(eevee);
	AddObject(opponent);
	AddObject(ball);

	window = win;
}