#include "Colours.c"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

enum Colours* generateRandomColours(const int amountOfColours) {
  int min = 0;
  int max = NUMBER_OF_COLOURS
  // use calculate malloc instead of regular malloc
  enum Colours* colours = malloc(amountOfColours * sizeof(enum Colours));
  srand(time(NULL));

  for (int i = 0; i < amountOfColours; i++) {
    const int random = rand() % (max - min) + min;
    colours[i] = (enum Colours) random;
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