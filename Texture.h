#pragma once

#include <glad/glad.h>

#include <stb_image.h>
#include <iostream>

class Texture
{
private:
	unsigned int ID;
	bool isUsing = false;

public:
	void Init(const char* TextureLoc)
	{
		glGenTextures(1, &ID);

		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		int w, h, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(TextureLoc, &w, &h, &nrChannels, 0);
		
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load Texture: " << TextureLoc << std::endl;
		}

		stbi_image_free(data);
	}

	void Use()
	{
		if (!isUsing)
		{
			glBindTexture(GL_TEXTURE_2D, ID);
			isUsing = true;
		}
	}

	void Unuse()
	{
		if (isUsing)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			isUsing = false;
		}
	}
};

