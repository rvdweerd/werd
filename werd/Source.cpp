#pragma once
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <limits>
//#include <vector>
//#include <random>
#include "words.h"
#include <iomanip>

void WaitForKeyPressed()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void GetWordFromUser(std::string& wordInput, Words& words)
{
	//IMPLEMENT TESTS:
	// 1. word exists
	// 2. word has exactly 5 letters
	while (true)
	{
		std::cout << "Guess a five letter word: ";
		std::cin >> wordInput;
		if (words.Contains(wordInput)) break;
		std::cout << "\n" << wordInput << "is not a valid word\n";
	}
}

void GetTargetWord(std::string& wordSelected, Words& words)
{
	//IMPLEMENT RANDOM WORD SELECTOR
	wordSelected = words.GetRandom5LWord();
}

int PlayNormalGame()
{
	Words words;

	std::string guess;
	std::string target;
	int attempts = 1;

	GetTargetWord(target, words);
	//std::cout << "\nTarget word: " << target << std::endl;
	
	
	guess = "knife";
	
	while (true)
	{
		//GetWordFromUser(guess, words);
		
		if (guess == target) break;
		int score = words.CalculateScore(guess, target);
		words.AddGuess(guess, score);
		std::cout << ":" << score << "|";// << std::endl;
		attempts++;
		//std::cout << "Suggestion from the computer: " << words.GetSuggestion() << std::endl;
		guess = words.GetSuggestion(); std::cout << guess;// "Entry: " << guess;
	}

	std::cout << std::endl;// "\nSUCCESS!! \nNumber of attempts: " << attempts << std::endl;
	return attempts;
}

void PlayDiscordGame()
{
	int score = 0;
	Words words;
	std::string guess;

	while (score != 10)
	{
		std::cout << "Suggested word: " << words.GetSuggestion() << std::endl;
		std::cout << "Which word added: ";
		GetWordFromUser(guess, words);
		std::cout << "Score: ";
		std::cin >> score;
		words.AddGuess(guess, score);
	}
}

int main()
{
	std::vector<int> record;
	for (int i = 0; i < 1000; i++)
	{
		int score = PlayNormalGame();
		record.emplace_back(score);
	}
	//PlayNormalGame();
	//PlayDiscordGame();
	int sum = 0;
	std::cout << "\n vector of scores: (";
	for (int s : record)
	{
		std::cout << s << ",";
		sum += s;
	}
	std::cout << ")\n";
	float avg = (float(sum) / float(record.size() ) );
	std::cout << "Average: " << std::setprecision(3) <<avg ;
	WaitForKeyPressed();
	return 0;
}
