#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "System.h"
#include "Player.h"
#include "Ball.h"
//���������� ������, ������ Assn2�� ���� ��������̳� �Լ� ���� �����ϴ� ����Դϴ�.
#define MAX(x,y) (x > y ? x : y)
#define MIN(x,y) (x > y ? y : x)
#define WIN_HOR 100
#define WIN_VER 100
#define CAM_SIZE 20
#define BALL_SIZE 20

using namespace std;
void ReShape(int w, int h);
void setOrtho2D(GameManager* GM, KeyHandler* keyhandler);
void StepCaller(int dt);
void AsciiKeyPress(unsigned char key, int x, int y);
void AsciiKeyRelease(unsigned char key, int x, int y);
void SpecialKeyPress(int key, int x, int y);
void SpecialKeyRelease(int key, int x, int y);
void DrawCaller(); 
void InitScene(void);
void RegisterCallback();
void Control2P();
void RegisterObject(GameManager* GM, KeyHandler* keyhandler);
void PrintHelpText();