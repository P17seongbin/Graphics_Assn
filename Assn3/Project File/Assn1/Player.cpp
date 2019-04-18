#include "IObject.h"

class Player : IObject
{
public:
	glm::vec3 getPos() { return Pos; }
	glm::vec3 getSpeed() { return Speed; }
	glm::vec3 getAccel() { return Accel; }

	void setPos(glm::vec3 pos) { Pos = pos; }
	void setSpeed(glm::vec3 speed) { Speed = speed; }
	void setAccel(glm::vec3 accel) { Accel = accel; }

	void addPos(glm::vec3 dpos) { Pos += dpos; }
	void addSpeed(glm::vec3 dspeed) { Speed += dspeed; }
	void addAccel(glm::vec3 daccel) { Accel += daccel; }

	void setobjID(unsigned int i) { ID = i; }
	void setTag(std::string tag) { Tag = tag; }
	std::string getTag() { return Tag; }
private:
	glm::vec3 Pos;
	glm::vec3 Speed;
	glm::vec3 Accel;
	std::string Tag;
	unsigned int ID;
};
