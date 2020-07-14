/***********************************************************************************************************************
Name: Jackie Kwok
Program: Unbeatable Tic-tac-toe Bot
Description: Recreates Tic-tac-toe and allows the user to play against a computer that will never lose.
***********************************************************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define EMPTY 0
#define O 1
#define X 2

/***********************************************************************************************************************
Title: How to return a local array from a C/C++ function?
Author: Mazhar Imam Khan (Improved by Rishabh Prabhu)
Code Cited: "Using struct" code
Availability: https://www.geeksforgeeks.org/return-local-array-c-function/
***********************************************************************************************************************/
struct board {
	int array[3][3];
};

struct board createBoard() {
	struct board elem;

	elem.array[0][0] = EMPTY;
	elem.array[0][1] = EMPTY;
	elem.array[0][2] = EMPTY;
	elem.array[1][0] = EMPTY;
	elem.array[1][1] = EMPTY;
	elem.array[1][2] = EMPTY;
	elem.array[2][0] = EMPTY;
	elem.array[2][1] = EMPTY;
	elem.array[2][2] = EMPTY;

	return elem;
}

void printBoard(struct board elem) {
	// Loop through the array and print the board based on the values of the elements of the array.
	for(int i = 0; i < 3; i++) {
 		for(int j = 0; j < 3; j++) {
			if (elem.array[i][j] == EMPTY) {
				printf("   ");
			} else if (elem.array[i][j] == O) {
				printf(" O ");
			} else if (elem.array[i][j] == X) {
				printf(" X ");
			}
			
			// Prints '|' to draw the vertical lines of the board.
			if (j != 2) {
				printf("|");
			}
		}

		// Prints '-' to draw the horizontal lines of the board. 
		if (i != 2) {
			printf("\n-----------\n");
		}
	}
	printf("\n\n");
}

int checkWinner(struct board elem) {
	// Used to check the "type" of win.
	int haveWinner = 0;
	char youWin[] = "You are the winner! ";
	char compWin[] = "Sorry! The computer won! ";

	// This breaks down all the possible ways to win. To determine who wins, we can check the value 
	// of the "first" element of the winning row. Since the board is initialized with all 0's, we 
	// need to make sure that a win is not triggered by an empty row, so we check the first element 
	// of each possible way to win to make sure that they're not equal to 0.
	if ((elem.array[0][0] == elem.array[0][1]) && (elem.array[0][1] == elem.array[0][2]) && 
		elem.array[0][0] != EMPTY) {
		haveWinner = 1;
	} else if ((elem.array[0][0] == elem.array[1][0]) && (elem.array[1][0] == elem.array[2][0]) && 
		elem.array[0][0] != EMPTY) {
		haveWinner = 1; 
	} else if ((elem.array[0][0] == elem.array[1][1]) && (elem.array[1][1] == elem.array[2][2]) && 
		elem.array[0][0] != EMPTY) {
		haveWinner = 1;
	} else if ((elem.array[0][2] == elem.array[1][2]) && (elem.array[1][2] == elem.array[2][2]) && 
		elem.array[0][2] != EMPTY) {
		haveWinner = 2;
	} else if ((elem.array[0][2] == elem.array[1][1]) && (elem.array[1][1] == elem.array[2][0]) && 
		elem.array[0][2] != EMPTY) {
		haveWinner = 2;
	} else if ((elem.array[2][0] == elem.array[2][1]) && (elem.array[2][1] == elem.array[2][2]) && 
		elem.array[2][0] != EMPTY) {
		haveWinner = 3;
	} else if ((elem.array[0][1] == elem.array[1][1]) && (elem.array[1][1] == elem.array[2][1]) && 
		elem.array[0][1] != EMPTY) {
		haveWinner = 4;
	} else if ((elem.array[1][0] == elem.array[1][1]) && (elem.array[1][1] == elem.array[1][2]) && 
		elem.array[1][0] != EMPTY) {
		haveWinner = 5;
	}

	// If haveWinner is 1, the winning row includes the top left spot, so we check that spot to 
	// determine the winner. 
	if (haveWinner == 1) {
		if (elem.array[0][0] == O) {
			printf("%s\n", youWin);
		} else {
			printf("%s\n", compWin);
		}
		return 1;
	// If haveWinner is 2, the winning row includes the top right spot, so we check that spot to
	// determine the winner.
	} else if (haveWinner == 2) {
		if (elem.array[0][2] == O) {
			printf("%s\n", youWin);
		} else {
			printf("%s\n", compWin);
		}
		return 1;
	// If haveWinner is 3, the winning row includes the bottom left spot, so we check that spot to
	// determine the winner.
	} else if (haveWinner == 3) {
		if (elem.array[2][0] == O) {
			printf("%s\n", youWin);
		} else {
			printf("%s\n", compWin);
		}
		return 1;
	// If haveWinner is 4, the winning row includes the middle spot in the top row, so we check that
	// spot to determine the winner.
	} else if (haveWinner == 4) {
		if (elem.array[0][1] == O) {
			printf("%s\n", youWin);
		} else {
			printf("%s\n", compWin);
		}
		return 1;
	// If haveWinner is 5, the winning row includes the spot left of the middle spot, so we check
	// that spot to determine the winner.
	} else if (haveWinner == 5) {
		if (elem.array[1][0] == O) {
			printf("%s\n", youWin);
		} else {
			printf("%s\n", compWin);
		}
		return 1;
	// Else, there is no winner.
	} else {
		return 0;
	}
}

