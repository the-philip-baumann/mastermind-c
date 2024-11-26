#include <stdlib.h>

struct Config {
    int roundsToPlay;
    int amountOfColoursToGuess;
};

struct Config* readConfigFile() {
    // TODO: Impl file read
    struct Config* config = (struct Config*) malloc(sizeof(struct Config));
    config->roundsToPlay = 12;
    config->amountOfColoursToGuess = 4;
    return config;
}