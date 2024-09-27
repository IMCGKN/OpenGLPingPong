#include "Application.h"

void Application::Init()
{
	srand(time(NULL));
	win.Init(1280, 720);
	mainShader.Init("shaders/shader.vert", "shaders/shader.frag");

	std::vector<Vertex> vertices = {
		{ glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2( 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec2( 1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },

		{ glm::vec2( 1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec2(-1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec2(-1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
	};

	ball.Init(vertices, ballPos, glm::vec2(0.02f, 0.03f), "textures/ball.png");

	greenPaddle.Init(vertices, greenPaddlePos, glm::vec2(0.03f, 0.13f), "textures/paddle_green.png");
	redPaddle.Init(vertices, redPaddlePos, glm::vec2(0.03f, 0.13f), "textures/paddle_red.png");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	int random = rand() % 4 + 1;
	srand(time(NULL));
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (random == 1)
	{
		xVelocity = -r;
	}
	else if (random == 2)
	{
		xVelocity = g;
	}
	else if (random == 3)
	{
		yVelocity = -g;
	}
	else if (random == 4)
	{
		yVelocity = r;
	}
}

void Application::MainLoop()
{
	while (win.isOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.12f, 0.12f, 0.54f, 1.0f);

		greenPaddle.Draw(mainShader);
		redPaddle.Draw(mainShader);
		ball.Draw(mainShader);

		win.Update();

		if (win.getKeyPressed(GLFW_KEY_ESCAPE))
			win.Exit();
		if (win.getKeyPressed(GLFW_KEY_W) && greenPaddlePos.y <= 0.87f)
		{
			greenPaddlePos.y += 1.0f * win.getDeltaTime();
			greenPaddle.SetPos(greenPaddlePos);
		}
		if (win.getKeyPressed(GLFW_KEY_S) && greenPaddlePos.y >= -0.87f)
		{
			greenPaddlePos.y -= 1.0f * win.getDeltaTime();
			greenPaddle.SetPos(greenPaddlePos);
		}
		if (win.getKeyPressed(GLFW_KEY_UP) && redPaddlePos.y <= 0.87f)
		{
			redPaddlePos.y += 1.0f * win.getDeltaTime();
			redPaddle.SetPos(redPaddlePos);
		}
		if (win.getKeyPressed(GLFW_KEY_DOWN) && redPaddlePos.y >= -0.87f)
		{
			redPaddlePos.y -= 1.0f * win.getDeltaTime();
			redPaddle.SetPos(redPaddlePos);
		}

		ball.SetPos(ballPos);

		ballPos.x -= xVelocity * win.getDeltaTime();
		ballPos.y -= yVelocity * win.getDeltaTime();

		if (ballPos.x <= -1.0f)
		{
			xVelocity *= -1.0f;
			redScore++;
			ballPos.x = 0.0f;
			ballPos.y = 0.0f;
		}
		if (ballPos.y - xCollisionMargin <= -1.0f)
		{
			yVelocity *= -1.0f;
		}
		if (ballPos.x >= 1.0f)
		{
			ballPos.x = 0.0f;
			ballPos.y = 0.0f;
			xVelocity *= -1.0f;
			greenScore++;
		}
		if (ballPos.y + xCollisionMargin >= 1.0f)
		{
			yVelocity *= -1.0f;
		}

		if (CheckCollision(ballPos, greenPaddlePos))
		{
			yVelocity *= 1.0f;
			xVelocity *= -1.0f;
		}
		if (CheckCollision(redPaddlePos, ballPos))
		{
			yVelocity *= 1.0f;
			xVelocity *= -1.0f;
		}

		std::cout << "Green: " << greenScore << "\t Red: " << redScore << '\n';
	}

	Destroy();
}

void Application::Destroy()
{
	win.Destroy();
}
