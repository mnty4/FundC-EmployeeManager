/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Lukas Gaspar
 * Student ID: 13910676
 * Date of submission: 16/04/21
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * I was able to achieve a functioning program that can create employees, 
 * delete the last employee on the employee list and display a list of all 
 * employees created. It can also save the employee list to a database and 
 * add employees from the database to the employee list.
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/
/* gcc -Wall -Werror -ansi -o Ass2_main.out Ass2_main.c -lm */
/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/

#define MAX_COMPANY_SIZE 5
#define MAX_NAME_SIZE 11

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
struct date
{
    unsigned int day;
    unsigned int month;
    unsigned int year;
};
typedef struct date date_t;

/* Basic employee structure*/
struct employee
{
    char name[MAX_NAME_SIZE];
    float fte;
    date_t birthday;
};
typedef struct employee employee_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void printMenu(void);
date_t createBirthday(void);
employee_t addEmployee(void);
void displayEmployeeList(employee_t employeelist[], int employeeCount);
void saveToDatabase(employee_t employeelist[], int employeeCount, 
char dbFileName[]);
int readDatabase(employee_t employeelist[], int employeeCount, 
char dbFileName[]);
/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /*
    * Choice - number entered by user
    * employeeCount - number of employees on employeelist 
    */
    int choice, employeeCount = 0; /* Choice - number entered by user, 
                        employeeCount - number of employees on employeelist*/
    
    char newLine; /* var to eat new line */
    
    employee_t employeelist[MAX_COMPANY_SIZE]; /* employeelist - an array of 
                                            all the employees */

    char dbFileName[] = "database";

    /* Checks the user's choice and will carry out the assinged process */
    do
    {
        /* printMenu - list of number choices for the user */
        printMenu();
        printf("Enter your choice>");

        /* Takes the choice input and eats the new line */
        scanf("%d%c", &choice, &newLine);

        if (choice < 1 || choice > 6) {
            printf("Invalid choice.\n");
        }
        if (choice == 1)
        {
            /* Ensures employeeCount will not surpass the MAX_COMPANY_SIZE */
            if(employeeCount == MAX_COMPANY_SIZE) {
                printf("Maximum number of employees reached.\n");
                continue;
            }
            /* Creates new employee through addEmployee function and stores 
            into next element in the employeelist array */
            employeelist[employeeCount] = addEmployee();
            employeeCount++;
        }

        if (choice == 2)
        {
            /* Check if employeelist array is empty. */
            if (employeeCount == 0) {
                printf("No employee.\n");
                continue;
            }

                employeeCount--;

        }

        if (choice == 3)
        {
            /* Calls the displayEmployeeList function which displays 
            all current employees. */
            displayEmployeeList(employeelist, employeeCount);
        }

        if (choice == 4)
        {
            /* Calls saveToDatabase to save all employees currently 
            in the employee list to the database file */
            saveToDatabase(employeelist, employeeCount, dbFileName);
        }

        if (choice == 5)
        {
            /* Calls the readDatabase function which adds all employees in the
            datbase to the employee list array */
            employeeCount = readDatabase(employeelist, 0, dbFileName);
        }
        
    } while (choice != 6); /* Keeps reading user choices when a choice is 
                            completed until 6 is input. */
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMenu(void)
{
    printf("\n\n"
           "1. add employee\n"
           "2. delete last employee\n"
           "3. display employee list\n"
           "4. save the employee list to the database\n"
           "5. read the employee list from the database\n"
           "6. exit the program\n");
}

