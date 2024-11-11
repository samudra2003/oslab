/*

 Name - Samudra Roy
 Roll - 002211001114
 
*/

/*
Assignment Details - The OS is a program that uses various data structures. Like all programs in
                     execution, you can determine the performance and other behaviour of the OS by
                     inspecting its state - the values stored in its data structures. In this part of the
                     assignment, we study some aspects of the organization and behaviour of a Linux
                     system by observing values of kernel data structures exposed through the /proc
                     virtual file system.

                     The /proc virtual file system:
                     Linux uses the /proc file system to collect information from kernel data structures.
                     The /proc implementation provided with Linux can read many different kernel data
                     structures. If you cd to /proc on a Linux machine, you will see a number of files and
                     directories at that location. Files in this directory subtree each correspond to some
                     kernel data structure. The subdirectories with numeric names contain virtual files
                     with information about the process whose process ID is the same as the directory
                     name. Files in /proc can be read like ordinary ASCII files. You can open each file
                     and read it using library routines such as fgets() or fscanf(). The proc (5) manual
                     page explains the virtual files and their content available through the /proc file
                     system.

                     Requirements in detail:
                     You are supposed to write a C program which should run continuously and print lists
                     of the following dynamic values every seconds:
                     ? Per second disk read/write in the system
                     ? Per second Timer Interrupts
                     ? Currently executing kernel scheduling entities (processes, threads)
                     ? Number of kernel scheduling entities that currently exist on the system

Input Description  - No input
Output Description - Print the dynamic values every seconds
                     ? Per second disk read/write in the system
                     ? Per second Timer Interrupts
                     ? Currently executing kernel scheduling entities (processes, threads)
                     ? Number of kernel scheduling entities that currently exist on the system

*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 114_6.c
Execution Command (in Linux Bash Terminal) :- ./a.out
*/

/*
Sample Input  - No input
Sample Output -
Output :- (PROGRAM OUTPUT)
Displaying ... 

Time spent in user mode : 3.521550 %, idle mode : 90.060128 % , system mode : 3.358025 % 

Available Memory : 1347880 kb
The Percentage Available Memory : 38.852717

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 869.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.519696 %, idle mode : 90.065231 % , system mode : 3.356482 % 

Available Memory : 1347880 kb
The Percentage Available Memory : 38.852717

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 181.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.519087 %, idle mode : 90.064941 % , system mode : 3.359039 % 

Available Memory : 1347880 kb
The Percentage Available Memory : 38.852717

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 590.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.517162 %, idle mode : 90.070266 % , system mode : 3.357311 % 

Available Memory : 1347880 kb
The Percentage Available Memory : 38.852717

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 156.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515247 %, idle mode : 90.075674 % , system mode : 3.355483 % 

Available Memory : 1347880 kb
The Percentage Available Memory : 38.852717

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 149.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515152 %, idle mode : 90.071302 % , system mode : 3.361401 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 40.000000
Rate of Context Switches (number per sec) : 799.000000
Rate of Process Creations (number per sec) : 1.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515129 %, idle mode : 90.067153 % , system mode : 3.367493 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 862.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515098 %, idle mode : 90.063031 % , system mode : 3.373352 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 790.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515418 %, idle mode : 90.058412 % , system mode : 3.379445 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 1396.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515617 %, idle mode : 90.054159 % , system mode : 3.385300 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 847.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515579 %, idle mode : 90.050074 % , system mode : 3.391348 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 24.000000
Rate of Context Switches (number per sec) : 711.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515341 %, idle mode : 90.046268 % , system mode : 3.397188 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 709.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
------------------------------------------------------------------------------------------

Displaying ... 

Time spent in user mode : 3.515337 %, idle mode : 90.041769 % , system mode : 3.403472 % 

Available Memory : 1347888 kb
The Percentage Available Memory : 38.852947

Average Read Rate of the disk (sectors per second) : 0.000000
Average Write Rate of the disk (sectors per second) : 0.000000
Rate of Context Switches (number per sec) : 736.000000
Rate of Process Creations (number per sec) : 0.000000

Kernel Information: 
Kernel Name: CPU0
Kernel Release: CPU2
-------------------------------------------------------------------------------------------------


*/




// Header Files
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER_LENGTH 10000

// Utility function to print a separator line
void printLine()
{
    printf("------------------------------------------------------------------------------------------\n\n");
}

// Function to convert a string to a double
double toDouble(const char *str)
{
    int n = strlen(str);
    int i;
    double ans = 0;
    for (i = 0; i < n; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ans = ans * 10 + (str[i] - '0');
        }
    }
    return ans;
}

