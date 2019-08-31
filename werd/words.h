#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <random>

class Words {
public:
	class Pair {
	public:
		Pair(std::string word_in, int score_in)
			:
			word(word_in),
			score(score_in)
		{
		}
	public:
		std::string word;
		int score;
	};
	Words()
		:
		rng(std::random_device()())
	{
		std::ifstream in("5Lwords.txt");
		while (in.good())
		{
			std::string str;
			getline(in, str);
			fiveLetterWords.emplace_back(str);
		}
	}
	std::string GetRandom5LWord()
	{
		std::uniform_int_distribution<int> nDistr(0, fiveLetterWords.size() - 1);
		return fiveLetterWords[nDistr(rng)];
	}
	bool Contains(std::string in_word)
	{
		for (size_t i = 0; i < fiveLetterWords.size(); i++)
		{
			if (in_word == fiveLetterWords[i])
			{
				return true;
			}
		}
		return false;
	}
	void AddGuess(std::string word_in, int score_in)
	{
		priorGuesses.emplace_back(word_in, score_in);
	}
	std::string GetSuggestion()
	{
		bool Test = false;
		std::string guess;
		while (!Test)
		{
			Test = true;
			guess = GetRandom5LWord();
			for (Pair p : priorGuesses)
			{
				if (CalculateScore(guess, p.word) != p.score)
				{
					Test = false;
				}
			}
		}
		return guess;
	}
	int CalculateScore(std::string guess, std::string target)
	{
		int score = 0;
		bool activeTarget[5]{ true,true,true,true,true };
		bool activeGuess[5]{ true,true,true,true,true };

		//hard matches
		for (int i = 0; i < 5; i++)
		{
			if (guess[i] == target[i])
			{
				score += 2;
				activeTarget[i] = false;
				activeGuess[i] = false;
			}
		}

		//soft matches
		for (int i = 0; i < 5; i++) //looping guess letters
		{
			for (int j = 0; j < 5; j++) //checking matches for each guess word  letter
			{
				if (guess[i] == target[j] && activeTarget[j] && activeGuess[i])
				{
					score++;
					activeTarget[j] = false;
					activeGuess[i] = false;
					break;
				}
			}
		}
		return score;
	}

private:
	std::vector <std::string> fiveLetterWords;
	std::vector<Pair> priorGuesses;
	std::mt19937 rng;
};
