#include <stdlib.h>
#include <string.h>
#include "rent.h"

/* Global variable to store the next available rent ID */
int nextRentId = 1;

/* Generate the next available rent ID */
int getNextRentId()
{
    return nextRentId++;
}

/* Display All Rents from a list */
void displayRentsList(Rent *lst)
{
    Rent *aux = lst;
    while (aux != NULL)
    {
        showRent(aux);
        aux = aux->next;
    }
    putchar('\n');
}

/* Create a new rent struct and return it */
Rent* createRent(int userNif, int vehicleId, int numberOfDays)
{
    Rent *newRent = malloc(sizeof(Rent));

    if (newRent == NULL)
    {
        printf("Error: Unable to allocate memory for rent\n");
        return newRent;
    }

    /* Set the ID for the new rent */
    newRent->id = getNextRentId();

    newRent->userNif = userNif;
    newRent->vehicleId = vehicleId;
    newRent->numberOfDays = numberOfDays;

    /* Set the next pointer to NULL */
    newRent->next = NULL;
    return newRent;
}

/*Insert one given rent to a rentList*/
void insertRent(Rent *newRent, Rent **head)
{
    if (*head == NULL)
    {
        *head = newRent;
        newRent->next = NULL;
    }
    else
    {
        newRent->next = *head;
        *head = newRent;
    }
}

/* Save vehiclelist into the rentbinary file */
int saveRent(Rent*head)
{
    FILE *file;
    Rent *currentRent= head;

    file = fopen(RENTFILENAME, "wb");
    if (file == NULL)
    {
        return 0; // Error opening file
    }

    // Write the vehicles to the file
    while (currentRent!= NULL)
    {
        if (fwrite(currentRent, sizeof(Rent), 1, file) != 1)
        {
            fclose(file);
            return 0; // Error writing to file
        }
        currentRent= currentRent->next;
    }
    fclose(file);
    return 1; // Success
}

/* Read the rentbinary file */
int readRent(Rent**head)
{
    FILE *file;
    Rent *tempRent;
    Rent *newRent;

    file = fopen(RENTFILENAME, "rb");
    if (file == NULL)
    {
        return 0; // File not found
    }

    while (1)
    {
        newRent= (Rent*)malloc(sizeof(Rent));
        if (fread(newRent, sizeof(Rent), 1, file) != 1)
        {
            free(newRent);
            break;
        }

        insertRent(newRent, head);
    }

    fclose(file);
    return 1; // Rentread successfully
}


/* Display the info of one user */
void showRent(Rent *rent)
{
    printf("---------------Start of Rent--------------\n");
    printf("User Nif : %i \n", rent->userNif);
    printf("Vehicle Id : %i \n", rent->vehicleId);
    printf("Number of days : %i \n", rent->numberOfDays);
    printf("---------------END of User-----------------\n");
}

