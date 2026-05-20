#include "../include/csv.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *csv_retrieveField(FILE *filePointer) { // completely GENERIC, as every function should be: completely detached from underlying data-types

    static char field[CSV_FIELD_LENGTH] = {0};

    if(!filePointer) return 0;

    char retrievedChar = 0;

    while(1) {
        retrievedChar = getc(filePointer);

        if(retrievedChar == EOF) return 0;

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

    return field;
}

void csv_saveToFile(const char *fileName, UDT source) { // Now GENERIC! (aka detached from whatever UDT is underneath)
    FILE *mainFile = fopen(fileName, "w");

    if(!mainFile || udt_isValid(source)) {
        fprintf(stderr, "ERROR in csv_save\n");
        exit(EXIT_FAILURE);
    }

    udt_csv_saveToFile(mainFile, source); // a UDT doesn't deserve the right to save it wherever it feels to.

    fclose(mainFile);
}

int csv_saveToUdt(const char *fileName, UDT *destination) { // GENERIC
    FILE *mainFile = fopen(fileName, "r");

    if(!mainFile) return 1;

    if(mainFile) {
        char *field = 0;
        
        while((field = csv_retrieveField(mainFile))) {

            udt_csv_saveToUdt(destination, field); // pass by value when source, pass by pointer when destination
            
        }
    }

    fclose(mainFile);
    return 0;
}
