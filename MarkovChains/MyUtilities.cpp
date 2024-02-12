#include <iostream>
#include "MyUtilities.h"
#include "Random.h"

bool isAlreadyFoundAfter(const SubSentence& subSentences, const std::string& targetWord, int& indexFoundAt)
{
	for (int i = 0; i < subSentences.wordsAfter.size(); ++i)
	{
		if (subSentences.wordsAfter[i].word == targetWord)
		{
			indexFoundAt = i;
			return true;
		}
	}
	return false;
}

bool isSentenceFoundAlready(const std::vector<SubSentence>& subSentences, const std::string& targetSetence, int& indexFoundAt)
{
	for (int i = 0; i < subSentences.size(); ++i)
	{
		if (subSentences[i].sentence == targetSetence)
		{
			indexFoundAt = i;
			return true;
		}
	}
	return false;
}

void calculateProbabilities(std::vector<SubSentence>& subSentences)
{
	for (auto& ss : subSentences)
	{
		for (auto& word : ss.wordsAfter)
		{
			word.probability = (1.0 * word.count / ss.totalAppearances);
		}
	}

	//cummulative probabilities
	for (auto& ss : subSentences)
	{
		for (int i = 1; i < ss.wordsAfter.size(); ++i)
		{
			double previous = ss.wordsAfter[i - 1].probability;
			ss.wordsAfter[i].probability += previous;
		}
	}
}

void generateText(const std::vector<SubSentence>& subSentences, const int& wordPrecision, const int& wordCount)
{
	SubSentence currentSubSentence = subSentences[randomNumberGen(0, subSentences.size() - 1)];
	std::cout << currentSubSentence.sentence;
	int count = 0;
	while (count < wordCount && currentSubSentence.wordsAfter.size() != 0)
	{
		double randomProb = randomNumberGen(0.0, 1.0);
		bool found = false;
		for (int i = 0; currentSubSentence.wordsAfter.size() && !found; ++i)
		{
			if (randomProb < currentSubSentence.wordsAfter[i].probability)
			{
				found = true;
				std::string word = currentSubSentence.wordsAfter[i].word;
				std::cout << word << " ";

				std::string newSubSentence;
				if (wordPrecision == 1)
				{
					newSubSentence = word + " ";
				}
				else
				{
					size_t spaceIndex = currentSubSentence.sentence.find(" ");
					newSubSentence = currentSubSentence.sentence.substr(spaceIndex + 1) + word + ' ';
				}

				//find the new subSentence obj with the new sentence
				bool foundNewSS = false;
				for (int i = 0; i < subSentences.size(); ++i)
				{
					if (newSubSentence == subSentences[i].sentence)
					{
						currentSubSentence = subSentences[i];
						foundNewSS = true;
						exit;
					}
				}

				if (!foundNewSS)
				{
					currentSubSentence = {};
				}
			}
		}
		count++;
	}
}