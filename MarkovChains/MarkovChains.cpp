#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Word
{
	std::string word;
	int probability;
	int count;
};

struct SubSentence
{
	std::string sentence;
	std::vector<Word> wordsAfter;
	int totalAppearances = 0;
};

int main()
{


	return 0;
}