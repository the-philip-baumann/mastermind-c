#include <stdlib.h>
#include <stdio.h>

struct GameScore {
      int correctColourAndPosition;
      int correctColourButWrongPosition;
};

struct GameScore* evaluateGameScore(const enum Colours* userInput, const enum Colours* solution, int amountOfColoursToGuess) {
    struct GameScore* gameScore = malloc(sizeof(struct GameScore));
    enum Colours* userInputClone = malloc(amountOfColoursToGuess * sizeof(enum Colours));
    enum Colours* solutionClone = malloc(amountOfColoursToGuess * sizeof(enum Colours));
    memcpy(userInputClone, userInput, amountOfColoursToGuess * sizeof(enum Colours*));
    memcpy(solutionClone, solution, amountOfColoursToGuess  * sizeof(enum Colours*));
    int correctColourAndPosition = 0;
    int correctColourButWrongPosition = 0;

    const enum Colours PROCESSED_SOLUTION = -1;
    const enum Colours PROCESSED_INPUT = -2;

    for (int i = 0; i < amountOfColoursToGuess; i++) {
        if (userInputClone[i] == solutionClone[i]) {
            userInputClone[i] = PROCESSED_INPUT;
            solutionClone[i] = PROCESSED_SOLUTION;
            correctColourAndPosition++;
        }
    }

    for (int i = 0; i < amountOfColoursToGuess; i++) {
        if (userInputClone[i] != PROCESSED_INPUT) {
            for (int j = 0; j < amountOfColoursToGuess; j++) {
                if (userInputClone[i] == solutionClone[j]) {
                    solutionClone[j] = PROCESSED_SOLUTION;
                    correctColourButWrongPosition++;
                }
            }
        }
    }

    printf("Solution: %s - %s - %s - %s\n",
        getStringRepresentation(solution[0]),
        getStringRepresentation(solution[1]),
        getStringRepresentation(solution[2]),
        getStringRepresentation(solution[3])
    );

    printf("UserInput: %s - %s - %s - %s\n",
        getStringRepresentation(userInput[0]),
        getStringRepresentation(userInput[1]),
        getStringRepresentation(userInput[2]),
        getStringRepresentation(userInput[3])
    );

    printf("Clone:  %s - %s - %s - %s\n",
         getStringRepresentation(userInputClone[0]),
         getStringRepresentation(userInputClone[1]),
         getStringRepresentation(userInputClone[2]),
         getStringRepresentation(userInputClone[3])
    );

    gameScore->correctColourAndPosition = correctColourAndPosition;
    gameScore->correctColourButWrongPosition = correctColourButWrongPosition;
    return gameScore;
}
