
#include <iostream>
#include <algorithm>
#include <string>
#include "FBullCowGame.h"


enum switchPaths {
	eProcess,
	eExit
};


//Function Prototypes
void PrintIntro(void);
void PlayGame(void);
void PrintGameSummary(void);
bool PlayAgain(void);

FText GetValidGuess();


FBullCowGame BCGame;



int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (PlayAgain());
	return 0;
}

FText GetValidGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	FText sGuess;
	EGuessStatus Status = EGuessStatus::Invalid;

	do
	{
		std::cout << std::endl << "Enter Guess (type exit to quit): ";
		std::getline(std::cin, sGuess);
		Status = BCGame.CheckGuessValidity(sGuess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a valid isogram.  Please try again." << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a valid length of " << BCGame.GetHiddenWordLength() << ".  Please try again." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a all lowercase.  Please try again." << std::endl;
			break;
		case EGuessStatus::Not_Isogram_and_Wrong_Length:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a valid isogram and is the wrong length.  Please try again." << std::endl;
			break;
		case EGuessStatus::Not_Isogram_and_Not_Lowercase:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a valid isogram and is not all lowercase.  Please try again." << std::endl;
			break;
		case EGuessStatus::Wrong_Length_and_Not_Lowercase:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is the wrong length and not all lowercase.  Please try again." << std::endl;
			break;
		case EGuessStatus::Not_Isogram_and_Wrong_Length_and_Not_Lowercase:
			std::cout << "Try " << BCGame.GetCurrentTry() << ".  Guess is not a valid isogram, is the wrong length, and is not all lowercase.  Please try again." << std::endl;
			break;
		}
		
	}while(Status != EGuessStatus::OK);
	

	return sGuess;
}	

void PrintIntro(void)
{
	//Introduce the game
	std::cout << "Welcome to Bulls and Cows, a fantastic word game." << std::endl;
	std::cout << "Can you guess the "<< BCGame.GetHiddenWordLength() <<" letter isogram I'm thinking of?" << std::endl;
	return;
}



void PlayGame(void)
{
	BCGame.Reset();
	while((BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) && (!BCGame.IsGameWon()))
	{
		FBullCowCount BullCowCount;
		//Get valid guess
		FText Guess = GetValidGuess(); 
		std::cout << "Try " << BCGame.GetCurrentTry() << ". Your guess was: " << Guess << std::endl << std::endl;
		//Submit valid guess to game.
		BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "There were " << BullCowCount.Bulls << " Bulls, and " << BullCowCount.Cows << " Cows." << std::endl;	
		BCGame.IncrementTry();
	} 
	PrintGameSummary();

	return;
}

void PrintGameSummary(void)
{
	FText Response = "";
	if (BCGame.IsGameWon())
		std::cout << "Well done! You win!" << std::endl;
	else
		std::cout << "Didn't make the cut.  Better luck next time." << std::endl;
	return;
}

bool PlayAgain(void)
{
	bool bPlayAgain = false;
	FText userInput = "";
	bool correctResponse = false;

	while (!correctResponse)
	{
		std::cout << "Would you like to play again? (y/n) ";
		std::getline(std::cin, userInput);
		if (userInput == "y" || userInput == "Y")
		{
			return true;
		}
		else if (userInput == "n" || userInput == "N")
		{
			return false;
		}
		else
		{
			correctResponse = false;
		}
	}
	return false;
}


