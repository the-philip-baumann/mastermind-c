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

enum FileReadCode writeConfigFile(struct Config* config) {
    FILE* configFile = fopen(FILENAME, "wb");
    if (!configFile) {
        perror("Failed to open config file (config.dat)");
        return FAILED;
    }

    if (fwrite(config, sizeof(struct Config), 1, configFile) != 1) {
        perror("Failed to write to config file");
        fclose(configFile);
        return FAILED;
    }

    fclose(configFile);

    return SUCCESSFUL;
}

struct Config* defaultConfig() {
    struct Config* defaultConfig = malloc(sizeof(struct Config));
    defaultConfig->roundsToPlay = 12;
    defaultConfig->amountOfColoursToGuess = 4;
    writeConfigFile(defaultConfig);
    return defaultConfig;
}

struct Config* readConfigFile() {
    FILE* configFile = fopen(FILENAME, "rb");

    if (!configFile) {
        return defaultConfig();
    }

    struct Config* config = malloc(sizeof(struct Config));
    if (fread(config, sizeof(struct Config), 1, configFile) != 1) {
        perror("Error reading config file");
        free(config);
        fclose(configFile);
        return defaultConfig();
    }

    fclose(configFile);

    return config;
}

void adjustUserConfiguration() {
    int roundsToPlay, amountOfColoursToGuess;
    printf("\nSet amount of rounds you want to play: ");
    scanf("%d", &roundsToPlay);
    printf("Set amount of colours you want to guess: ");
    scanf("%d", &amountOfColoursToGuess);

    if (roundsToPlay > 20 || roundsToPlay < 1 ||
        amountOfColoursToGuess < 1 || amountOfColoursToGuess > 8) {
        printf("You have entered invalid configuration, default configuration is used");
        roundsToPlay = 12;
        amountOfColoursToGuess = 4;
    }

    struct Config* userConfig = malloc(sizeof(struct Config));
    userConfig->roundsToPlay = roundsToPlay;
    userConfig->amountOfColoursToGuess = amountOfColoursToGuess;

    writeConfigFile(userConfig);
    free(userConfig);
}

void printConfig() {
    FILE* configFile = fopen(FILENAME, "rb");
    if (!configFile) {
        perror("Failed to open config file (config.dat)");
        return;
    }

    struct Config* config = malloc(sizeof(struct Config));
    fread(config, sizeof(struct Config), 1, configFile);
    fclose(configFile);

    printf("\nRounds: %d - Amount of Colours to guess: %d \n\n", config->roundsToPlay, config->amountOfColoursToGuess);

    free(config);
}