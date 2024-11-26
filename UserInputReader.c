#include <stdio.h>

enum Colours* readUserInput(const int amountOfColours) {
    enum Colours* colours = malloc(amountOfColours * sizeof(enum Colours));
    for (int i = 0; i < amountOfColours; i++) {
        char userInput[10];
        printf("Enter Colour: ");
        scanf("%s", userInput);

        enum Colours colour = getColourFromStringRepresentation(userInput);

        if (colour == -1) {
            i--;
        } else {
            colours[i] = colour;
        }
    }
    return colours;
}
