#ifndef SORT_DOT_H
#define SORT_DOT_H

#include "tablegen.h"

void sortPackages(struct Package *rows, int nbRows, char firstColumn);

int compareSIN(const void *a, const void *b);

int compareFirstName(const void *a, const void *b);

int compareLastName(const void *a, const void *b);

int compareCountry(const void *a, const void *b);

int comparePhone(const void *a, const void *b);

int compareEmailAddress(const void *a, const void *b);

int comparePassword(const void *a, const void *b);

#endif