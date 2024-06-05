#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablegen.h"
#include "generate.h"
#include "io.h"
#include "sort.h"

int main(int argc, char const *argv[])
{
    while(1) {
        system("clear");
        printf("TableGen Menu\n-------------\n1. Generate new table\n2. Exit\n\nSelection: ");
        int answer;
        scanf("%d", &answer);
        system("clear");

        //If user doesn't wanna proceed
        if(answer == 2) {
            printf("Goodbye and thanks for using TableGen\n");
            return 0;
        }
        //Want to generate
        char colmnNb[17];
        int nbRows;
        char outputFileName[30];
        if(answer == 1) {
            //Ask for columns
            printf("Column Options\n----------------\n1. User ID\t5. Phone Number\n2. First Name\t6. Email address\n3. Last Name\t7. SIN\n4. Country\t8. Password\n\nEnter column list (comma-separated, no spaces): ");
            scanf("%s", colmnNb);
            
            //Ask for rows
            printf("Enter row count (1 < n < 1M): ");
            scanf("%d", &nbRows);

            //Ask for output file name
            printf("Enter output file name (no suffix): ");
            scanf("%s", outputFileName);
        }
        printf("Summary of properties:\n Columns: %s\n Row count: %d\n File name: %s\n\n", colmnNb, nbRows, outputFileName);
        char fileSuffix[] = ".csv";
        strcat(outputFileName, fileSuffix);
        //create packages
        struct Package *rows = (struct Package*)malloc(nbRows * sizeof(struct Package));
        //generate data for packages
        createRows(rows, colmnNb, nbRows);

        //sort the packages
        char firstColumn = colmnNb[0];
        sortPackages(rows, nbRows, firstColumn);    

        //Generate csv file
        writeCSV(rows, nbRows, outputFileName, colmnNb);

        free(rows);
        printf("Table written successfully to %s\n\n", outputFileName);
        char proceed;
        printf("\nPress 'c' or 'C' to continue ");
        do{
            scanf("%c", &proceed);
        } while ( (proceed != 'c') && (proceed != 'C'));

    }

    return 0;
}
