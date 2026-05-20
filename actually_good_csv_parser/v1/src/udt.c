#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/udt.h"

bool udt_isValid(const UDT toCheck) {
    return strlen(toCheck.name) > 0 && toCheck.age >= 0;
}

bool udt_isEmpty(const UDT toCheck) {
    return toCheck.name[0] == '\0' && toCheck.age == 0;
}

bool udt_csv_saveToFile(FILE *fp, const UDT source) {
    if(!fp || !udt_isValid(source)) {
        return false;
    }

    fprintf(fp, "%d,%s\n", source.age, source.name);

    return true;
}

bool udt_csv_saveToUdt(UDT *destination, const char *field) {
    static int currentField = 0;

    if(!destination || !field) {
        currentField = 0;
        return false;
    }

    switch(currentField) {
        case 0:
            destination->age = atoi(field);
            break;

        case 1:
            strncpy(destination->name, field, sizeof(destination->name)-1);
            destination->name[sizeof(destination->name)-1] = '\0';
            break;

        default:
            currentField = -1;
            return false;
    }

    ++currentField;

    if(currentField >= 2) {
        currentField = 0;
        return true;
    }

    return false;
}
