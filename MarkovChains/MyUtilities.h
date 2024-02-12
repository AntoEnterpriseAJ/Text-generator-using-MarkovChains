#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <vector>

struct Word
{
	std::string word;
	double probability;
	int count = 0;
};

struct SubSentence
{
	std::string sentence;
	std::vector<Word> wordsAfter;
	int totalAppearances = 0;
};

bool isAlreadyFoundAfter(const SubSentence& subSentences, const std::string& targetWord, int& indexFoundAt);

bool isSentenceFoundAlready(const std::vector<SubSentence>& subSentences, const std::string& targetSetence, int& indexFoundAt);

void calculateProbabilities(std::vector<SubSentence>& subSentences);

void generateText(const std::vector<SubSentence>& subSentences, const int& wordPrecision, const int& wordCount);

void displayDetails(const std::vector<SubSentence>& subSentences);

#endif