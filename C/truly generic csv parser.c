char *csv_retrieveField(FILE *filePointer) {

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