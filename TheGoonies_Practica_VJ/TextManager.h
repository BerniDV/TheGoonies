#pragma once
#include <vector>

#include "TextWriter.h"

class TextManager
{

public:
	static TextManager* CreateTextManager(ShaderProgram& program, const string& sentence, const glm::vec2& position, float LetterSize = 40.f, float SpaceAmongLetters = 0.003f);
	TextManager(ShaderProgram& program, const string& sentence, const glm::vec2& position, float LetterSize, float SpaceAmongLetters);
	void print();
	void buildArray(string sentence, const glm::vec2& Position, float LetterSize, float spaceAmongLetters, ShaderProgram& program);

private:


	vector<TextWriter*> VWriter;

};



