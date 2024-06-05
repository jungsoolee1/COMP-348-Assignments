#ifndef TABLEGEN_DOT_H
#define TABLEGEN_DOT_H

struct Package {
    int userID;
    char firstName[30];
    char lastName[30];
    char country[64];
    char phone[9];
    char emailAddress[100];
    int SIN;
    char password[17];
};

#endif