/*****************************************************************/ /**
 * @file   User.h
 * @brief  Library for managing users
 * 
 * @author Diogo
 * @date   March 2023
 *********************************************************************/
#include <stdio.h>

#ifndef USERSLIB
#define USERSLIB

#define MAX_LINE_LENGTH 1000
#define NAMELENGHT 50
#define ADDRESSLENGHT 100
#define USERSFILENAME "./user/user.bin"
#define USERSCSVFILENAME "./user/user.csv"

typedef struct User
{
    int nif; 
    char name[NAMELENGHT];
    double balance;
    char address[ADDRESSLENGHT];
    /* If it is manager is 1 else is 0 */
    int isManager; 
    struct User *next;
} User;

/* Create an instance of a user struct and return it*/
User *createUser();

/* Given a nif returns a user if it is exist */
User *searchUserByNif(int nif, User *users);

/* Display the info of one user */ 
void showUser(User *user);

/* Insert one given user to a userList */
void insertUser(User *newUser,User **head);

/* Edit one given user */
void editUser(User **user);

/*  If user exist in the list return 1 
    else return 0 
 */
int userExists(int nif, User *user);

/* Create an User and add it to an given list */
int createUserToList(User **head);


/* Search User By nif and check if it is admin if yes return 1 else return 0 */
int logInAsAdmin(User *head);


/* -------- Functions to manage User list -------- */

/* Read user data from a CSV file and add it to the user linked list */
void readUserDataFromFile(User **head);

/* Display All Users from a list */
void displayUsersList(User *lst);

/* Edit one User from a given userList searched by nif  */
int editUserByNif(User **head);

/* Delete one User from a given userList searched by nif  */
int deleteUser(User **head); 

/* Save a given userList to a binnary file */
int saveUser(User *head);

/* Read from a binary file a user List */
int readUser(User **head);


#endif 
