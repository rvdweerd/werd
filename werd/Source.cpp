#include <string>
#include <iostream>
#include <fstream>
#include <limits>

void WaitForKeyPressed()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}

void GetWordFromUser(std::string& wordInput)
{
	std::cout << "Guess a five letter word: ";
	std::cin >> wordInput;
}

void GetTargetWord(std::string& wordSelected)
{
	wordSelected = "elder";
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
	std::string guess;
	std::string target;
	int attempts = 1;

	GetTargetWord(target);
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
