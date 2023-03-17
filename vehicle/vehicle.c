#include <stdlib.h>
#include <string.h>
#include "vehicle.h"

/* Display All Vehicles from a list */
void displayVehiclesList(Vehicle *lst)
{
    Vehicle *aux = lst;
    while (aux != NULL)
    {
        showVehicle(aux);
        aux = aux->next;
    }
    putchar('\n');
}

/* Delete one Vehicle from a given vehicleList searched by id  */
int deleteVehicle(Vehicle **head)
{
    Vehicle *temp = *head;
    Vehicle *prev;
    int id;
    printf("\n What vehicle you want to Delete ? (Search by id) \n");
    scanf("%i", &id);

    // If head node itself holds the matching id
    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        return 1;
    }

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    // If id was not found in the linked list
    if (temp == NULL)
    {
        printf("Vehicle with id %d not found\n", id);
        return 0;
    }

    // Unlink the node with the matching id
    prev->next = temp->next;

    // Free the memory occupied by the node with the matching id
    free(temp);
    return 1;
}

/* Edit one Vehicle from a given vehicleList searched by id  */
int editVehicleById(Vehicle **head)
{
    Vehicle *current = NULL;
    int idToEdit;

    printf("\n What vehicle you want to edit ? (Search by id) \n");
    scanf("%i", &idToEdit);

    current = searchVehicleById(idToEdit, *head);
    if (current != NULL)
    {
        editVehicle(&current);
        return 1;
    }
    return 0;
}

/* Save vehiclelist into the vehicle binary file */
int saveVehicle(Vehicle *head)
{
    FILE *file;
    Vehicle *currentVehicle = head;

    file = fopen(VEHICLEFILENAME, "wb");
    if (file == NULL)
    {
        return 0; // Error opening file
    }

    // Write the vehicles to the file
    while (currentVehicle != NULL)
    {
        if (fwrite(currentVehicle, sizeof(Vehicle), 1, file) != 1)
        {
            fclose(file);
            return 0; // Error writing to file
        }
        currentVehicle = currentVehicle->next;
    }
    fclose(file);
    return 1; // Success
}

/* Read the vehicle binary file */
int readVehicle(Vehicle **head)
{
    FILE *file;
    Vehicle tempVehicle;
    Vehicle *newVehicle;

    file = fopen(VEHICLEFILENAME, "rb");
    if (file == NULL)
    {
        return 0; // File not found
    }

    while (1)
    {
        newVehicle = (Vehicle *)malloc(sizeof(Vehicle));
        if (fread(newVehicle, sizeof(Vehicle), 1, file) != 1)
        {
            free(newVehicle);
            break;
        }

        insertVehicle(newVehicle, head);
    }

    fclose(file);
    return 1; // Vehicle read successfully
}

/* Create an Vehicle and add it to an given list */
int createVehicleToList(Vehicle **head)
{
    /* Create vehicles */
    Vehicle *newVehicle = createVehicle();
    /* Validate if vehicle already exist */
    if (vehicleExists(newVehicle->id, *head) != 1)
    {
        insertVehicle(newVehicle, head);
        return 1;
    }
    else
    {
        free(newVehicle);
        return 0;
    }
}

/* Read vehicle data from a CSV file and add it to the vehicle linked list */
void readVehicleDataFromFile(Vehicle **head)
{
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *token;
    Vehicle *newVehicle;

    fp = fopen(VEHICLECSVFILENAME, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file %s\n", VEHICLECSVFILENAME);
        return;
    }
    fgets(line, MAX_LINE_LENGTH, fp); // Read first line (header)

    /* Read each line in the file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        newVehicle = malloc(sizeof(Vehicle));
        token = strtok(line, ",");
        newVehicle->id = atoi(token);
        token = strtok(NULL, ",");
        strncpy(newVehicle->name, token, NAME_LENGHT-1);
        token = strtok(NULL, ",");
        newVehicle->battery = atof(token);
        token = strtok(NULL, ",");
        newVehicle->rentCost = atof(token);
        token = strtok(NULL, ",");
        strncpy(newVehicle->location, token, LOCATION_LENGHT-1);
        newVehicle->next = NULL;
        insertVehicle(newVehicle, head);
    }

    fclose(fp);
}


/* ------------------- Internal Functions for vehicle Library -------------------- */

/* Create an instance of a vehicle struct and return it*/
Vehicle *createVehicle()
{
    Vehicle *newVehicle = malloc(sizeof(Vehicle));

    printf("Enter the vehicle id: ");
    scanf("%d", &newVehicle->id);
    getchar();

    printf("Enter the vehicle name: ");
    scanf("%[^\n]", newVehicle->name);
    getchar(); // clear input buffer

    printf("Enter the battery level: ");
    scanf("%f", &newVehicle->battery);

    printf("Enter the rental cost per day: ");
    scanf("%f", &newVehicle->rentCost);
    getchar(); // clear input buffer

    printf("Enter the location of the vehicle: ");
    scanf("%[^\n]", newVehicle->location);
    getchar(); // clear input buffer

    newVehicle->next = NULL;
    return newVehicle;
}
/* Display the info of one vehicle */
void showVehicle(Vehicle *vehicle)
{
    printf("\n---------------Start of Vehicle--------------\n\n");
    printf("Vehicle ID: %d \n", vehicle->id);
    printf("Vehicle Name: %s \n", vehicle->name);
    printf("Vehicle Battery Level: %.2f \n", vehicle->battery);
    printf("Vehicle Rental Cost per Day: %.2f \n", vehicle->rentCost);
    printf("Vehicle Location: %s \n", vehicle->location);
    printf("\n---------------END of Vehicle-----------------\n");

}

/*Insert one given vehicle to a vehicleList*/
void insertVehicle(Vehicle *newVehicle, Vehicle **head)
{
        newVehicle->next = *head;
        *head = newVehicle;
}

/* Edit one given vehicle */
void editVehicle(Vehicle **vehicle)
{

    char newLocation[LOCATION_LENGHT],newName[NAME_LENGHT],newBattery[50],newCost[50];

    printf("Enter new name (leave blank for no change): ");
    scanf(" %[^\n]s", newName);
    if (strlen(newName) > 0)
    {
        strcpy((*vehicle)->name, newName);
    }

    printf("Enter new battery level (leave blank for no change): ");
    scanf(" %[^\n]s", newBattery);
    if (strlen(newBattery) >= 0)
    {
        (*vehicle)->battery = atof(newBattery);
    }

    printf("Enter new rental cost per day (leave blank for no change): ");
    scanf(" %[^\n]s", newCost);
    if (strlen(newCost) > 0)
    {
        (*vehicle)->rentCost = atof(newCost);
    }
    printf("Enter new location (leave blank for no change): ");
    scanf(" %[^\n]s", newLocation);
    if (strlen(newLocation) > 0)
    {
        strcpy((*vehicle)->location, newLocation);
    }
}

/* Given a id returns a vehicle if it is exist */
Vehicle *searchVehicleById(int id, Vehicle *vehicles)
{
    Vehicle *vehicle = NULL;
    while (vehicles != NULL)
    {
        if (vehicles->id == id)
        {
            vehicle = vehicles;
        }
        vehicles = vehicles->next;
    }
    return vehicle;
}

/*  If vehicle exist in the list return 1 
    else return 0 
 */
int vehicleExists(int id, Vehicle *vehicle)
{
    while (vehicle != NULL)
    {
        if (vehicle->id == id)
        {
            return 1;
        }
        vehicle = vehicle->next;
    }
    return 0;
}