void compTurn(struct board *elem) {
	// If the middle spot it open, the computer should take it immediately because it blocks
	// four out of the eight possible was for the player to win.
	if (elem->array[1][1] == EMPTY) {
		elem->array[1][1] = X;
		return;
	} 

	// If there are two spots in a row that are equal and not empty, then the computer should
	// take the third spot in that row. This either blocks the player from winning or leads to
	// a victory for the computer.
	for (int row = 0; row < 3; row++) {
		if (elem->array[row][0] == elem->array[row][1] && elem->array[row][0] != EMPTY) {
			if (elem->array[row][2] == EMPTY) {
				elem->array[row][2] = X;
				return;
			} 
		}
	
		if (elem->array[row][0] == elem->array[row][2] && elem->array[row][0] != EMPTY) {
			if (elem->array[row][1] == EMPTY) {
				elem->array[row][1] = X;
				return;
			} 
		}

		if (elem->array[row][1] == elem->array[row][2] && elem->array[row][1] != EMPTY) {
			if (elem->array[row][0] == EMPTY) {
				elem->array[row][0] = X;
				return;
			}
		}		
	}

	// If there are two spots in a column that are equal and not empty, then the computer should
	// take the third spot in that column. This either blocks the player from winning or leads to
	// a victory for the computer.
	for (int col = 0; col < 3; col++) {
		if (elem->array[0][col] == elem->array[1][col] && elem->array[0][col] != EMPTY) {
			if (elem->array[2][col] == EMPTY) {
				elem->array[2][col] = X;
				return;
			}
		}

		if (elem->array[0][col] == elem->array[2][col] && elem->array[0][col] != EMPTY) {
			if (elem->array[1][col] == EMPTY) {
				elem->array[1][col] = X;
				return;
			}
		}

		if (elem->array[1][col] == elem->array[2][col] && elem->array[1][col] != EMPTY) {
			if (elem->array[0][col] == EMPTY) {
				elem->array[0][col] = X;
				return;
			}
		}
	}

	// If there are two spots in the diagonal starting from the top left corner that
	// are equal and not empty, then the computer should take the third spot in that
	// diagonal. This either blocks the player from winning or leads to a victory for
	// the computer.
	if (elem->array[0][0] == elem->array[1][1] && elem->array[0][0] != EMPTY) {
		if (elem->array[2][2] == EMPTY) {
			elem->array[2][2] = X;
			return;
		}
	}

	if (elem->array[0][0] == elem->array[2][2] && elem->array[0][0] != EMPTY) {
		if (elem->array[1][1] == EMPTY) {
			elem->array[1][1] = X;
			return;
		}
	}

	if (elem->array[1][1] == elem->array[2][2] && elem->array[1][1] != EMPTY) {
		if (elem->array[0][0] == EMPTY) {
			elem->array[0][0] = X;
			return;
		}
	}

	// If there are two spots in the diagonal starting from the top right corner that
	// are equal and not empty, then the computer should take the third spot in that
	// diagonal. This either blocks the player from winning or leads to a victory for
	// the computer.
	if (elem->array[0][2] == elem->array[1][1] && elem->array[0][2] != EMPTY) {
		if (elem->array[2][0] == EMPTY) {
			elem->array[2][0] = X;
			return;
		}
	}	

	if (elem->array[0][2] == elem->array[2][0] && elem->array[0][2] != EMPTY) {
		if (elem->array[1][1] == EMPTY) {
			elem->array[1][1] = X;
			return;
		}
	}

	if (elem->array[1][1] == elem->array[2][0] && elem->array[1][1] != EMPTY) {
		if (elem->array[0][2] == EMPTY) {
			elem->array[0][2] = X;
			return;
		}
	}
	
	// Blocks the player if they try to use the side strategy.
	if (elem->array[0][1] == O && elem->array[1][0] == O) {
		if (elem->array[0][0] == EMPTY) {
			elem->array[0][0] = X;
			return;
		}
	} else if (elem->array[0][1] == O && elem->array[1][2] == O) {
		if (elem->array[0][2] == EMPTY) {
			elem->array[0][2] = X;
			return;
		}
	} else if (elem->array[1][0] == O && elem->array[2][1] == O) {
		if (elem->array[2][0] == EMPTY) {
			elem->array[2][0] = X;
			return;
		}
	} else if (elem->array[1][2] == O && elem->array[2][1] == O) {
		if (elem->array[2][2] == EMPTY) {
			elem->array[2][2] = X;
			return;
		}
	}
	
	// Blocks the player if they try to use the middle strategy.
	if (elem->array[1][1] == O) {
		if (elem->array[0][0] == EMPTY) {
			elem->array[0][0] = X;
		} else if (elem->array[0][2] == EMPTY) {
			elem->array[0][2] = X;
		} else if (elem->array[2][0] == EMPTY) {
			elem->array[2][0] = X;
		} else if (elem->array[2][2] == EMPTY) {
			elem->array[2][2] = X;
		}
	// Blocks the player if they try to use the corner strategy.
	} else {
		if (elem->array[0][1] == EMPTY) {
			elem->array[0][1] = X;
		} else if (elem->array[1][0] == EMPTY) {
			elem->array[1][0] = X;
		} else if (elem->array[1][2] == EMPTY) {
			elem->array[1][2] = X;
		} else if (elem->array[2][1] == EMPTY) {
			elem->array[2][1] = X;
		}
	}
}

