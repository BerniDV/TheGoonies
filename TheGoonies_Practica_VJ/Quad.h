#pragma once
#include <GL/glew.h>
#include "ShaderProgram.h"

class Quad
{
public:
	// Quads can only be created inside an OpenGL context
	static Quad* createQuad(float x, float y, float width, float height, ShaderProgram& program);

	Quad(float x, float y, float width, float height, ShaderProgram& program);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;
};

