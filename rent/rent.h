/*****************************************************************/ /**
 * @file   Rent.h
 * @brief  Library for managing Vehicles
 * 
 * @author Diogo
 * @date   March 2023
 *********************************************************************/
#include <stdio.h>

#ifndef RENTSLIB
#define RENTSLIB
#define RENTFILENAME "./rent/rent.bin"


typedef struct Rent
{
    int id; 
    int userNif;
    int vehicleId;
    int numberOfDays;
    struct Rent *next;
} Rent;

/* Create a new rent struct and return it */
Rent* createRent(int userNif, int vehicleId, int numberOfDays);

/*Insert one given rent to a rentList*/
void insertRent(Rent *newRent, Rent **head);

/* Display All Rents from a list */
void displayRentsList(Rent *lst);

/* Display the info of one user */
void showRent(Rent *rent);

/* Save a given Rent List to a binnary file */
int saveRent(Rent *head);

/* Read from a binary file a Rent List */
int readRent(Rent **head);

#endif 
