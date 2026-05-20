#pragma once

typedef struct {
    int age;
    char name[256];
} Person;

#define UDT Person

bool udt_isValid(const UDT toCheck);
bool udt_isEmpty(const UDT toCheck);

bool udt_csv_saveToFile(FILE *fp, const UDT source); // underlines for namespaces
bool udt_csv_saveToUdt(UDT *destination, const char *field);
