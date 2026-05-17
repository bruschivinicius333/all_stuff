#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    retrievedChar = getc(filePointer);
    if(retrievedChar == EOF || retrievedChar == '\n') {
        output[0] = '\0';
        return 1;
    }
    ungetc(retrievedChar, filePointer);

    for(int iField = 0; (retrievedChar = getc(filePointer)) && (retrievedChar != ',' && retrievedChar != EOF); ++iField) {
        field[iField] = retrievedChar;
    }

    char *toRemove = 0;
    if(*(toRemove = &field[strlen(field)-1]) == '\n') {
        *toRemove = '\0';
    }

    snprintf(output, sizeof(outputLength), "%s", field);
    return 0;
}

int main() {
    
    FILE *fp = NULL;

    fp = fopen(FILE_NAME, "w");
    fprintf(fp, "%s", "banana,apple,mango,\n");
    fclose(fp);

    fp = fopen(FILE_NAME, "r+");
    
    if(!fp) {
        printf("Ue\n");
        exit(EXIT_FAILURE);
    }
    
    char toPrint[CSV_FIELD_LENGTH] = {0};
    
    while(!csv_next(fp, toPrint, sizeof(toPrint))) {
        printf("%s\n", toPrint);
    }
    
    fclose(fp);
    
    return 0;
}
