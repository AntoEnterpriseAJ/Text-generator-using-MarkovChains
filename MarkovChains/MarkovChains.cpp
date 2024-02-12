#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Random.h"
#include "MyUtilities.h"

int main()
{
	std::string fileName{ "fileIn.txt" };
	std::ifstream file(fileName);
	int wordPrecision;
	std::cout << "Word precision: ";
	std::cin >> wordPrecision;

	std::vector<SubSentence> subSentences;
	std::string currentSentence;
	for (int i = 0; i < wordPrecision && !file.eof(); ++i)
	{
		std::string word;
		file >> word;
		currentSentence += word + ' ';
	}
	subSentences.push_back({ currentSentence, {},  0});

	while (!file.eof())
	{
		std::string word;
		file >> word;
		int indexFoundAt;

		if (isSentenceFoundAlready(subSentences, currentSentence, indexFoundAt))
		{
			int wordFoundIndex;
			if (isAlreadyFoundAfter(subSentences[indexFoundAt], word, wordFoundIndex))
			{
				subSentences[indexFoundAt].wordsAfter[wordFoundIndex].count++;
			}
			else
			{
				subSentences[indexFoundAt].wordsAfter.push_back({ word, 0, 1 });
			}
			subSentences[indexFoundAt].totalAppearances++;
		}
		else
		{
			subSentences.push_back({ currentSentence, {{word, 0, 1}}, 1 });
		}

		size_t spaceIndex = currentSentence.find(' ');
		currentSentence = currentSentence.substr(spaceIndex + 1) + word + ' ';
	}

	calculateProbabilities(subSentences);

	while (true)
	{
		std::cout << "Generate text(1)\nDisplay text details(2)\nExit(3)\nSelected option: ";
		int option;
		std::cin >> option;

		switch (option)
		{
		case (1):
		{
			std::cout << "\nWord count: ";
			int wordCount;
			std::cin >> wordCount;
			generateText(subSentences, wordPrecision, wordCount);
			std::cout << "\n\n";
			break;
		}
		case (2):
		{
			displayDetails(subSentences);
			break;
		}
		case(3):
		{
			return 1;
		}
		default:
			break;
		}
	}

	return 0;
}