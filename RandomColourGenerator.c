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
    printf("random colour number %d: \n", random);
    colours[i] = (enum Colours) random;
  }

  return colours;
}