int tie(struct board elem) {
	// Loop through the entire board. If an empty spot is
	// discovered, return 0. Otherwise, return 1.
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (elem.array[row][col] == EMPTY) {
				return 0;
			}
		}
	}
	
	return 1;
}

/***********************************************************************************************************************
Title: How do you clear the console screen in C? (Stack Overflow)
Asked by: devurs (http://stackoverflow.com/users/183441/devurs)
Answered by: nbro (http://stackoverflow.com/users/3924118/nbro)
Date: 3/27/2016
Availability: http://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
***********************************************************************************************************************/
void clearScr() {
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		system("clear");
	#endif

	#if defined(_WIN32) || defined(_WIN64)
		system("cls");
	#endif
}

/***********************************************************************************************************************
Title: Time delay in C
Author: Pratik Chhajer (improved by ManasChhabra2 & tapin13)
Availability: https://geeksforgeeks.org/time-delay-c/
***********************************************************************************************************************/
void delay(int seconds) {
	// Converts seconds of delay desired into milliseconds.
	int millSec = CLOCKS_PER_SEC * seconds;

	// Stores the time we start at before the delay.
	clock_t startTime = clock();

	// Loops until the current time is past our starting time + the number of milliseconds we want to delay.
	while (clock() < startTime + millSec);
}

