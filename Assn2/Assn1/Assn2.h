#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "System.h"
#include "Player.h"
#include "Ball.h"
#include "Cloud.h"
//물리엔진과 무관한, 순수히 Assn2을 위한 헤더파일이나 함수 등을 선언하는 헤더입니다.
#define MAX(x,y) (x > y ? x : y)
#define MIN(x,y) (x > y ? y : x)
#define WIN_HOR 100
#define WIN_VER 100
#define CAM_SIZE 20
#define BALL_SIZE 20
#define P2_TOLERANCE (rand() % 30)
#define GRAVITITIONAL_ACCEL -0.00098

using namespace std;
void ReShape(int w, int h);
void setOrtho2D(GameManager* GM, KeyHandler* keyhandler);

void StepCaller(int dt);
void DrawCaller();

void AsciiKeyPress(unsigned char key, int x, int y);
void AsciiKeyRelease(unsigned char key, int x, int y);
void SpecialKeyPress(int key, int x, int y);
void SpecialKeyRelease(int key, int x, int y);

void InitScene(void);
void RegisterCallback();
void Control2P();
void RegisterObject(GameManager* GM, KeyHandler* keyhandler);
void PrintHelpText();