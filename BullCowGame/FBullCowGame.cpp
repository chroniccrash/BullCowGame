#include "FBullCowGame.h"
#include <iostream>

FBullCowGame::FBullCowGame(FString newSolution, int32 maxTries)
{
	if (maxTries > 0)
		MaxTries = maxTries;
	else
		MaxTries = DEFAULT_MAX_TRIES;
	Solution = newSolution;
	CurrentTry = 1;
}

FBullCowGame::~FBullCowGame()
{
}

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
FString FBullCowGame::GetSolution() const { return Solution; }

int32 FBullCowGame::GetHiddenWordLength() const
{
	return Solution.length();
}

bool FBullCowGame::IsGameWon() const
{
	if (bIsGameWon)
		return true;
	return false;
}

bool FBullCowGame::IsAllLower(FString Guess) const
{
	bool IsLower = true;
	for (int i = 0; i < Guess.length(); i++)
	{
		if (!islower(Guess[i]))
		{
			IsLower = false;
			break;
		}
	}
	if (IsLower)
		return true;
	else
		return false;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	TMap<char, bool> hMap;

	for (char Letter : Guess)
	{
		if (!hMap[tolower(Letter)])
			hMap[tolower(Letter)] = true;
		else
			return false;

	}
	return true;
	
}

void FBullCowGame::SetMaxTries(int32 newMaxTries)
{
	if (newMaxTries > 0)
		MaxTries = newMaxTries;
	return;
}

void FBullCowGame::SetCurrentTry(int32 newCurrentTry)
{
	if (newCurrentTry > 0)
		CurrentTry = newCurrentTry;
	return;
}

void FBullCowGame::SetSolution(FString newSolution)
{
	Solution = newSolution;
}

void FBullCowGame::IncrementTry()
{
	CurrentTry += 1;
}

void FBullCowGame::Reset()
{
	Solution = HIDDEN_WORD;
	MaxTries = DEFAULT_MAX_TRIES;
	CurrentTry = 1;
	bIsGameWon = false;

}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	bool IsProperIsogram = true;
	bool IsLowercase = true;
	bool IsProperWordLength = true;

	if (!IsIsogram(Guess))//Not an isogram
		IsProperIsogram = false;
	if (!IsAllLower(Guess))//Not all lowercase
		IsLowercase = false;
	if (Guess.length() != this->GetHiddenWordLength())//Word length is wrong
		IsProperWordLength = false;

	if ((not IsProperIsogram) & (not IsLowercase) & (not IsProperWordLength))
		return EGuessStatus::Not_Isogram_and_Wrong_Length_and_Not_Lowercase;
	else if ((not IsProperIsogram) & (not IsLowercase))
		return EGuessStatus::Not_Isogram_and_Not_Lowercase;
	else if ((not IsProperIsogram) & (not IsProperWordLength))
		return EGuessStatus::Not_Isogram_and_Wrong_Length;
	else if ((not IsLowercase) & (not IsProperWordLength))
		return EGuessStatus::Wrong_Length_and_Not_Lowercase;
	else if (not IsLowercase)
		return EGuessStatus::Not_Lowercase;
	else if (not IsProperWordLength)
		return EGuessStatus::Wrong_Length;
	else if (not IsProperIsogram)
		return EGuessStatus::Not_Isogram;
	else
		return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//setup a return variables
	FBullCowCount BullCowCount;
	
	for (int32 i = 0; i < (int32)Solution.length(); i++)
	{
		if (Solution[i] == Guess[i])
			BullCowCount.Bulls++;
		else
		{
			for (int32 j = 0; j < (int32)Guess.length(); j++)
			{
				if (Solution[i] == Guess[j])
					BullCowCount.Cows++;
			}
		}
	}
	if (Guess == Solution)
		bIsGameWon = true;
	else
		bIsGameWon = false;
	return BullCowCount;
}
