/*****************************************************************/ /**
 * @file   Vehicles.h
 * @brief  Library for managing Vehicles
 * 
 * @author Diogo
 * @date   March 2023
 *********************************************************************/
#include <stdio.h>

#ifndef VEHICLESLIB
#define VEHICLESLIB
#define MAX_LINE_LENGTH 1000
#define NAME_LENGHT 100
#define LOCATION_LENGHT 100
#define VEHICLEFILENAME "./vehicle/vehicle.bin"
#define VEHICLECSVFILENAME "./vehicle/vehicle.csv"


typedef struct Vehicle
{
    int id; 
    char name[NAME_LENGHT];
    float battery;
    float rentCost;
    char location[LOCATION_LENGHT]; 
    struct Vehicle *next;
} Vehicle;

/* Create an instance of a vehicle struct and return it*/
Vehicle *createVehicle();

/* Given a id returns a vehicle if it is exist */
Vehicle *searchVehicleById(int id, Vehicle *vehicles);

/* Display the info of one vehicle */ 
void showVehicle(Vehicle *vehicle);

/* Insert one given vehicle to a vehicleList */
void insertVehicle(Vehicle *newVehicle,Vehicle **head);

/* Edit one given vehicle */
void editVehicle(Vehicle **vehicle);

/*  If vehicle exist in the list return 1 
    else return 0 
 */
int vehicleExists(int id, Vehicle *vehicle);

/* Create an Vehicle and add it to an given list */
int createVehicleToList(Vehicle **head);

/* Receive an linked list and the number of items it hold and return an array */
Vehicle **getVehicleFromListIntoArray(int n, Vehicle *vehicleList);

/* Count the elements of vehicle linked list */
int countVehiclesFromList(Vehicle *sortedList);

/* List all vehicles from a location given by User */
void listVehiclesByLocation(Vehicle *vehicleList);

/* -------- Functions to manage Vehicle list -------- */

/* Compares two vehicles based on their battery level */
int compareVehiclesByBattery(const void *a, const void *b);

/* Give all vehicles from on location received */
void getVehiclesByLocation(Vehicle *head, char *location);

/* Display All Vehicles from a list */
void displayVehiclesList(Vehicle *lst);

/* Edit one Vehicle from a given vehicleList searched by id  */
int editVehicleById(Vehicle **head);

/* Delete one Vehicle from a given vehicleList searched by id  */
int deleteVehicle(Vehicle **head); 

/* Save a given vehicleList to a binnary file */
int saveVehicle(Vehicle *head);

/* Read from a binary file a vehicle List */
int readVehicle(Vehicle **head);

/* Read vehicle data from a CSV file and add it to the vehicle linked list */
void readVehicleDataFromFile(Vehicle **head);

/* Sort an list of vehicle by batery */
void listVehiclesSortedByBattery(Vehicle *vehicleList);

#endif
