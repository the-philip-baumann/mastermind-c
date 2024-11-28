#include <stdlib.h>
#include <stdio.h>

struct GameScore {
    int correctColourAndPosition;
    int correctColourButWrongPosition;
};

struct GameScore* evaluateGameScore(const enum Colours* userInput, const enum Colours* solution, int amountOfColoursToGuess) {
    struct GameScore* gameScore = malloc(sizeof(struct GameScore));

    gameScore->correctColourAndPosition = 0;
    gameScore->correctColourButWrongPosition = 0;

    int* processedSolution = calloc(amountOfColoursToGuess, sizeof(int));
    int* processedInput = calloc(amountOfColoursToGuess, sizeof(int));

    for (int i = 0; i < amountOfColoursToGuess; i++) {
        if (userInput[i] == solution[i]) {
            gameScore->correctColourAndPosition++;
            processedSolution[i] = 1; // Mark as processed
            processedInput[i] = 1;   // Mark as processed
        }
    }

    for (int i = 0; i < amountOfColoursToGuess; i++) {
        if (!processedInput[i]) { // Skip already processed input
            for (int j = 0; j < amountOfColoursToGuess; j++) {
                if (!processedSolution[j] && userInput[i] == solution[j]) {
                    gameScore->correctColourButWrongPosition++;
                    processedSolution[j] = 1; // Mark as processed
                    break; // Stop after finding one match
                }
            }
        }
    }

    printf("solution: ");
    for (int i = 0; i < amountOfColoursToGuess; i++) {
        printf("%s ", getStringRepresentation(solution[i]));
        if (i < amountOfColoursToGuess - 1) printf("- ");
    }
    printf("\n");

    printf("user input: ");
    for (int i = 0; i < amountOfColoursToGuess; i++) {
        printf("%s ", getStringRepresentation(userInput[i]));
        if (i < amountOfColoursToGuess - 1) printf("- ");
    }
    printf("\n");

    printf("processed solution flags: ");
    for (int i = 0; i < amountOfColoursToGuess; i++) {
        printf("%d ", processedSolution[i]);
    }
    printf("\n");

    printf("processed input flags: ");
    for (int i = 0; i < amountOfColoursToGuess; i++) {
        printf("%d ", processedInput[i]);
    }
    printf("\n");

    printf("correct colour and position: %d\n", gameScore->correctColourAndPosition);
    printf("correct colour but wrong position: %d\n", gameScore->correctColourButWrongPosition);
    printf("\n");

    return gameScore;
}