// Function to convert a string to an integer
int toInt(const char *str)
{
    int n = strlen(str);
    int i, ans = 0;
    for (i = 0; i < n; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ans = ans * 10 + (str[i] - '0');
        }
    }
    return ans;
}

// Function to print kernel information from /proc/interrupts file
void kernelInfo()
{
    FILE *fp;
    fp = fopen("/proc/interrupts", "rb");
    char *kernelName = (char *)malloc(1024);
    char *release = (char *)malloc(1024);
    char *temp = (char *)malloc(1024);
    fscanf(fp, "%s %s %s", kernelName, temp, release);
    printf("\nKernel Information: \n");
    printf("Kernel Name: %s\n", kernelName);
    printf("Kernel Release: %s\n", release);
    free(kernelName);
    free(release);
    free(temp);
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    char stream[MAX_BUFFER_LENGTH]; // Buffer for reading data from files

    // Initialization of key variables for CPU, memory, and disk metrics
    double total = 0, idle, user, temp, system, mem_total, ctxt_prev, process_prev, sector_write_prev, sector_read_prev;
    double user_total = 0, idle_total = 0, system_total = 0, disk_read = 0, disk_write = 0;
    unsigned long long int available_mem, available_mem_total = 0;
    double ctxt_rate = 0, process_rate = 0;
    int observations = 0, disks = 0;
    int read_time = 1, print_time = 1;

    // Reading /proc/stat to save initial values for context switches and process counts
    FILE *kernel_st_file = fopen("/proc/stat", "r");
    if (kernel_st_file == NULL)
    {
        perror("Error in opening file to read kernel/system statistics\n");
        exit(EXIT_FAILURE);
    }

    // Fetching initial context switch and process creation counts from /proc/stat
    while (fgets(stream, MAX_BUFFER_LENGTH, kernel_st_file))
    {
        char *tk = NULL;
        tk = strtok(stream, " ");
        int i = 1, flag = 0;

        while (tk != NULL)
        {
            if (strcmp(tk, "ctxt") == 0) flag = 1;
            if (strcmp(tk, "processes") == 0) flag = 2;
            if (i == 2 && flag == 1)
            {
                flag = 0;
                ctxt_prev = toDouble(tk); // Initial context switches count
            }
            if (i == 2 && flag == 2)
            {
                flag = 0;
                process_prev = toDouble(tk); // Initial process count
            }
            i++;
            tk = strtok(NULL, " ");
        }
        free(tk);
    }
    fclose(kernel_st_file);

    // Opening /proc/diskstats to read initial disk statistics
    FILE *diskstat_file = fopen("/proc/diskstats", "r");
    if (diskstat_file == NULL)
    {
        perror("Error in opening the file to read the disk statistics \n");
        exit(EXIT_FAILURE);
    }

    // Parsing disk stats for initial read and write sectors (for disk "sda")
    while (fgets(stream, MAX_BUFFER_LENGTH, diskstat_file))
    {
        char *token = NULL;
        int i = 1, flag = 0;
        token = strtok(stream, " ");

        while (token != NULL)
        {
            if (strcmp(token, "sda") == 0) flag = 1;
            if (flag == 1)
            {
                if (i == 6) sector_read_prev = toDouble(token); // Initial sectors read
                if (i == 10) sector_write_prev = toDouble(token); // Initial sectors written
            }
            token = strtok(NULL, " ");
            i++;
        }
        free(token);
    }
    fclose(diskstat_file);

    // Starting the clocks for file reading and printing intervals
    clock_t initial_read = clock();
    clock_t initial_write = clock();

    // Infinite loop to continuously monitor system stats
    while (1)
    {
        clock_t final_time = clock();

        // Calculating elapsed time for reading and printing
        int diff_read = (int)(final_time - initial_read) / CLOCKS_PER_SEC;
        int diff_print = (int)(final_time - initial_write) / CLOCKS_PER_SEC;

        // Condition to record data at specified read interval
        if (diff_read == read_time)
        {
            // Reset and initialize variables for each observation
            total = 0;
            temp = 0;
            int i = 1;
            observations++;
            double read_rate = 0, write_rate = 0;
            double ctxt_new, process_new;

            // Reading CPU statistics from /proc/stat
            FILE *stat_file = fopen("/proc/stat", "r");
            if (stat_file == NULL)
            {
                perror("Error in opening file for reading processor time statistics \n");
                exit(EXIT_FAILURE);
            }

            fscanf(stat_file, "%s", stream);
            while (i <= 10)
            {
                fscanf(stat_file, "%lf", &temp);
                total += temp; // Sum total CPU time

                if (i == 1) user = temp;   // User mode time
                else if (i == 3) system = temp; // System mode time
                else if (i == 4) idle = temp;   // Idle mode time
                i++;
            }

            idle = (idle * 100.0) / total;
            user = (user * 100.0) / total;
            system = (system * 100.0) / total;

            idle_total += idle;
            user_total += user;
            system_total += system;

            fclose(stat_file);

            // Reading memory stats from /proc/meminfo
            FILE *mem_file = fopen("/proc/meminfo", "r");
            if (mem_file == NULL)
            {
                perror("Error in opening file for reading memory details \n");
                exit(EXIT_FAILURE);
            }

            // Read total memory
            fscanf(mem_file, "%s", stream);
            fscanf(mem_file, "%lf", &mem_total);
            fscanf(mem_file, "%s\n", stream);
            fgets(stream, MAX_BUFFER_LENGTH, mem_file);

            // Read available memory
            fscanf(mem_file, "%s", stream);
            fscanf(mem_file, "%lld", &available_mem);
            fscanf(mem_file, "%s", stream);

            available_mem_total += available_mem;
            fclose(mem_file);

            // Reading disk stats for read/write rates
            FILE *disk_file = fopen("/proc/diskstats", "r");
            if (disk_file == NULL)
            {
                perror("Error in opening the file to read the disk statistics \n");
                exit(EXIT_FAILURE);
            }

            double sector_read, sector_write;
            while (fgets(stream, MAX_BUFFER_LENGTH, disk_file))
            {
                char *token = NULL;
                int i = 1, flag = 0;
                token = strtok(stream, " ");

                while (token != NULL)
                {
                    if (strcmp(token, "sda") == 0) flag = 1;
                    if (flag == 1)
                    {
                        if (i == 6) sector_read = toDouble(token);
                        if (i == 10) sector_write = toDouble(token);
                    }
                    token = strtok(NULL, " ");
                    i++;
                }
                free(token);
            }

            read_rate = (sector_read - sector_read_prev) / read_time;
            write_rate = (sector_write - sector_write_prev) / read_time;

            sector_write_prev = sector_write;
            sector_read_prev = sector_read;

            disk_read += read_rate;
            disk_write += write_rate;
            fclose(disk_file);

            // Reading context switches and process creation rates
            FILE *kernel_stat_file = fopen("/proc/stat", "r");
            if (kernel_stat_file == NULL)
            {
                perror("Error in opening file to read kernel/system statistics\n");
                exit(EXIT_FAILURE);
            }

            while (fgets(stream, MAX_BUFFER_LENGTH, kernel_stat_file))
            {
                char *tk = NULL;
                tk = strtok(stream, " ");
                int i = 1, flag = 0;

                while (tk != NULL)
                {
                    if (strcmp(tk, "ctxt") == 0) flag = 1;
                    if (strcmp(tk, "processes") == 0) flag = 2;
                    if (i == 2 && flag == 1)
                    {
                        flag = 0;
                        ctxt_new = toDouble(tk);
                    }
                    if (i == 2 && flag == 2)
                    {
                        flag = 0;
                        process_new = toDouble(tk);
                    }
                    i++;
                    tk = strtok(NULL, " ");
                }
                free(tk);
            }

            ctxt_rate += (ctxt_new - ctxt_prev) / read_time;
            process_rate += (process_new - process_prev) / read_time;
            ctxt_prev = ctxt_new;
            process_prev = process_new;
            fclose(kernel_stat_file);

            initial_read = clock();
        }

        // Printing the data every print interval
        if (diff_print == print_time)
        {
            printLine();
            printf("Observed Statistics after %d seconds \n", observations * read_time);
            printf("Average User Mode CPU %% = %lf %%\n", user_total / observations);
            printf("Average System Mode CPU %% = %lf %%\n", system_total / observations);
            printf("Average Idle CPU %% = %lf %%\n", idle_total / observations);
            printf("Average Available Memory = %lf KB\n", available_mem_total / observations);
            printf("Average Disk Read Rate = %lf blocks/s\n", disk_read / observations);
            printf("Average Disk Write Rate = %lf blocks/s\n", disk_write / observations);
            printf("Context Switching Rate = %lf ctxt/s\n", ctxt_rate / observations);
            printf("Process Creation Rate = %lf processes/s\n", process_rate / observations);
            initial_write = clock();
            printLine();
        }
    }
    return 0;
}
