#include <Engine.h> 
#include <stdlib.h> 
#include <FileReader.h>
#include <cmath>
#include <Projection.hpp>
#include <View.hpp>
#include <RenderTarget.hpp>
#include <cfloat>
#include "Input.hpp"

#undef isnan
Engine::Engine() 
	: iQuad(0, 0, 512, 512),
	  quad1(150.f, 300.f, 256, 256),
	  quad2(900.f, 300.f, 256, 256),
	  bg(0, 0, 2000, 2000),
	  marioQ(-200.f, 300.f, 256, 256),
	  cube1(400, 400, -300, 128, 128, 128),
	  maxSceneDuration(600),
	  scenes(4),
	  sine(0)
{ 
    Scale = blackBarH = blackBarV = 0;
    x = y = 0;

	scene = 0;
	sceneCounter = 0;
} 
  
Engine::~Engine()
{
	
}

void Engine::Init(const float w, const float h)
{
	m_w = w;
	m_h = h;

	// Set up render target
	rTarget.init();
	rTarget.setCamera(&camera);


	// intro
	iTex.loadFromFile("text.tga");
	iQuad.bindTexture(&iTex);

	iQuad.setOrigin(256, 256);
	iQuad.setPosition(w / 2, h / 2);

	//scene 1
	texture.loadFromFile("doge.tga");
	texture2.loadFromFile("longcat.tga");
	
	quad1.bindTexture(&texture);
	quad2.bindTexture(&texture2);

	quad1.setOrigin(128, 128);
	quad2.setOrigin(128, 128);

	// scene 2
	bgTexture.loadFromFile("hypno.tga", true);
	bg.bindTexture(&bgTexture);
	bg.setOrigin(1000, 1000);
	bg.setPosition(w / 2, h / 2);

	marioT[0].loadFromFile("mario1.tga");
	marioT[1].loadFromFile("mario2.tga");
	marioT[2].loadFromFile("mario3.tga");
	marioT[3].loadFromFile("mario4.tga");
	marioT[4].loadFromFile("mario5.tga");

	marioQ.bindTexture(&marioT[0]);
	marioQ.setOrigin(128, 128);

	// scene 3
	cubeT.loadFromFile("cube.tga", true);

	cube1.bindTexture(&cubeT);
	cube1.setOrigin(64, 64, 64);


	// Hide the cursor
	#if defined(WINDOWS_FRAMEWORK)
		ShowCursor(FALSE);
	#endif
}
  
