#pragma once

#include <stdio.h>

#define CSV_FIELD_LENGTH 1024

#include "udt.h"

char *csv_retrieveField(FILE *filePointer);
void csv_saveToFile(const char *fileName, UDT source);
int csv_saveToUdt(const char *fileName, UDT *destination);
