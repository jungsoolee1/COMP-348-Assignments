#ifndef IO_DOT_H
#define IO_DOT_H

#include "tablegen.h"

void transferNames(char dataRows[][70], int nbOfNames, char fileName[]);

void writeCSV(struct Package *rows, int nbRows, char outputFileName[], char colmnNb[]);

#endif