/*******************************************************************************
 * This function prompts the user for the date of their birthday and returns
 * the information in the type date_t.
 * inputs:
 * - none
 * outputs:
 * - newBirthday> contains the new employees birthday in type date_t
*******************************************************************************/
date_t createBirthday(void)
{

    date_t newBirthday;
    int invalidInput = 1;

    /* Gets new employees birthday day, will repeat 
    if invalid day is input until correct day is entered */
    do
    {
        invalidInput = 1;
        printf("Enter birthday: day>");
        scanf("%d", &newBirthday.day);

        if (newBirthday.day < 1 || newBirthday.day > 31)
        {
            printf("Invalid day. ");
            invalidInput = 0;
        }
    } while (invalidInput == 0);

    /* Gets new employees birthday month, will repeat 
    if invalid month is input until correct month is entered */
    do
    {
        invalidInput = 1;
        printf("Enter birthday: month>");
        scanf("%d", &newBirthday.month);
        if (newBirthday.month < 1 || newBirthday.month > 12)
        {
            printf("Invalid month. ");
            invalidInput = 0;
        }
    } while (invalidInput == 0);

    /* Gets new employees birthday year, will repeat 
    if invalid year is input until correct year is entered */
    do
    {
        invalidInput = 1;
        printf("Enter birthday: year>");
        scanf("%d", &newBirthday.year);
        if (newBirthday.year < 1800 || newBirthday.year > 2017)
        {
            printf("Invalid year. ");
            invalidInput = 0;
        }
    } while (invalidInput == 0);

    return newBirthday;
}

/*******************************************************************************
 * This function prompts the user to enter in their name, birthday and fte and
 * returns this info in the struct employee_t.
 * inputs:
 * - none
 * outputs:
 * - newEmployee> new employees name, birthday and fte in type employee_t
*******************************************************************************/
employee_t addEmployee(void)
{

    employee_t newEmployee;
    int invalidInput = 1, i = 0;

    printf("Enter name>");
    
    /* Get employee name character by character and 
    end the loop when a new line is input. */
    while (scanf("%c", &newEmployee.name[i]) == 1)
    {
        /* New line character from stdin is replaced by a 
        /0 character to finish the name string. */
        if (newEmployee.name[i] == '\n' && i > 0)
        {
            newEmployee.name[i] = '\0';
            break;
        }
        /* Eats any excess chars. */
        if(i >= MAX_NAME_SIZE - 1) {
            newEmployee.name[i] = '\0';
            continue;
        }
        
        i++;
    }

    /* Calls createBirthday function to get the new 
    employees birthday. */
    newEmployee.birthday = createBirthday();

    /* Gets fte value and puts into newEmployee.fte, 
    if incorrect input, loops back again. */
    do 
    {
        invalidInput = 1;
        printf("Enter FTE>");
        scanf("%f", &newEmployee.fte);
        if (newEmployee.fte < 0.0 || newEmployee.fte > 1.0)
        {
            printf("Invalid FTE. ");
            invalidInput = 0;
        }
    } while (invalidInput == 0);
    return newEmployee;

}
/*******************************************************************************
 * This function displays the employees from a list given.
 * inputs:
 * - employeelist> the array of employees
 * outputs:
 * - none
*******************************************************************************/
void displayEmployeeList(employee_t employeelist[], 
int employeeCount)
{

    int i, j;
    if (employeeCount > 0) {
        printf("Name       Birthday   FTE\n");
        printf("---------- ---------- ------\n");

        for (j = 0; j < employeeCount; j++)
        {

            printf("%s", employeelist[j].name);

            /* Add blanks to make up to 11 characters. */
            for (i = 0; i < 11 - strlen(employeelist[j].name); i++)
            {
                printf(" ");
            }
            /* adds a 0 before the day and month if it is below 10. */
            if (employeelist[j].birthday.day < 10)
            {
                printf("0%d-", employeelist[j].birthday.day);
            }
            else
            {
                printf("%d-", employeelist[j].birthday.day);
            }

            if (employeelist[j].birthday.month < 10)
            {
                printf("0%d-", employeelist[j].birthday.month);
            }
            else
            {
                printf("%d-", employeelist[j].birthday.month);
            }

            printf("%d ", employeelist[j].birthday.year);

            printf("%0.4f\n", employeelist[j].fte);
        }
    }
    if (employeeCount == 0) {
        printf("No employee.\n");
    }
}

