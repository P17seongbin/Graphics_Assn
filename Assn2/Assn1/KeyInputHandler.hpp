#pragma once
#include<map>

class KeyHandler
{
public:
	void AsciiKeyPress(unsigned char key, int x, int y)
	{
		AsciiKeyPressed[key] = true;
	}
	void AsciiKeyRelease(unsigned char key, int x, int y)
	{
		if(key != ' ')//Enter means start, so It should not be released
		AsciiKeyPressed[key] = false;
	}
	void SpecialKeyPress(int key, int x, int y)
	{
		SpecialKeyPressed[key] = true;
	}
	void SpecialKeyRelease(int key, int x, int y)
	{
		SpecialKeyPressed[key] = false;
	}
	bool isAsciiKeyPressed(unsigned char key) { return (AsciiKeyPressed.find(key) != AsciiKeyPressed.end()) && AsciiKeyPressed[key]; }
	bool isSpecialKeyPressed(int key) { return (SpecialKeyPressed.find(key) != SpecialKeyPressed.end()) && SpecialKeyPressed[key]; }
private:
	std::map<unsigned char, bool> AsciiKeyPressed;
	std::map<int, bool> SpecialKeyPressed;
};

