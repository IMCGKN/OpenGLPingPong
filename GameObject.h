#pragma once

#include <glad/glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

#include "Texture.h"
#include "Shader.h"

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class GameObject
{
private:
	unsigned int VAO, VBO;
	glm::vec2 position;
	glm::vec2 scale;

	Texture texture;
	const char* textLoc;

	unsigned int vertSize;

public:
	void Init(std::vector<Vertex> &vertices, glm::vec2 pos, glm::vec2 sca, const char* textureLoc)
	{
		if (textureLoc != "null")
		{
			texture.Init(textureLoc);
			textLoc = "not null";
		}
		vertSize = vertices.size();
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (7 * sizeof(float)), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (7 * sizeof(float)), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (7 * sizeof(float)), (void*)(5 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		position = pos;
		scale = sca;
	}

	void SetPos(const glm::vec2& pos)
	{
		position = pos;
	}

	void Draw(Shader& shader)
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 pos = glm::vec3(position.x, position.y, 0.0f);
		glm::vec3 sca = glm::vec3(scale.x, scale.y, 0.0f);
		model = glm::translate(model, pos);
		model = glm::scale(model, sca);

		shader.Use();
		shader.SetMat4("Model", model);
		if (textLoc == "not null")
		{
			texture.Use();
		}
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertSize);
		glBindVertexArray(0);
		if (textLoc == "not null")
		{
			texture.Unuse();
		}
		shader.Unuse();
	}
};
