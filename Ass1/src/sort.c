#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tablegen.h"
#include "generate.h"
#include "io.h"
#include "sort.h"

void sortPackages(struct Package *rows, int nbRows, char firstColumn){
    //firstName
    if(firstColumn == '2'){
        qsort(rows, nbRows, sizeof(struct Package), compareFirstName);
    }
    //lastName
    else if(firstColumn == '3'){
        qsort(rows, nbRows, sizeof(struct Package), compareLastName);
    }
    //country
    else if(firstColumn == '4'){
        qsort(rows, nbRows, sizeof(struct Package), compareCountry);
    }  
    //phone
    else if(firstColumn == '5'){
        qsort(rows, nbRows, sizeof(struct Package), comparePhone);
    }
    //emailAddress
    else if(firstColumn == '6'){
        qsort(rows, nbRows, sizeof(struct Package), compareEmailAddress);
    }
    //SIN
    else if(firstColumn == '7'){
        qsort(rows, nbRows, sizeof(struct Package), compareSIN);
    }
    //password
    else if(firstColumn == '8'){
        qsort(rows, nbRows, sizeof(struct Package), comparePassword);
    }
}

int compareSIN(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    if(p1->SIN < p2->SIN) {
        return -1;
    }
    else if (p1->SIN > p2->SIN) {
        return +1;
    }
    else
        return 0;
}

int comparePhone(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    char phone[8] = "\0", phone2[8] = "\0";
    for(int i = 0; i < 9; i++){
        if(i != 3) {
            strncat(phone, &p1->phone[i], 1);
            strncat(phone2, &p2->phone[i], 1);
        }
    }
    int realPhone1 = atoi(phone);
    int realPhone2 = atoi(phone2);
    if(realPhone1 < realPhone2) {
        return -1;
    }
    else if (realPhone1 > realPhone2) {
        return +1;
    }
    else
        return 0;

}

int compareFirstName(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    return strcmp(p1->firstName, p2->firstName);
}

int compareLastName(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    return strcmp(p1->lastName, p2->lastName);
}

int compareCountry(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    return strcmp(p1->country, p2->country);
}

int compareEmailAddress(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    return strcmp(p1->emailAddress, p2->emailAddress);
}

int comparePassword(const void *a, const void *b) {
    const struct Package *p1 = (struct Package *)a;
    const struct Package *p2 = (struct Package *)b;
    return strcmp(p1->password, p2->password);
}