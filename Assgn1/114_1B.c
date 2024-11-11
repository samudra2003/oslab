/*

 

Name – Samudra Roy

Roll - 002211001114

 

*/

 

/*

 

Assignment Details - This is a program to GET and SET the ENVIRONMENT VARIABLES

and to know the use of getenv and setenv system calls

 

Input Description - No input

 

Output Description - The required ENVIRONMENT VARIABLES are displayed at first

After that two new ENVIRONMENT VARIABLES are set and displayed

 

*/

 

/*

 

Compilation Command - gcc 114_1B.c

 

Execution Command - ./a.out

 

*/

 

/*

PROGRAM TO GET AND SET ENVIRONMENT VARIABLES

------------------------------------------------------------------

 

The ENVIRONMENT VARIABLES ARE

 

USER = samudra

HOME = /home/samudra

No ENVIRONMENT VARIABLE named 'HOST' exists

No ENVIRONMENT VARIABLE named 'ARCH' exists

DISPLAY = :0

No ENVIRONMENT VARIABLE named 'PRINTER' exists

PATH = /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin

------------------------------------------------------------------

 

Setting up two new ENVIRONMENT VARIABLES 'HOST' and 'ARCH'

The newly setted ENVIRONMENT VARIABLES are

 

HOST = samudra

ARCH = x86_64

------------------------------------------------------------------



*/

 

 

// Header Files

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/utsname.h>

 

#define MAX_LENGTH 10

 

int main()

{

char environmentVariableName[][MAX_LENGTH] =

{

{"USER"},

{"HOME"},

{"HOST"},

{"ARCH"},

{"DISPLAY"},

{"PRINTER"},

{"PATH"},

}; // Character array containing the ENVIRONMENT VARIABLES

 

printf("PROGRAM TO GET AND SET ENVIRONMENT VARIABLES\n");

printf("------------------------------------------------------------------\n\n");

printf("The ENVIRONMENT VARIABLES ARE \n\n");

 

int i;

for(i = 0; i < 7; i++) // Printing the ENVIRONMENT VARIABLES

{

char *environmentValue = getenv(environmentVariableName[i]);

// Using the 'getenv' method to get the ENVIRONMENT VARIABLES

if(environmentValue == NULL)

printf("No ENVIRONMENT VARIABLE named '%s' exists\n",environmentVariableName[i]);

else

printf("%s = %s\n",environmentVariableName[i],environmentValue);

}

 

char hostName[50];

if(gethostname(hostName,50)) // Getting and storing the host name in 'hostName'

perror("Error getting hostname"); // 'perror' uses 'errno' variable and prints error information

 

if(setenv("HOST",hostName,1)<0) // Using 'setenv' method for setting the hostName into the new ENVIRONMENT VARIABLE 'HOST'

perror("Error setting 'HOST' environment variable");

 

 

struct utsname buffer;

 

if(uname(&buffer)<0) // Getting the utsname structure containing the system information in 'buffer'

perror("Error getting the system information using uname");

if(setenv("ARCH",buffer.machine,1)<0) // Setting the value contained in 'buffer.machine' into the new ENVIRONMENT VARIABLE 'ARCH'

perror("Error setting 'ARCH' environment variable");

 

printf("------------------------------------------------------------------\n\n");

printf("Setting up two new ENVIRONMENT VARIABLES 'HOST' and 'ARCH' \n");

printf("The newly setted ENVIRONMENT VARIABLES are \n\n");

 

 

for(i = 2; i < 4; i++) // Printing the newly setted ENVIRONMENT VARIABLES

{

char *environmentValue = getenv(environmentVariableName[i]);

 

if(environmentValue == NULL)

printf("No ENVIRONMENT VARIABLE named '%s' exists\n",environmentVariableName[i]);

else

printf("%s = %s\n",environmentVariableName[i],environmentValue);

}

 

printf("------------------------------------------------------------------\n");

return 0;

}