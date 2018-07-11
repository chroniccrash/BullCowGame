#pragma once
#include <string>
#include <map>
#define TMap std::map

using FText = std::string;
using FString = std::string;
using int32 = int32_t;


constexpr int32 DEFAULT_MAX_TRIES = 8;
const FString HIDDEN_WORD = "planet";
constexpr int32 WORD_LENGTH = 6;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};


enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Isogram_and_Wrong_Length,
	Not_Isogram_and_Not_Lowercase,
	Wrong_Length_and_Not_Lowercase,
	Not_Isogram_and_Wrong_Length_and_Not_Lowercase	
};

class FBullCowGame
{
public:
	FBullCowGame(FString Solution = HIDDEN_WORD, int32 maxTries = DEFAULT_MAX_TRIES);
	~FBullCowGame();
	//Getter Functions
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FText GetSolution() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	bool IsAllLower(FString Guess) const;
	
	//Setter Functions
	void SetMaxTries(int32 newMaxTries);
	void SetCurrentTry(int32 newCurrentTry);
	void SetSolution(FString newSolution);
	void IncrementTry();
	//Generic Functions
	void Reset();
	EGuessStatus CheckGuessValidity(FString Guess) const;
	FBullCowCount SubmitValidGuess(FString Guess); //Counts bulls and cows and increases try # on valid guess

private:
	int32 CurrentTry = 1;
	int32 MaxTries = DEFAULT_MAX_TRIES;
	FString Solution;
	bool bIsGameWon = false;

	bool IsIsogram(FString Guess) const;
};

