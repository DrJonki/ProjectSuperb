#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>
#include <Camera.hpp>
#include <Texture.hpp>
#include <Quad.hpp>
#include <Cube.hpp>


class Engine
{
public:

	Engine();
	~Engine(); 
	void fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);
	void Init(const float w, const float h);
	void Update();
	void Draw();
	float Scale,blackBarH,blackBarV;
	int x,y;

private:

	int scene;
	int sceneCounter;
	const int maxSceneDuration;
	const int scenes;
	float m_w, m_h;

	float sine;
	
	eng::Camera camera;


	// Intro
	eng::Texture iTex;
	eng::Quad iQuad;

	// scene 1
	eng::Texture texture;
	eng::Texture texture2;
	eng::Quad quad1;
	eng::Quad quad2;

	// scene 2
	eng::Texture bgTexture;
	eng::Quad bg;
	eng::Texture marioT[5];
	eng::Quad marioQ;

	// scene 3
	eng::Texture cubeT;
	eng::Cube cube1;

};
#endif
