#define NUMBER_OF_COLOURS 8
#include <ctype.h>
#include <string.h>

enum Colours {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    BLACK,
    ORANGE,
    PURPLE
};

char *getStringRepresentation(enum Colours colour) {
    switch (colour) {
        case RED: return "RED";
        case GREEN: return "GREEN";
        case BLUE: return "BLUE";
        case YELLOW: return "YELLOW";
        case WHITE: return "WHITE";
        case BLACK: return "BLACK";
        case ORANGE: return "ORANGE";
        case PURPLE: return "PURPLE";
        default: return "UNKNOWN";
    }
}

void printAllColours() {
    for (int i = 0; i <= PURPLE; i++) {
        printf("%s", getStringRepresentation((enum Colours)i));
        if (i < PURPLE) {
            printf(" - ");
        }
    }
    printf("\n"); // Newline at the end
}
// Returns -1 if input is not a valid colour
enum Colours getColourFromStringRepresentation(char *input) {
    char clone[10];
    strcpy(clone, input);
    for (int i = 0; clone[i]; i++) {
        clone[i] = toupper(clone[i]);
    }

    if (strcmp(clone, "RED") == 0) return RED;
    if (strcmp(clone, "GREEN") == 0) return GREEN;
    if (strcmp(clone, "BLUE") == 0) return BLUE;
    if (strcmp(clone, "YELLOW") == 0) return YELLOW;
    if (strcmp(clone, "WHITE") == 0) return WHITE;
    if (strcmp(clone, "BLACK") == 0) return BLACK;
    if (strcmp(clone, "ORANGE") == 0) return ORANGE;
    if (strcmp(clone, "PURPLE") == 0) return PURPLE;

    return -1;
}
