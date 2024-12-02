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
            processedSolution[i] = 1;
            processedInput[i] = 1;
        }
    }

    for (int i = 0; i < amountOfColoursToGuess; i++) {
        if (!processedInput[i]) {
            for (int j = 0; j < amountOfColoursToGuess; j++) {
                if (!processedSolution[j] && userInput[i] == solution[j]) {
                    gameScore->correctColourButWrongPosition++;
                    processedSolution[j] = 1;
                    break;
                }
            }
        }
    }

    return gameScore;
}
