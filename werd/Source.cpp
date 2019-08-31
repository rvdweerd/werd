#include <string>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <random>

class Words {
public:
	Words()
		:
		rng( std::random_device()())
	{
		std::ifstream in("5Lwords.txt");
		while (in.good())
		{
			std::string str;
			getline(in,str);
			fiveLetterWords.emplace_back(str);
		}
	}
	std::string GetRandom5LWord()
	{
		std::uniform_int_distribution<int> nDistr(0, fiveLetterWords.size() - 1);
		return fiveLetterWords[nDistr(rng)];
	}

private:
	std::vector <std::string> fiveLetterWords;
	std::mt19937 rng;
};

void WaitForKeyPressed()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void GetWordFromUser(std::string& wordInput)
{
	//IMPLEMENT TESTS:
	// 1. word exists
	// 2. word has exactly 5 letters

	std::cout << "Guess a five letter word: ";
	std::cin >> wordInput;
}

void GetTargetWord(std::string& wordSelected, Words& words)
{
	//IMPLEMENT RANDOM WORD SELECTOR
	wordSelected = words.GetRandom5LWord();
}

int CalculateScore(std::string guess, std::string target)
{
	int score=0;
	bool activeTarget[5] { true,true,true,true,true };
	bool activeGuess[5]  { true,true,true,true,true };
	
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
	for (int i = 0; i < 5 ; i++) //looping guess letters
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

int main()
{
	Words words;
	std::string guess;
	std::string target;
	int attempts = 1;

	GetTargetWord(target, words);
	std::cout << "\nTarget word: " << target<<std::endl;
	bool win = false;


	while (!win)
	{
		GetWordFromUser(guess);
		if (guess == target) break;
		std::cout << "\nPoints: " << CalculateScore(guess, target) << std::endl;
		attempts++;
	}
	
	std::cout << "\nSUCCESS!! \nNumber of attempts: " << attempts;
	WaitForKeyPressed();
	return 0;
}
