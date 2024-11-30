#include "ConfigLoader.c"
#include "RandomColourGenerator.c"
#include "UserInputReader.c"
#include "GameScoreEvaluator.c"

enum GameState {
    WON,
    LOST,
    PENDING
};

int main(int argc, char* argv[]) {
    printf("Welcome to masterminds!\n"
        "Your goal is to guess the correct colours in correct order.\n"
        "These are the colours included in the game:\n");
    printAllColours();

    struct Config* initialConfig = malloc(sizeof(struct Config));
    initialConfig->roundsToPlay = 12;
    initialConfig->amountOfColoursToGuess = 4;
    
    writeConfigFile(initialConfig); //only write if not set by user
    free(initialConfig);

    printConfig();
    const struct Config* config = readConfigFile();

    const enum Colours* randomColours = generateRandomColours(config->amountOfColoursToGuess);
    
    printf("generated random colours");
    for (int i = 0; i < config->amountOfColoursToGuess; ++i) {
        printf(" %s", getStringRepresentation(randomColours[i]));
        if (i < config->amountOfColoursToGuess - 1) {
            printf(" -");
        }
    }
    printf("\n\n");

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

        if (gameState == PENDING && currentRound >= config->roundsToPlay) {
            gameState = LOST;
        }

        if (gameState == PENDING) {
            printf("your current score ------------------- \n");
            printf("red (correct colour and position): %d\n", gameScore->correctColourAndPosition);
            printf("white (correct colour but wrong position): %d\n", gameScore->correctColourButWrongPosition);
            printf("rounds left: %d", config->roundsToPlay - currentRound);
            printf("\n");
            ++currentRound;
        }
    }

    if (gameState == WON) {
        printf("you have found the correct solution!\n");
        printf("the solution: ");
        for (int i = 0; i < config->amountOfColoursToGuess; i++) {
            printf("%s ", getStringRepresentation(randomColours[i]));
            if (i < config->amountOfColoursToGuess - 1) printf("- ");
        }
        printf("\n");
    }

    if (gameState == LOST) {
        printf("game over. unfortunately you have lost!\n");
        printf("the solution would have been: ");
        for (int i = 0; i < config->amountOfColoursToGuess; i++) {
            printf("%s ", getStringRepresentation(randomColours[i]));
            if (i < config->amountOfColoursToGuess - 1) printf("- ");
        }
        printf("\n");
    }

}

