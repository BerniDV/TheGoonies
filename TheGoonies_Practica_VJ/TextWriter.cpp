#include "TextWriter.h"





TextWriter* TextWriter::CreateTextWriter(glm::vec2 geom[2], ShaderProgram& program)
{

	TextWriter* writer = new TextWriter(geom, program, 'A');
	return writer;
}


TextWriter::TextWriter(glm::vec2 geom[2], ShaderProgram& program, char letra)
	:program(program)
{


	init(letra, geom);

}


void TextWriter::usarLetra(char letra, glm::vec2 geo[2], float spaceAmongLetters)
{
	//Deja un espacio negro a la derecha de la letra para poder concatenar con espaciado con otra letra si es necessario
	float SpaceAmongLetters = spaceAmongLetters;

	//Calcula el offset en las X dentro de la textura, al restarle 65 a la letra tenemos un valor
	//assignado a la letra que empieza en A = 0, y al multiplicarlo por 0.11 coseguimos el valor exacto
	//en las X que representa esa letra en nuestra imagen, hacemos el modulo 9 para crear una cola ciclica
	//que permita reiniciar el proceso en el momento que nos salimos de los extremos de la imagen.
	float TexsCoordXOffset = ((letra - 65) % 9) * 0.11f;

	//Mismo procedimiento para el eje Y
	float TexsCoordYOffset = ((letra - 65) / 9) * 0.1045f;

	//tamano del cuadrado
	glm::vec2 geom[2] = { glm::vec2(0.f + geo[0].x, 0.f + geo[0].y), glm::vec2(0.f + geo[1].x, 0.f + geo[1].y) };
	//coord de la textura a pintar dentro de la imagen
	glm::vec2 texCoords[2] = { glm::vec2(0.028f + TexsCoordXOffset, 0.016f + TexsCoordYOffset), glm::vec2(0.082f + TexsCoordXOffset + SpaceAmongLetters, 0.073f + TexsCoordYOffset) };

	tex.loadFromFile("images/bitmapFont2.png", TEXTURE_PIXEL_FORMAT_RGBA);

	float vertices[24] = { geom[0].x, geom[0].y, texCoords[0].x, texCoords[0].y,
												geom[1].x, geom[0].y, texCoords[1].x, texCoords[0].y,
												geom[1].x, geom[1].y, texCoords[1].x, texCoords[1].y,
												geom[0].x, geom[0].y, texCoords[0].x, texCoords[0].y,
												geom[1].x, geom[1].y, texCoords[1].x, texCoords[1].y,
												geom[0].x, geom[1].y, texCoords[0].x, texCoords[1].y };

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));

}


void TextWriter::init(char Letra, glm::vec2 geom[2])
{

	usarLetra(Letra, geom, 0.003f);

}

void TextWriter::render()
{

	glEnable(GL_TEXTURE_2D);
	tex.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void TextWriter::free()
{

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

}
