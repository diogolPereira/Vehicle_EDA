#include <stdlib.h>
#include <stdio.h>
#include "user/user.h"
#include "vehicle/vehicle.h"

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
	}while(option != 0);

	return 0;
}

void readFromBinaries(User **users, Vehicle **vehicles)
{
	readVehicle(vehicles);
	readUser(users);
}

void saveAllInfoOnBinaries(User *users, Vehicle *vehicles)
{
	saveVehicle(vehicles);
	saveUser(users);
}

//hack for MACOS
void waitHack()
{
	system("read -n 1 -s -p \" Press any key to continue...\"");
}

int main()
{

	User *users = NULL;
	Vehicle *vehicles = NULL;
	int firstMenu = 0;

	readFromBinaries(&users, &vehicles);

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
		case 0:
			break;
		default:
			printf("Chose a valid option");
			break;
		}

	} while (firstMenu != 0);

	saveAllInfoOnBinaries(users, vehicles);

	waitHack();
	// /* Ler users */
	// if (readUser(&users))
	// {
	// 	/* Show all users */
	// 	displayUsersList(users);
	// }

	// /* Create a user */
	// createUserToList(&users);

	// /* Edit user by nif */
	// editUserByNif(&users);

	// /* Apagar user se já existe um user com esse nif */

	// deleteUser(&users);

	// saveUser(users);

	// if(readVehicle(&vehicles)){
	// 	displayVehiclesList(vehicles);
	// }

	// createVehicleToList(&vehicles);

	// /* Edit user by nif */
	// editVehicleById(&vehicles);

	// /* Apagar user se já existe um user com esse nif */

	// deleteVehicle(&vehicles);

	// saveVehicle(vehicles);
}
