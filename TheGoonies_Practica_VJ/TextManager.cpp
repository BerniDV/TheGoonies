#include "TextManager.h"

#include "Game.h"


TextManager* TextManager::CreateTextManager(ShaderProgram& program, const string& sentence, const glm::vec2& position = { 0.f, 0.f }, float LetterSize, float SpaceAmongLetters)
{
	TextManager* TxtManager = new TextManager(program, sentence, position, LetterSize, SpaceAmongLetters);
	return TxtManager;
}


TextManager::TextManager(ShaderProgram& program, const string& sentence, const glm::vec2& position, float LetterSize, float SpaceAmongLetters)
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(40.f, 40.f) };
	glm::vec2 Position = { (SCREEN_WIDTH - 200.f) * 0.5f, SCREEN_HEIGHT * 0.5f };

	buildArray(sentence, position, LetterSize, SpaceAmongLetters, program);

}

void TextManager::print()
{

	float diffLettersLocation = 0.f;

	for (TextWriter* writer : VWriter)
	{

		writer->render();
	}
}

void TextManager::buildArray(string sentence, const glm::vec2& Position, float LetterSize, float spaceAmongLetters, ShaderProgram& program)
{
	float diffLettersLocation = 0.f;
	VWriter.reserve(sentence.length());

	for (char c : sentence)
	{

		glm::vec2 geom[2] = { glm::vec2(Position.x + diffLettersLocation, Position.y), glm::vec2(Position.x + LetterSize + diffLettersLocation, Position.y + LetterSize) };
		TextWriter* writer = TextWriter::CreateTextWriter(geom, program);
		writer->usarLetra(c, geom, spaceAmongLetters);

		VWriter.emplace_back(writer);

		diffLettersLocation += LetterSize;
	}

}

