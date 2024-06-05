#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tablegen.h"
#include "generate.h"
#include "io.h"
#include "sort.h"

//to transfer names
void transferNames(char dataRows[][70], int nbOfNames, char fileName[]){
    FILE *file;
    file = fopen(fileName, "r");
    for (int i = 0; i < nbOfNames; i++){
        char valueName[70];
        fgets(valueName, 68, file);
        char realValueName[70];
        for(int count = 0; count < 70; count++){
            if(valueName[count] == '\n'){
                realValueName[count] = '\0';
                break;
            }
            else {
                realValueName[count] = valueName[count];
            }
        }
        strcpy(dataRows[i], realValueName);
    }
    fclose(file);
}

void writeCSV(struct Package *rows, int nbRows, char outputFileName[], char colmnNb[]) {
    char number;
    //overwrite or create file
    FILE *file;
    file = fopen(outputFileName, "wt");

    for(int index = 0; index <= 16; index++) {
        number = colmnNb[index];
        //check if char is null char or a comma
        if (number == ',')
            fputs(",", file);
        else if(number == '\0') {
            fputs("\n", file);
            break;
        }
        //User ID
        else if (number == '1') {
            fputs("User ID", file);
        }
        //First Name
        else if (number == '2') {
           fputs("First name", file);
        }
        //Last Name
        else if (number == '3') {
            fputs("Last name", file);
        }
        //Country
        else if (number == '4') {
            fputs("Country", file);
        }
        //Phone
        else if (number == '5') {
            fputs("Phone Number", file);
        }
        //Email address
        else if (number == '6') {
            fputs("Email address", file);
        }
        //SIN
        else if (number == '7') {
            fputs("SIN", file);
        }
        //Password
        else if (number == '8') {
            fputs("Password", file);
        }
    }
    for(int i = 0; i < nbRows; i++) {
        for(int count = 0; count <= 16; count++) {
            number = colmnNb[count];
            //check if char is null char or a comma
            if (number == ',')
                fputs(",", file);
            else if(number == '\0') {
                fputs("\n", file);
                break;
            }
            //User ID
            else if (number == '1') {
                char IDString[10];
                sprintf(IDString, "%d", rows[i].userID);
                fputs(IDString, file);
            }
            //First Name
            else if (number == '2') {
                fputs(rows[i].firstName, file);
            }
            //Last Name
            else if (number == '3') {
                fputs(rows[i].lastName, file);
            }
            //Country
            else if (number == '4') {
                fputs(rows[i].country, file);
            }
            //Phone
            else if (number == '5') {
                fputs(rows[i].phone, file);
            }
            //Email address
            else if (number == '6') {
                fputs(rows[i].emailAddress, file);
            }
            //SIN
            else if (number == '7') {
                char SINString[11];
                sprintf(SINString, "%d", rows[i].SIN);
                fputs(SINString, file);
            }
            //Password
            else if (number == '8') {
                fputs(rows[i].password, file);
            }
        }
    }

    fclose(file);
}