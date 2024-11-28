#include <stdio.h>
#include <stdlib.h>

#define FILENAME "./config.dat"

struct Config {
    int roundsToPlay;
    int amountOfColoursToGuess;
};

enum FileReadCode {
    SUCCESSFUL,
    FAILED
};

struct Config* readConfigFile() {
    // Mode "wb" -> "write binary"
    FILE* configFile = fopen(FILENAME, "rb");

    if (!configFile) {
        perror("Failed to open config file (config.dat) using default config");
        struct Config* config = malloc(sizeof(struct Config));
        config->roundsToPlay = 12;
        config->amountOfColoursToGuess = 4;
        return config;
    }

    struct Config* config = malloc(sizeof(struct Config));
    fread(config, sizeof(struct Config), 1, configFile);
    fclose(configFile);

    return config;
}

enum FileReadCode writeConfigFile(struct Config* config) {
    // TODO: Clear up basic implementation
    if (remove(FILENAME) == 0) {
        printf("Successfuly removed File: '%s'\n", FILENAME);
    } else {
        printf("Failed to remove File '%s'\n", FILENAME);
        exit(1);
    }

    // Mode "rb" -> "read binary"
    FILE* configFile = fopen(FILENAME, "wb");
    if (!configFile) {
        perror("Failed to open config file (config.dat)");
        return FAILED;
    }

    printf("Data to save: %d - %d \n", config->roundsToPlay, config->amountOfColoursToGuess);

    // TODO: Fix content is not being written to file
    fwrite(config, sizeof(struct Config), 1, configFile);
    fclose(configFile);

    return SUCCESSFUL;
}


void printConfig() {
    FILE* configFile = fopen(FILENAME, "wb");
    if (!configFile) {
        perror("Failed to open config file (config.dat)");
    }

    struct Config* config = malloc(sizeof(struct Config));
    fread(config, sizeof(struct Config), 1, configFile);
    fclose(configFile);

    printf("Rounds: %d - Amount of Colours to guess: %d \n", config->roundsToPlay, config->amountOfColoursToGuess);

    free(config);
}