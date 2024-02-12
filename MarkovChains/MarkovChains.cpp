#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Word
{
	std::string word;
	int probability;
	int count = 0;
};

struct SubSentence
{
	std::string sentence;
	std::vector<Word> wordsAfter;
	int totalAppearances = 0;
};

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

	for (const auto& x : subSentences)
	{
		std::cout << x.sentence << " " << x.totalAppearances << "		";
		for (const auto& y : x.wordsAfter)
		{
			std::cout << y.word << "- " << y.count << "  ";
		}
		std::cout << '\n';
	}

	return 0;
}