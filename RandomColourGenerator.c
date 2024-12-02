#include "Colours.c"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

enum Colours* generateRandomColours(const int amountOfColours) {
    enum Colours allColours[NUMBER_OF_COLOURS];
    for (int i = 0; i < NUMBER_OF_COLOURS; i++) {
        allColours[i] = (enum Colours) i;
    }

    srand(time(NULL));

    for (int i = NUMBER_OF_COLOURS - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        enum Colours temp = allColours[i];
        allColours[i] = allColours[j];
        allColours[j] = temp;
    }

    enum Colours* colours = malloc(amountOfColours * sizeof(enum Colours));
    if (!colours) {
        perror("Failed to allocate memory for colours");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < amountOfColours; i++) {
        colours[i] = allColours[i];
    }

    return colours;
}

void printGeneratedColours(const struct Config *config, const enum Colours *randomColours)
{
    for (int i = 0; i < config->amountOfColoursToGuess; ++i)
    {
        printf(" %s", getStringRepresentation(randomColours[i]));
        if (i < config->amountOfColoursToGuess - 1)
        {
            printf(" -");
        }
    }
}