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

    char workflow[1];
    printf("\nType any character + 'Enter' if you want to start the game!");
    printf("\nType '1' if you want to adjust the game configuration: ");
    scanf("%s", workflow);

    if (workflow[0] == '1') {
        adjustUserConfiguration();
    }

    const struct Config* config = readConfigFile();
    printConfig();

    const enum Colours* randomColours = generateRandomColours(config->amountOfColoursToGuess);

    enum GameState gameState = PENDING;
    int currentRound = 1;
    while (gameState == PENDING) {
        const enum Colours* userInput = readUserInput(config->amountOfColoursToGuess);
        const struct GameScore* gameScore = evaluateGameScore(userInput, randomColours, config->amountOfColoursToGuess);

        if (gameScore->correctColourAndPosition == config->amountOfColoursToGuess) {
            gameState = WON;
        }

        if (gameState == PENDING && currentRound >= config->roundsToPlay) {
            gameState = LOST;
        }

        if (gameState == PENDING) {
            printf("------------------- your current score -------------------\n");
            printf("black (correct colour and position): %d\n", gameScore->correctColourAndPosition);
            printf("white (correct colour but wrong position): %d\n", gameScore->correctColourButWrongPosition);
            printf("rounds left: %d", config->roundsToPlay - currentRound);
            printf("\n----------------------- keep going -----------------------\n");
            ++currentRound;
        }
    }

    if (gameState == WON) {
        printf("\nyou have found the correct solution!\n");
        printf("the solution: ");
        printGeneratedColours(config, randomColours);
        printf("\n");
    }

    if (gameState == LOST) {
        printf("game over. unfortunately you have lost!\n");
        printf("the solution would have been: ");
        printGeneratedColours(config, randomColours);
        printf("\n");
    }

}