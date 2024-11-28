#include <stdio.h>

enum Colours* readUserInput(const int amountOfColours) {
    enum Colours* colours = malloc(amountOfColours * sizeof(enum Colours));

    for (int i = 0; i < amountOfColours; i++) {
        char userInput[10];
        printf("enter colour %d out of %d: ", i + 1, amountOfColours);
        scanf("%s", userInput);
        enum Colours colour = getColourFromStringRepresentation(userInput);
        if (colour == -1) {
            i--;
            printf("invalid colour try another colour");
        } else {
            colours[i] = colour;
        }
    }

    printf("your guess in this round is:");
    for (int i = 0; i < amountOfColours; ++i) {
        printf(" %s", getStringRepresentation(colours[i]));
        if (i < amountOfColours - 1) {
            printf(" -");
        }
    }
    printf("\n\n");

    return colours;
}
