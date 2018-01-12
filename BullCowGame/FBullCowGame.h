/*
The game logic (no view code or direct user interation
The game is a simple guess the word based on Mastermind
*/

#pragma once
#include <string>

// to make syntax Unreal Friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Numbers_Symbols,
	Not_Lowercase
};

class FBullCowGame {
public:																		//Public methods
	FBullCowGame();			// Constructor, all of this will be done when new instance is created.

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	FBullCowCount SubmitValidGuess(FString);
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	void Reset();
	
private:																	//Private methods/Support Function/Helper Functions, member variables, helper functions
	// see constructor for initialization
	int32 MyCurrentTry;
	bool bIsGameWon;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};