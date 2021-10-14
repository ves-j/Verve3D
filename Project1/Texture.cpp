#include "Texture.h"

Texture:: Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = texType;
	// TEXTURES STUFF (WIDTH, HEIGHT, COLOUR CHANNEL)
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	// loading the image from resouces folder and assigning the variable references -> image width, height and colour channels
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// generate texture object
	glGenTextures(1, &ID);

	// Assigns the texture to a Texture Unit
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	// GL_NEAREST or GL_LINEAR
	// GL_NEAREST: keeps the pixels as they are -> important if doing pixel art
	// GL_LINEAR: creates near pixels to produce smooth but blury images
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// repeat the texture if scale is larger ----> GL_MIRRORED_REPEAT or GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);


	// Assigns the image to the OpenGL Texture object
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// Generate MipMaps: create smaller resolutions of the same image
	glGenerateMipmap(GL_TEXTURE_2D);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(GL_TEXTURE_2D, 0);

}

// sending the texture to the uniform in shaders
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// getting uniform variable "tex0" from vertex shader
	GLuint texUni = glad_glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}