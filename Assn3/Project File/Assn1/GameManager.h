#pragma once
#include "RenderChannel.h"
#include "IObject.h"

using namespace std;
class GameManager
{
public:
	void Terminate_Game();
	vector<IObject*> getCollideList(string tag);
	void Update();
private:
	map<string, IObject*> ObjectQueue;//(tag,object)
};
