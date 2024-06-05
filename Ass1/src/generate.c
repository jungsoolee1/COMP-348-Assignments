#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tablegen.h"
#include "generate.h"
#include "io.h"
#include "sort.h"

int hello = 2;

void createRows(struct Package *rows, char colmnNb[], int nbRows) {
    
    //generate random seed
    time_t seed;
    hello = 4;
    srand((unsigned)time(&seed));

    char number;
    int phoneIndex[10] = {398, 270, 925, 867, 209, 429, 908, 997,444, 219};
    
    //to check in case email cannot be generated due to first name or last name missing
    rows[0].firstName[0] = '!';
    rows[0].lastName[0] = '!';
    int toEmail = 0;
    
    for (int index = 0; index <= 16; index++) {
        number = colmnNb[index];

        //do email if conditions are met
        if (number == '\0' && toEmail == 1) {
            number = '6';
        }

        //check if char is null char or a comma
        if (number == ',')
            continue;
        else if(number == '\0')
            break;
        //User ID
        else if (number == '1') {
            for (int i = 0; i < nbRows; i++) {
                rows[i].userID = i+1;
            }
        }
        //First Name
        else if (number == '2') {
            int nbOfFirstNames = 1000;
            char firstNameArray[1000][70];
            char fileName[] = "TextData/first_names.txt";
            transferNames(firstNameArray, nbOfFirstNames, fileName);
            for (int i = 0; i < nbRows; i++) {
                strcpy(rows[i].firstName, firstNameArray[rand() % nbOfFirstNames]);
            }
        }
        //Last Name
        else if (number == '3') {
            int nbOfLastNames = 1000;
            char lastNameArray[1000][70];
            char fileName[] = "TextData/last_names.txt";
            transferNames(lastNameArray, nbOfLastNames, fileName);
            for (int i = 0; i < nbRows; i++) {
                strcpy(rows[i].lastName, lastNameArray[rand() % nbOfLastNames]);
            }
        }
        //Country
        else if (number == '4') {
            int nbOfCountries = 195;
            char countrArray[195][70];
            char fileName[] = "TextData/countries.txt";
            transferNames(countrArray, nbOfCountries, fileName);
            for (int i = 0; i < nbRows; i++) {
                strcpy(rows[i].country, countrArray[rand() % nbOfCountries]);
            }
        }
        //Phone
        else if (number == '5') {
            for (int i = 0; i < nbRows; i++) {
                int indexChosen = phoneIndex[rand() % 10];
                sprintf(rows[i].phone, "%d", indexChosen);
                char hyphen[] = "-";
                strcat(rows[i].phone, hyphen);
                int phoneLine[4];
                for(int count = 0; count < 4; count++) {
                    phoneLine[count] = rand() % 10;
                    char phoneInteger[2];
                    sprintf(phoneInteger, "%d", phoneLine[count]);
                    strcat(rows[i].phone, phoneInteger);
                }
            }
        }
        //Email address
        else if (number == '6') {
            if (rows[0].firstName[0] == '!' || rows[0].lastName[0] == '!') {
                toEmail = 1;
                continue;
            }
            int nbSuffixes = 100;
            char suffixArray[100][70];
            char fileName[] = "TextData/email_suffixes.txt";
            transferNames(suffixArray, nbSuffixes, fileName);
            for (int i = 0; i < nbRows; i++) {
                rows[i].emailAddress[0] = rows[i].firstName[0];
                rows[i].emailAddress[1] = '\0';
                strcat(rows[i].emailAddress, rows[i].lastName);
                char emailSymbol = '@';
                strncat(rows[i].emailAddress, &emailSymbol, 1);
                strcat(rows[i].emailAddress, suffixArray[rand() % nbSuffixes]);
                for(int count = 0; rows[i].emailAddress[count]; count++){
                    rows[i].emailAddress[count] = tolower(rows[i].emailAddress[count]);
                }
            }
            if (toEmail == 1) {
                break;
            }
        }
        //SIN
        else if (number == '7') {
            for(int i = 0; i < nbRows; i++) {
                rows[i].SIN = rand() % 900000000 + 100000000;
            }
        }
        //Password
        else if (number == '8') {
            for(int i = 0; i < nbRows; i++) {
                rows[i].password[0] = '\0';
                int length = rand() % 11 + 6;
                for(int count = 0; count < length; count++){
                    int asciiNb;
                    do {
                        asciiNb = rand() % 94 + 33;
                    }
                    while(asciiNb == 44);
                    char asciiChar = asciiNb;
                    strncat(rows[i].password, &asciiChar, 1);
                }
            }
        }
    }
}