void Engine::Update() 
{ 
	sceneCounter++;
	sine += 0.01f;

	static bool camera1set = false, camera2set = false;


	if (scene == 0)
	{
		if (!camera1set)
		{
			camera.setCameraMode(eng::Camera::two_dimensional);
			camera.setProjectionMatrix(eng::Projection::getOrthoMatrix(m_w / 2, m_h / 2, m_w, m_h));
			camera1set = true;
		}

		iQuad.setColor((std::sin(-sine * 3) + 1) / 2, (std::sin(sine * 4) + 1) / 2, (std::sin(sine * 5) + 1) / 2, 1);
	}
	else if (scene == 1)
	{
		if (!camera1set)
		{
			camera.setCameraMode(eng::Camera::two_dimensional);
			camera.setProjectionMatrix(eng::Projection::getOrthoMatrix(m_w / 2, m_h / 2, m_w, m_h));
			camera1set = true;
		}

		if (sceneCounter < maxSceneDuration * 0.25)
		{
			quad1.move(1, 1);
			quad2.move(-1, 1);
		}
		else if (sceneCounter < maxSceneDuration * 0.5)
		{
			quad1.rotate(0, 0, 1);
			quad2.rotate(0, 0, -1);
		}
		else if (sceneCounter < maxSceneDuration * 0.75)
		{
			quad1.scale(1.01, 1.01);
			quad2.scale(1.01, 1.01);
		}
		else if (sceneCounter < maxSceneDuration)
		{
			quad1.move(-5, 2.5);
			quad2.move(5, -2.5);
			quad1.rotate(0, 0, -1);
			quad2.rotate(0, 0, 1);
			quad1.scale(0.99, 0.99);
			quad2.scale(0.99, 0.99);
		}

	}
	else if (scene == 2)
	{
		if (!camera1set)
		{
			camera.setCameraMode(eng::Camera::two_dimensional);
			camera.setProjectionMatrix(eng::Projection::getOrthoMatrix(m_w / 2, m_h / 2, m_w, m_h));
			camera1set = true;
		}

		bg.rotate(0, 0, 1);
		marioQ.move(3, 0);
		marioQ.setColor((std::sin(-sine * 3) + 1) / 2, (std::sin(sine * 4) + 1) / 2, (std::sin(sine * 5) + 1) / 2, 1);

		static int frame = 0;

		if (sceneCounter % 10 == 0)
		{
			frame++;
			if (frame > 4) frame = 0;

			marioQ.bindTexture(&marioT[frame]);
		}
	}
	else if (scene == 3)
	{
		// Camera
		if (!camera2set)
		{
			camera.setCameraMode(eng::Camera::three_dimensional);
			camera.setProjectionMatrix(eng::Projection::getPerspectiveMatrix(80, m_w / m_h, 1.f, FLT_MAX));
			camera2set = true;
		}
		
		camera.setViewMatrix(eng::View::get3DViewMatrix(gpm::Vector3F(400.f, 400.f, 0.f), gpm::Vector3F(400.f, 400.f, -1.f), gpm::Vector3F(0.f, 1.f, 0.f)));

		static gpm::Vector2F rotation;
		gpm::Vector2F tempRotation = eng::getLastMouseMove();
		tempRotation = -tempRotation;

		rotation += tempRotation;
		
		camera.rotate(rotation.x * 0.5f, rotation.y * 0.5f, 0);

		static gpm::Vector3F movement;
		gpm::Vector3F tempMovement;

		if (eng::keyPressed(eng::KeyBoard::W))
			tempMovement.z += -1;
		if (eng::keyPressed(eng::KeyBoard::S))
			tempMovement.z += 1;
		if (eng::keyPressed(eng::KeyBoard::A))
			tempMovement.x += 1;
		if (eng::keyPressed(eng::KeyBoard::D))
			tempMovement.x += -1;
		

		tempMovement = camera.m_viewTransform * tempMovement;
		tempMovement.normalize();

		tempMovement.scale(4);

		movement += tempMovement;

		camera.move(movement.x, movement.y, -movement.z);


		// Objects
		cube1.setColor((std::sin(-sine * 3) + 1) / 2, (std::sin(sine * 4) + 1) / 2, (std::sin(sine * 5) + 1) / 2, 1);
		if (eng::keyPressed(eng::KeyBoard::Up))
			cube1.rotate(3, 0, 0);
		if (eng::keyPressed(eng::KeyBoard::Down))
			cube1.rotate(-3, 0, 0);
		if (eng::keyPressed(eng::KeyBoard::Left))
			cube1.rotate(0, 3, 0);
		if (eng::keyPressed(eng::KeyBoard::Right))
			cube1.rotate(0, -3, 0);

		//cube1.rotate(4, 4, 0);

		//float scale = (std::sin(sine * 3.f) + 2.f) / 2.f;
		//cube1.setScale(scale, scale, scale);

        sceneCounter = 0;
	}


	if (sceneCounter > (scene == 0 ? maxSceneDuration - 420 : maxSceneDuration))
	{
		scene++;
		sceneCounter = 0;
	}
	if (scene >= scenes)
	{
		quad1.resetTransform();
		quad2.resetTransform();
		marioQ.resetTransform();

		quad1.setPosition(150.f, 300.f);
		quad2.setPosition(900.f, 300.f);
		quad1.setOrigin(128, 128);
		quad2.setOrigin(128, 128);
		marioQ.setPosition(-200.f, 300.f);
		marioQ.setOrigin(128, 128);
		cube1.setRotation(0, 0, 0);

		scene = 1;
		camera1set = false;
		camera2set = false;
	}

	if (eng::keyPressed(eng::KeyBoard::Escape))
		exit(EXIT_SUCCESS);
}

void Engine::Draw() 
{ 
	if (scene == 0)
		rTarget.clear((std::sin(-sine * 6) + 1) / 2, (std::sin(sine * 8) + 1) / 2, (std::sin(sine * 10) + 1) / 2, 1);
	else
		rTarget.clear(0.f, 0.f, 1.f, 1.f);


	if (scene == 0)
	{
		rTarget.draw(iQuad);
	}
	else if (scene == 1)
	{
		rTarget.draw(quad1);
		rTarget.draw(quad2);
	}
	else if (scene == 2)
	{
		rTarget.draw(bg);
		rTarget.draw(marioQ);
	}
	else if (scene == 3)
	{
		rTarget.draw(cube1);
	}
}

void Engine::fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height)
{
	//Calculate desired Aspect Ratio
	float dAR =  desiredWidth / desiredHeight;

	//Calculate real Aspect Ratio
	float rAR = width / height;
	float w, h;
	//Check Aspect Ratio's
	if (dAR == rAR)
	{
		//Same aspect, no letterboxing needed!
		Scale = width/desiredWidth;
	}
	else if (dAR < rAR)
	{
		//Horizontal letterboxing needed!
		Scale = height / desiredHeight;
		blackBarH = (width - Scale * desiredWidth) / 2;
	}
	else
	{
		//Vertical letterboxing needed!
		Scale = width / desiredWidth;
		blackBarV = (height - (Scale * desiredHeight)) / 2;
	}
	w = desiredWidth * Scale;
	h = desiredHeight * Scale;

	glViewport((int)blackBarH, (int)blackBarV, (int)w, (int)h); // Sets up the OpenGL viewport

	Init(w, h);
}