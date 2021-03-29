#pragma once
#include "Texture.h"
#include "ShaderProgram.h"

class TextWriter
{
public:

	TextWriter(glm::vec2 geom[2], ShaderProgram& program, char letra);
	static TextWriter* CreateTextWriter(glm::vec2 geom[2], ShaderProgram& program);
	void init(char Letra, glm::vec2 geom[2]);
	void render();
	void usarLetra(char letra, glm::vec2 geom[2], float spaceAmongLetters);
	void free();

private:

	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	Texture tex;
	ShaderProgram& program;


};

