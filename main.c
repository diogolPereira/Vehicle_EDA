#include <stdlib.h>
#include <stdio.h>
#include "user/user.h"
#include "vehicle/vehicle.h"
#include "rent/rent.h"

int primaryMenu()
{
	int option;
	printf("\n------ Choice an option -----\n");
	printf("\n 1 - Create a User ");
	printf("\n 2 - Edit a User ");
	printf("\n 3 - Delete a User ");
	printf("\n 4 - See all Users ");
	printf("\n 5 - Read data from CSV File ");
	printf("\n 6 - Choice a User to manage your vehicles");
	printf("\n 7 - Rent a vehicles");
	printf("\n 0 - Sair \nR:.");
	scanf("%d", &option);
	return option;
}

int managingVehicles(Vehicle **vehicles)
{
	int option;
	do
	{
		printf("\n------ Choice an option -----\n");
		printf("\n 1 - Create a Vehicle ");
		printf("\n 2 - Edit a Vehicle ");
		printf("\n 3 - Delete a Vehicle ");
		printf("\n 4 - See all Vehicles ");
		printf("\n 5 - Import vehicles as csv file ");
		printf("\n 0 - Sair \nR:.");
		scanf("%d", &option);

		switch (option)
		{
		// Create a vehicle
		case 1:
			getchar(); // Clean Bufer
			createVehicleToList(vehicles);
			break;

		// Edit a vehicle
		case 2:
			getchar(); // Clean Bufer
			editVehicleById(vehicles);
			break;

		// Delete a vehicle
		case 3:
			getchar(); // Clean Bufer
			deleteVehicle(vehicles);
			break;

		// Show all vehicles
		case 4:
			displayVehiclesList(*vehicles);
			break;
		// Show all vehicles
		case 5:
			readVehicleDataFromFile(vehicles);
			break;

		default:
			break;
		}
	} while (option != 0);

	return 0;
}

void readFromBinaries(User **users, Vehicle **vehicles, Rent **rents)
{
	readVehicle(vehicles);
	readUser(users);
	readRent(rents);
}

void saveAllInfoOnBinaries(User *users, Vehicle *vehicles, Rent *rents)
{
	saveVehicle(vehicles);
	saveUser(users);
	saveRent(rents);
}

//hack for MACOS
void waitHack()
{
	system("read -n 1 -s -p \" Press any key to continue...\"");
}

void addRent(User **userList, Vehicle *vehicleList, Rent **rentList)
{
	int userNif, vehicleId, numberOfDays = 0;
	float rentCost;
	User *user;
 	Vehicle *vehicle;

	printf("\nEnter the user NIF: ");
	scanf("%d", &userNif);
	printf("Enter the vehicle ID: ");
	scanf("%d", &vehicleId);
	printf("Enter the number of days: ");
	scanf("%d", &numberOfDays);

	/* Check if the user exists */
	user = searchUserByNif(userNif, *userList);
	if (user == NULL)
	{
		printf("Error: User with NIF %d does not exist\n", userNif);
		return;
	}

	/* Check if the vehicle exists */
	vehicle = searchVehicleById(vehicleId, vehicleList);
	if (vehicle == NULL)
	{
		printf("Error: Vehicle with ID %d does not exist\n", vehicleId);
		return;
	}

	/* Calculate the rent cost */
	rentCost = vehicle->rentCost * numberOfDays;

	/* Check if the user has enough balance */
	if (user->balance < rentCost)
	{
		printf("Error: User with NIF %d does not have enough balance to rent this vehicle\n", userNif);
		return;
	}

	/* Deduct the rent cost from the user's balance */
	user->balance -= rentCost;

	/* Create the new rent */
	createRent(userNif, vehicleId, numberOfDays, rentList);

	printf("\nRent created.\n");
}

int main()
{

	User *users = NULL;
	Rent *rents = NULL;

	Vehicle *vehicles = NULL;
	int firstMenu = 0;

	readFromBinaries(&users, &vehicles, &rents);
	do
	{

		firstMenu = primaryMenu();
		switch (firstMenu)
		{

		// Create a user
		case 1:
			getchar(); // Clean Bufer
			createUserToList(&users);
			break;

		// Edit a user
		case 2:
			getchar(); // Clean Bufer
			editUserByNif(&users);
			break;

		// Delete a user
		case 3:
			getchar(); // Clean Bufer
			deleteUser(&users);
			break;

		// Show all users
		case 4:
			displayUsersList(users);
			break;
		case 5:
			readUserDataFromFile(&users);
			break;
		case 6:
			// Get an nif from user and validate premissions
			if (logInAsAdmin(users) == 1)
			{
				managingVehicles(&vehicles);
			}
			else
			{
				printf("\nThe user was not founded or is not manager.");
			}
			break;
		case 7:
			addRent(&users, vehicles, &rents);
			break;
		case 0:
			break;
		default:
			printf("Chose a valid option");
			break;
		}

	} while (firstMenu != 0);

	saveAllInfoOnBinaries(users, vehicles, rents);

	waitHack();
}