/*******************************************************************************
 * This function saves all employees from the current employee list to a
 * database file.
 * inputs:
 * - employeelist> the list of employees
 * - employeeCount> the number of employees in the employee list array
 * - dbFileName> the database file name
 * outputs:
 * - none
*******************************************************************************/
void saveToDatabase(employee_t employeelist[], int employeeCount, 
char dbFileName[])
{
    int i, j;
    FILE *databasep = NULL;

    if (employeeCount == 0) {
        printf("No employee.\n");
        return;
    }
    
    databasep = fopen(dbFileName, "w");
    
    /* If databasep is NULL, the file didnt open correctly and so we 
    get out of the function. */
    if (databasep == NULL) {
        return;
    }
    /* Prints the employee details for each element of 
    employee list into the file up to the employee total (employeeCount). */
    for (i = 0; i < employeeCount; i++) {
        fprintf(databasep, "%d\n", i);
        fprintf(databasep, "name: ");
        for (j = 0; j < strlen(employeelist[i].name); j++) {
            fprintf(databasep, "%c", employeelist[i].name[j]);
        }
        fprintf(databasep, "\n");

        fprintf(databasep, "day: %d\n", employeelist[i].birthday.day);
        fprintf(databasep, "month: %d\n", employeelist[i].birthday.month);
        fprintf(databasep, "year: %d\n", employeelist[i].birthday.year);

        fprintf(databasep, "fte: %f\n", employeelist[i].fte);
    }

    fclose(databasep);
}

/*******************************************************************************
 * This function reads the employees from the database file and adds them to
 * the employee list.
 * inputs:
 * - employeelist> the list of employees
 * - employeeCount> the number of employees in employee list
 * - dbFileName> the database file name
 * outputs:
 * - employeeCount> number of employees after they've been read in
*******************************************************************************/
int readDatabase(employee_t employeelist[], int employeeCount, 
                        char dbFileName[]) {
    FILE* databasep = NULL;
    
    char tempStr[MAX_NAME_SIZE]; /* tempStr is used to temporarily store and 
                                check for strings */
    
    int i, employeedbNumber; /* employeedbNumber is the number of employees 
                                in the database. I is used for a for loop. */

    databasep = fopen(dbFileName, "r");

    /* If databasep is NULL, the file didnt open correctly or is empty and so 
    we return the function. */
    if (databasep == NULL) {
        printf("Read error\n");
        return employeeCount;
    }
    /* Scans in the employee number starting from 0.
    If it does not read in enough arguments or temp has the incorrect value,
    then we check if either the loop is finished in which case we
    break out of it or temp didn't read anything in which case there 
    is a read error. */
    for (i = 0; i < MAX_COMPANY_SIZE; i++) {
        employeedbNumber = 0;

        /* Scans for an Integer that numbers the employees in the database,
        stores it in employeedbNumber. If fscanf result does not equal 1
        then then nothing was scanned and so we have reached the end of 
        file. */
        if (fscanf(databasep, "%d", &employeedbNumber) != 1) {
            break;
        }
        
        /* Checks there is a "name: " string to ensure there is a name to scan.
        If not, program prints an error msg and breaks the loop. Otherwise the
        employee name is scanned into the next element in the employeelist 
        array's 
        name (employeelist[employeeCount].name) */
        if (fscanf(databasep, "%s%s", tempStr, employeelist[employeeCount]
            .name) < 2 || strcmp(tempStr, "name:") != 0) {
            printf("Read error\n");
            break;
        }

        if (fscanf(databasep, "%s%d", tempStr, &employeelist[employeeCount]
            .birthday.day) < 2 || strcmp(tempStr, "day:") != 0) {
            printf("Read error\n");
            break;
        }

        if (fscanf(databasep, "%s%d", tempStr, &employeelist[employeeCount]
            .birthday.month) < 2 || strcmp(tempStr, "month:") != 0) {
            printf("Read error\n");
            break;
        }

        if (fscanf(databasep, "%s%d", tempStr, &employeelist[employeeCount]
            .birthday.year) < 2 || strcmp(tempStr, "year:") != 0) {
            printf("Read error\n");
            break;
        }

        if (fscanf(databasep, "%s%f", tempStr, &employeelist[employeeCount]
            .fte) < 2 || strcmp(tempStr, "fte:") != 0) {
            printf("Read error\n");
            break;
        }

        employeeCount++;
    }

    fclose(databasep);
    
    return employeeCount;
}
