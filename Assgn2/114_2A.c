/*

Name- Samudra Roy
Roll - 002211001114

*/

/*

Assignment Details - Catch the signal "SIGINT" and display "Ha Ha, Not Stopping". Use "signal"
                     system call. Always use "perror" to check the return status of a library/system call.

Input Description  - Control + C

Output Description - Ha Ha, Not Stopping

*/

/*

Compilation Command - gcc 114_2A.c

Execution Command   - ./a.out

*/

/*

Sample Input  - No input
Sample Output -

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING
^C
Ha Ha, Not Stopping

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING

PROCESS RUNNING
^C
Ha Ha, Not Stopping

PROCESS RUNNING

PROCESS RUNNING
^C
Ha Ha, Not Stopping

PROCESS RUNNING

PROCESS RUNNING
^\Quit (core dumped)

*/

// Header Files
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int signal)
{
        if (signal == SIGINT) // When SIGINT is caught, we are printing the message
                printf("\nHa Ha, Not Stopping\n");
}

int main()
{
        if (signal(SIGINT, signalHandler) == SIG_ERR)
                perror("\nSome error occured in catching SIGINT.\n");

        while (1) // Running an infinite loop to dummy a process
        {
                printf("\nPROCESS RUNNING\n");
                sleep(1);
        }

        return 0;
}