int main() {
	// Calls createBoard to create a board named elem.
	struct board elem = createBoard();

	// When winnerFound is 0, there is no winner yet. If it is 1, then a winner has been found and the game 
	// should end.
	int winnerFound = 0;

	// Each iteration of this loop is one turn for the player and one turn for the computer. The game will end if
	// a winner is found.
	while (winnerFound != 1) {
		char promptUser[] = "It is now your turn. Please choose a cell by inputting a number from 1 to 9.";
		char reenterInput[] = "That spot is already taken. Please choose another number. ";
		char invalidInput[] = "You have entered an invalid number. Please enter a number from 1 to 9.\n";
		char tieGame[] = "Tie game! There is no winner!\n";

		printf("%s\n", promptUser);

		// Stores the number that the user inputs when choosing a spot on the board.
		int userInput;

		// Stores the invalid input of the user.
		int invalid;	
		
		/*******************************************************************************************************
		Title: How to deal with wrong input in C? (Stack Overflow)
		Asked by: Medvednic (http://stackoverflow.com/users/3142487/mednedvic)
		Author: Filipe Gonclaves (http://stackoverflow.com/users/2793118/filipe-gonclaves)
		Date: 2/13/2014
		Availability: http://stackoverflow.com/questions/21536168/how-to-deal-with-wrong-input-c
		*******************************************************************************************************/
		while (scanf("%d", &userInput) != 1) {
			while (!isspace(invalid = getchar()));
			ungetc(invalid, stdin);
			printf("%s", invalidInput);
			continue;
		}
		
		// Fills the corresponding spot depending on userInput. 
		// If the spot is already taken, prompt the user to
		// choose another spot.	
		switch(userInput) {
			case 1: if (elem.array[0][0] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[0][0] = O;
				break;
	
			case 2: if (elem.array[0][1] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[0][1] = O;
				break;

			case 3: if (elem.array[0][2] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[0][2] = O;
				break;

			case 4: if (elem.array[1][0] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[1][0] = O;
				break;

			case 5: if (elem.array[1][1] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[1][1] = O;
				break;

			case 6: if (elem.array[1][2] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[1][2] = O;
				break;
	
			case 7: if (elem.array[2][0] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[2][0] = O;
				break;

			case 8: if (elem.array[2][1] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[2][1] = O;
				break;

			case 9: if (elem.array[2][2] != EMPTY) {
					printf("%s", reenterInput);
					continue;
				}
				elem.array[2][2] = O;
				break;
		}
		
		// We only want to print the board when the user makes a valid action.
		if (userInput >= 1 && userInput <= 9) {
			// Clears the screen before new boards get printed.
			clearScr();
			printf("The move you just made.\n");		
	
			printBoard(elem);		
		}
		
		// Tell the user when their number is too small and let them try again.
		if (userInput < 1) {
			printf("That number was too small!\n");
		}

		// Tell the user when their number is too large and let them try again.
		if (userInput > 9) {
			printf("That number was too large!\n");
		}

		// Update winnerFound by running checkWinner(elem). If a winner is found, break out of the loop.
		winnerFound = checkWinner(elem);
		if (winnerFound == 1) {
			break;
		}
		
		// If the board is full after the player's turn and there is no winner, declare a tie.
		if (tie(elem) == 1) {
			printf("%s", tieGame);
			break;
		}

		// Start computer's turn. Only start the computer's turn if userInput has a valid value because we 
		// don't want the computer to get an extra turn.
		if (userInput >= 1 && userInput <= 9) {
			printf("It is now the computer's turn. Please wait a moment.\n");
			
			// Creates a small delay so that the player has time to see the move they made before the
			// computer makes its move.
			delay(2);

			// Erases the previous board (the board printed after the user's turn) so that an updated
			// board can be printed to the screen.
			clearScr();

			compTurn(&elem);
			printBoard(elem);
		}

		// Update winnerFound by running checkWinner(elem). If a winner is found, break out of the loop.
		winnerFound = checkWinner(elem);

		// If the board is full after the computer's turn and there is no winner, declare a tie.
		if (tie(elem) == 1) {
			printf("%s", tieGame);
			break;
		}
	}

	return 0;
}
