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

void createRent(int userNif,int vehicleId,int numberOfDays, Rent **head);

void insertRent(Rent *newRent, Rent **head);

/* Save a given Rent List to a binnary file */
int saveRent(Rent *head);

/* Read from a binary file a Rent List */
int readRent(Rent **head);

#endif 
