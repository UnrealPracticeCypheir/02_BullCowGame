//	Abstraction and ecapsulation
//	- A major goal in writing software is to manage compelxity.
//	- Abstraction is a technique for managing complexity,
//	  by considering things at a higher level.
//	
//	When to use for vs while loops
//	- Use "for" when you know at compile time how many times it will loop.
//	- Use "while" when youre not sure how many time it will loop.
//
//		for (initialization; condition; increase)
//			statement;
//
//	Comparison operators: == equals, && and, || or, [n] to access string at n=0
//
//	Do while loops
//		
//		do {
//			<the code>
//		}
//		while (condition);
//
//	FString - Manipulatable
//	FText - User Output
//	
//	If Statements
//	
//		if (condition1) {
//			statements;
//		} else if (condition2) {
//			statements;
//		} else {
//			statements;
//		}
//	
//	A place for everything, everything in its place
//	Think carefully about what you store
//	General bandwidth vs storage
//	For example store birthday, not age
//	until proven otherwise, dont store results
//	
//	Switch Statements
//	
//		switch (expression)
//			{
//				case constant1:
//					statements;
//					break;
//				case constant2:
//					statements;
//					break;
//				default:
//					statements;
//			}
//	Avoid Implicit dependencies
//		Implicit: suggested though not directly expressed.
//		Dependent: reliant on something else
//	
//		An implicit dependency is when it's not completely clear
//		that one thing depends on another. For example the order
//		of check in CheckGuess Validity().
//	
//	Unreal Engine likes numbers that dont change to use const and constexpr
//	Cannot change once the program is running


/*////////////////////////////////////////////////////////////////////
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC patter, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
////////////////////////////////////////////////////////////////////*/

// "preprocessor directive"
// - copies and pastes other code
// - use <> for standard libraries
// - use "" for libraries youve created
// - Use care with "using namespace" when you have access to multiple same named functions

#pragma once

#include "FBullCowGame.h"
#include <string>
#include <iostream>		

// to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;						// Create a new instance (BCGame) of the game (FBullCowGame), re-use across plays

// Entry point for our application
int main()
{

	do {
		PrintIntro();
		PlayGame();
		std::cout << std::endl;
	} while (AskToPlayAgain() == 1);

	return 0;
}

void PrintIntro()
{

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();	

	// Loop for guesses	while the game is NOT won and turns still remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "\nYour guess was: " << Guess;
		std::cout << "\nBulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
	return;
}

// Get a guess from the player and repeat the guess back to them
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << "/" << BCGame.GetMaxTries() << " - Enter your guess: ";

		std::getline(std::cin, Guess);					// Get line will not ignore the spaces in a std::string when taking multiple inputs

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;

		default:
			// Assuming the guess is valid
			break;
		}
		//std::cout << std::endl;

	} while (Status != EGuessStatus::OK); // Loop till no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
