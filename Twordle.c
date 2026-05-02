//Author: Braydon Langum
//Purpose: Project 10
//Date: 5/1/26

#include <stdio.h>
#include <stdbool.h>

#define WORD_LEN 5
#define MAX_GUESSES 6

int customStrLen(char str[]);
bool isLetter(char c);
void toLowerCase(char str[]);
bool isValidGuess(char guess[]);
void loadWord(char secret[]);
bool isWin(char display[]);
void evaluateGuess(char guess[], char secret[], char display[], char pointers[]);
void printBoard(char displays[][WORD_LEN + 1], char pointers[][WORD_LEN + 1], int attempts);
void printWinMessage(int attempts, char winningWord[]);

int main() {
	char secret[WORD_LEN + 1];
	loadWord(secret);
	toLowerCase(secret);

	char displays[MAX_GUESSES][WORD_LEN + 1];
	char pointers[MAX_GUESSES][WORD_LEN + 1];
    
	int attempts = 0;
	bool won = false;
	char guess[256];

	while (attempts < MAX_GUESSES && !won) {
		if (attempts == MAX_GUESSES - 1) {
			printf("FINAL GUESS : ");
		} else {
			printf("GUESS %d! Enter your guess: ", attempts + 1);
		}

		scanf("%255s", guess);

		while (!isValidGuess(guess)) {
			printf("Your guess must be 5 letters long.\n");
			printf("Please try again: ");
			scanf("%255s", guess);
		}

		toLowerCase(guess);

		evaluateGuess(guess, secret, displays[attempts], pointers[attempts]);
		attempts++;

		printBoard(displays, pointers, attempts);

		if (isWin(displays[attempts - 1])) {
			won = true;
			printWinMessage(attempts, displays[attempts - 1]);
		}
	}

	if (!won) {
		printf("\nYou lost, better luck next time!\n");
	}

	return 0;
}

int customStrLen(char str[]) {
	int len = 0;
		while (str[len] != '\0') {
			len++;
		}
	return len;
}

bool isLetter(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void toLowerCase(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}
	}
}

bool isValidGuess(char guess[]) {
	if (customStrLen(guess) != WORD_LEN) {
		return false;
	}
	for (int i = 0; i < WORD_LEN; i++) {
		if (!isLetter(guess[i])) {
			return false;
		}
	}
	return true;
}

void loadWord(char secret[]) {
	FILE *file = fopen("word.txt", "r");
	if (file != NULL) {
		fscanf(file, "%5s", secret);
		fclose(file);
	} else {
		secret[0] = 'm'; secret[1] = 'o'; secret[2] = 'n'; 
		secret[3] = 'e'; secret[4] = 'y'; secret[5] = '\0';
	}
}

bool isWin(char display[]) {
	for (int i = 0; i < WORD_LEN; i++) {
		if (display[i] < 'A' || display[i] > 'Z') {
			return false;
		}
	}
	return true;
}

void evaluateGuess(char guess[], char secret[], char display[], char pointers[]) {
	bool secret_used[WORD_LEN];
    
	for (int i = 0; i < WORD_LEN; i++) {
		display[i] = guess[i];
		pointers[i] = ' ';
		secret_used[i] = false;
	}
	display[WORD_LEN] = '\0';
	pointers[WORD_LEN] = '\0';

	for (int i = 0; i < WORD_LEN; i++) {
		if (guess[i] == secret[i]) {
			display[i] = guess[i] - 32;
			secret_used[i] = true;
		}
	}

	for (int i = 0; i < WORD_LEN; i++) {
		if (guess[i] != secret[i]) { 
			for (int j = 0; j < WORD_LEN; j++) {
				if (!secret_used[j] && guess[i] == secret[j]) {
					pointers[i] = '^';
					secret_used[j] = true; 
					break;
				}
			}
		}
	}
}

void printBoard(char displays[][WORD_LEN + 1], char pointers[][WORD_LEN + 1], int attempts) {
	printf("=================================\n");
	for (int i = 0; i < attempts; i++) {
		printf("%s\n", displays[i]);
		printf("%s\n", pointers[i]);
	}
}
void printWinMessage(int attempts, char winningWord[]) {
	printf("             %s\n", winningWord);
    
	if (attempts == 1) {
		printf("       You won in 1 guess!\n");
		printf("             GOATED!\n");
	} else {
		printf("       You won in %d guesses!\n", attempts);
	}

	if (attempts == 2 || attempts == 3) {
		printf("             Amazing!\n");
	} else if (attempts == 4 || attempts == 5) {
		printf("               Nice!\n");
	}
}

