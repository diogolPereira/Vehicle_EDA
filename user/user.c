#include <stdlib.h>
#include <string.h>
#include "user.h"

/* Display All Users from a list */
void displayUsersList(User *lst)
{
    User *aux = lst;
    while (aux != NULL)
    {
        showUser(aux);
        aux = aux->next;
    }
    putchar('\n');
}

/* Delete one User from a given userList searched by nif  */
int deleteUser(User **head)
{
    User *temp = *head;
    User *prev;
    int nif;

    getchar(); // Clean Bufer
    printf("\n Que nif pretende apagar? \n");
    scanf("%i", &nif);

    // If head node itself holds the matching id
    if (temp != NULL && temp->nif == nif)
    {
        *head = temp->next;
        free(temp);
        return 1;
    }

    while (temp != NULL && temp->nif != nif)
    {
        prev = temp;
        temp = temp->next;
    }

    // If id was not found in the linked list
    if (temp == NULL)
    {
        printf("User with nif %d not found\n", nif);
        return 0;
    }

    // Unlink the node with the matching id
    prev->next = temp->next;

    // Free the memory occupied by the node with the matching id
    free(temp);
    return 1;
}

/* Edit one User from a given userList searched by nif  */
int editUserByNif(User **head)
{
    User *current = NULL;
    int nifToEdit;

    printf("\nQue nif pretende editar? \n");
    scanf("%i", &nifToEdit);

    current = searchUserByNif(nifToEdit, *head);
    if (current != NULL)
    {
        editUser(&current);
        return 1;
    }
    printf("User with nif %d not found\n", nifToEdit);
    return 0;
}

/* Save userlist into the user binary file */
int saveUser(User *head)
{
    FILE *file;
    User *currentUser = head;

    file = fopen(USERSFILENAME, "wb");
    if (file == NULL)
    {
        return 0; // Error opening file
    }

    // Write the users to the file
    while (currentUser != NULL)
    {
        if (fwrite(currentUser, sizeof(User), 1, file) != 1)
        {
            fclose(file);
            return 0; // Error writing to file
        }
        currentUser = currentUser->next;
    }
    fclose(file);
    return 1; // Success
}

/* Read the user binary file */
int readUser(User **head)
{
    FILE *file;
    User tempUser;
    User *newUser;

    file = fopen(USERSFILENAME, "rb");
    if (file == NULL)
    {
        return 0; // File not found
    }

    while (1)
    {
        newUser = (User *)malloc(sizeof(User));
        if (fread(newUser, sizeof(User), 1, file) != 1)
        {
            free(newUser);
            break;
        }

        insertUser(newUser, head);
    }

    fclose(file);
    return 1; // User read successfully
}

/* Create an User and add it to an given list */
int createUserToList(User **head)
{
    /* Criar users */
    User *newUser = createUser();

    /* Validate if user already exist */
    if (userExists(newUser->nif, *head) != 1)
    {
        // passar em point
        insertUser(newUser, head);
        return 1;
    }
    else
    {
        free(newUser);
        return 0;
    }
}

/* Search User By nif and check if it is admin if yes return 1 else return 0 */
int logInAsAdmin(User *head)
{
    User *current = NULL;
    int nifToEdit;

    printf("\nWhat user do you want to chosse ?");
    scanf("%i", &nifToEdit);

    current = searchUserByNif(nifToEdit, head);
    if (current != NULL && current->isManager)
    {
        return 1;
    }
    return 0;
}

/* Read user data from a CSV file and add it to the user linked list */
void readUserDataFromFile(User **head)
{
    FILE *fp;
    char line[MAX_LINE_LENGTH];
    char *token;
    User *newUser;

    fp = fopen(USERSCSVFILENAME, "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file %s\n", USERSCSVFILENAME);
        return;
    }
    fgets(line, MAX_LINE_LENGTH, fp); // Read first line (header)

    /* Read each line in the file */
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL)
    {
        newUser = malloc(sizeof(User));
        token = strtok(line, ",");
        newUser->nif = atoi(token);

        /* Validate if doesn't exist a user already created with that nif*/
        if (!userExists(newUser->nif, *head))
        {
            token = strtok(NULL, ",");
            strncpy(newUser->name, token, NAMELENGHT - 1);
            token = strtok(NULL, ",");
            newUser->balance = atof(token);
            token = strtok(NULL, ",");
            strncpy(newUser->address, token, ADDRESSLENGHT - 1);
            token = strtok(NULL, ",");
            newUser->isManager = atoi(token);
            newUser->next = NULL;
            insertUser(newUser, head);
        }
    }

    fclose(fp);
}

/* ------------------- Internal Functions for user Library -------------------- */

/* Create an instance of a user struct and return it*/
User *createUser()
{
    User *newUser = malloc(sizeof(User));

    printf("\n---------------Create User--------------\n\n");
    printf("User name: ");
    scanf("%[^\n]", newUser->name);
    getchar();
    printf("User NIF: ");
    scanf("%i", &newUser->nif);
    printf("User balance: ");
    scanf("%lf", &newUser->balance);
    getchar();
    printf("User Address: ");
    scanf("%[^\n]", newUser->address);
    printf("Is admin: [0 - No 1 - Yes] \n");
    scanf("%i", &newUser->isManager);
    newUser->next = NULL;

    return newUser;
}

/* Display the info of one user */
void showUser(User *user)
{
    printf("---------------Start of User--------------\n");
    printf("NIF : %i \n", user->nif);
    printf("Name : %s \n", user->name);
    printf("Balance : %.1f \n", user->balance);
    printf("Address : %s \n", user->address);
    printf("IsManager : %s \n", user->isManager ? "Yes" : "No");
    printf("---------------END of User-----------------\n");
}

/*Insert one given user to a userList*/
void insertUser(User *newUser, User **head)
{
    if (*head == NULL)
    {
        *head = newUser;
        newUser->next = NULL;
    }
    else
    {
        newUser->next = *head;
        *head = newUser;
    }
}

/* Edit one given user */
void editUser(User **user)
{
    User *current = *user;
    int choice;

    printf("Qual campo quer editar?\n");
    printf("1. Name\n");
    printf("2. Balance\n");
    printf("3. Address\n");
    printf("4. isManager\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("\nNew name: ");
        scanf(" %[^\n]", current->name);
        break;
    case 2:
        printf("\nNew balance: ");
        scanf("%lf", &current->balance);
        break;
    case 3:
        printf("\nNew address: ");
        scanf(" %[^\n]", current->address);
        break;
    case 4:
        printf("\nIs admin: [0 - No 1 - Yes] ");
        scanf("%d", &current->isManager);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

/* Given a nif returns a user if it is exist */
User *searchUserByNif(int nif, User *users)
{
    User *user = NULL;
    while (users != NULL)
    {
        if (users->nif == nif)
        {
            user = users;
        }
        users = users->next;
    }
    return user;
}

/*  If user exist in the list return 1 
    else return 0 
 */
int userExists(int nif, User *user)
{
    while (user != NULL)
    {
        if (user->nif == nif)
        {
            return 1;
        }
        user = user->next;
    }
    return 0;
}
