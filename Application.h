#pragma once

#include "Shader.h"
#include "GameObject.h"
#include "Window.h"

#include <vector>

class Application
{
private:
	Window win;
	Shader mainShader;

	GameObject greenPaddle;
	glm::vec2 greenPaddlePos = glm::vec2(-0.85f, 0.0f);
	int greenScore = 0;

	GameObject redPaddle;
	glm::vec2 redPaddlePos = glm::vec2(0.85f, 0.0f);
	int redScore = 0;

	GameObject ball;
	glm::vec2 ballPos = glm::vec2(0.0f, 0.0f);
	float xVelocity = 0.5f;
	float yVelocity = 0.5f;

	const float xCollisionMargin = 0.056f;
	const float yCollisionMargin = 0.256f;

public:
	void Init();

	void MainLoop();

	bool CheckCollision(glm::vec2& ball, glm::vec2& player)
	{
		bool collisionX = ball.x + xCollisionMargin >= player.x && player.x + xCollisionMargin >= ball.x;
		bool collisionY = ball.y + xCollisionMargin >= player.y && player.y + yCollisionMargin >= ball.y;

		return collisionX && collisionY;
	}

private:
	void Destroy();
};
