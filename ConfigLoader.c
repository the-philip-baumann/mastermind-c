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


void printConfig() {
    FILE* configFile = fopen(FILENAME, "rb");
    if (!configFile) {
        perror("Failed to open config file (config.dat)");
        return;
    }

    struct Config* config = malloc(sizeof(struct Config));
    fread(config, sizeof(struct Config), 1, configFile);
    fclose(configFile);

    printf("Rounds: %d - Amount of Colours to guess: %d \n", config->roundsToPlay, config->amountOfColoursToGuess);

    free(config);
}