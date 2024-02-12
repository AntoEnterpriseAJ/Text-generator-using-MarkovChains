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

	for (const auto& x : subSentences)
	{
		std::cout << x.sentence << " " << x.totalAppearances << "		";
		for (const auto& y : x.wordsAfter)
		{
			std::cout << y.word << "- " << y.count << ", " << y.probability  << "  ";
		}
		std::cout << '\n';
	}

	int wordCount;
	std::cout << "Number of words to be generated: ";
	std::cin >> wordCount;


	generateText(subSentences, wordPrecision, wordCount);

	return 0;
}