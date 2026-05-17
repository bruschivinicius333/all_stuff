#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CSV_FIELD_LENGTH 100
#define FILE_NAME "test.csv"

int csv_next(FILE *filePointer, char *output, const size_t outputLength) {

    if(outputLength < 1) return 1;

    if(!filePointer) {
        output[0] = '\0';
        return 1;
    }

    char retrievedChar = 0;
    char field[CSV_FIELD_LENGTH] = {0};


    while(1) {
        retrievedChar = getc(filePointer);

        if(retrievedChar == EOF) {
            output[0] = '\0';
            return 1;
        }
        if(isalnum(retrievedChar)) {
            break;
        }
    }
    ungetc(retrievedChar, filePointer);

    for(int iField = 0; (retrievedChar = getc(filePointer)) && (isalnum(retrievedChar) || retrievedChar == ' '); ++iField) {
        field[iField] = retrievedChar;
    }

    char *toRemove = 0;
    if(*(toRemove = &field[strlen(field)-1]) == '\n') {
        *toRemove = '\0';
    }

    snprintf(output, outputLength, "%s", field);
    return 0;
}
