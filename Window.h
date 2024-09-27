#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* window;
	int width, height;
	float dt = 0.005f;
	float lastFrame = 0.0f;
public:
	void Init(int w, int h)
	{
		width = w;
		height = h;
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, "Ping Pong OpenGL", nullptr, nullptr);
		glfwMakeContextCurrent(window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glViewport(0, 0, width, height);
	}

	float getDeltaTime() const
	{
		return dt;
	}

	bool getKeyPressed(int key) const
	{
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	void Exit()
	{
		glfwSetWindowShouldClose(window, true);
	}

	int getWidth() const
	{
		return width;
	}

	int getHeight() const
	{
		return height;
	}

	bool isOpen() const
	{
		return glfwWindowShouldClose(window) == false;
	}

	void Update()
	{
		float newFrame = glfwGetTime();
		dt = newFrame - lastFrame;
		lastFrame = newFrame;

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void Destroy()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

