#include "ConfigLoader.c"
#include "RandomColourGenerator.c"
#include "UserInputReader.c"
#include "GameScoreEvaluator.c"

enum GameStates {
    WON,
    LOST,
    PENDING
};


// TODO: Implement Mastermind
int main(int argc, char* argv[]) {
    const struct Config* config = readConfigFile();
    const enum Colours* randomColours = generateRandomColours(config->amountOfColoursToGuess);

    printf("Generated random colours %s - %s - %s - %s \n",
         getStringRepresentation(randomColours[0]),
         getStringRepresentation(randomColours[1]),
         getStringRepresentation(randomColours[2]),
         getStringRepresentation(randomColours[3])
         );

    enum GameState gameState = PENDING;
    int currentRound = 1;
    while (gameState == PENDING) {
        const enum Colours* userInput = readUserInput(config->amountOfColoursToGuess);
        const struct GameScore* gameScore = evaluateGameScore(userInput, randomColours, config->amountOfColoursToGuess);



        printf("GameScore: %d red - %d white \n", gameScore->correctColourAndPosition, gameScore->correctColourButWrongPosition);


        printf("User input: %s - %s - %s - %s \n",
            getStringRepresentation(userInput[0]),
            getStringRepresentation(userInput[0]),
            getStringRepresentation(userInput[1]),
            getStringRepresentation(userInput[2]));

        if (gameScore->correctColourAndPosition == config->amountOfColoursToGuess) {
            gameState = WON;
        }

        if (currentRound > config->roundsToPlay) {
            gameState = LOST;
        }
    }

    if (gameState == LOST) {
        printf("You lost");
    }

    if (gameState == WON) {
        printf("You Won");
    }


}

