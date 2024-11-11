/*

 Name - Samudra Roy
 Roll - 002211001114

*/

/*

Assignment Details :- Objective of this programming assignment is to use mmap() call and observe page-fault
                      using the ‘sar’ command. A big file (about 8GB) should be created using the ‘fallocate’ command.
                      This big file should be written with a single integer value (say X) at a specific offset (say F).
                      Both the integer value and the offset should be generated using a random function.
                      Please do remember this random function should generate a quantity anywhere between 0 and 8G.
                      The above big file should also be mapped in the virtual address space using mmap() call.
                      Once it is mapped, the data should be read from the same specific offset (F).
                      Now, if the data read is X`; then verify that X and X` are the same.
                      In case of verification failure, an error message is to be printed.
                      Note that, the offset value F can be anywhere between 0 and 8G.
                      This sequence of writing and reading data to/from a specific offset and also verification should
                      be put in a while loop to go forever.
                      In another terminal execute the command ‘sar –B 1 1000’ to observe for the page fault.
                      This command should be started before the above program is put under execution.
                      So, one can observe that the page faults are increasing, once the above program starts executing.
                      The output of the program and the ‘sar’ command should be pasted as a comment at
                      the beginning of the program file.

Input Description  :- The name of the file to be transferred is entered as a command line input for execution of the program.


Output Description :-

    >>  The method prints the value written in the offset of the buffer and also the value read from the same offset
    >>  The method also prints whether the value written and read are the same or not


*/

/*

Sample Input :- No input

 

NOTE :- Use Control + C to exit from the infinite loop

 

Sample Output :- (PROGRAM OUTPUT)

 

The Value Written is : 986511773

The Value Read is : 986511773

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1063608692

The Value Read is : 1063608692

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 434293475

The Value Read is : 434293475

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 830071428

The Value Read is : 830071428

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1566549882

The Value Read is : 1566549882

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1893104631

The Value Read is : 1893104631

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1143586092

The Value Read is : 1143586092

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 135992242

The Value Read is : 135992242

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1269225863

The Value Read is : 1269225863

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1412380816

The Value Read is : 1412380816

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 2106873725

The Value Read is : 2106873725

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1389131656

The Value Read is : 1389131656

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 1965201656

The Value Read is : 1965201656

The value that is read and written are the same!

---------------------------------------------

The Value Written is : 230586627

The Value Read is : 230586627

The value that is read and written are the same!

---------------------------------------------

 

Output :- (OUTPUT OF SAR COMMAND)

Linux Bash Command :- sar -B 1 1000

 

Linux 6.8.0-48-generic (samudra) 11/11/24 _x86_64_ (6 CPU)

 

05:55:59 PM IST pgpgin/s pgpgout/s fault/s majflt/s pgfree/s pgscank/s pgscand/s pgsteal/s %vmeff

05:56:01 PM IST 0.00 0.00 294.29 0.00 146.67 0.00 0.00 0.00 0.00

05:56:02 PM IST 4.00 4.00 168.00 0.00 233.00 0.00 0.00 0.00 0.00

05:56:03 PM IST 0.00 0.00 66.34 0.00 95.05 0.00 0.00 0.00 0.00

05:56:04 PM IST 0.00 0.00 132.00 0.00 229.00 0.00 0.00 0.00 0.00

05:56:05 PM IST 0.00 0.00 131.00 0.00 144.00 0.00 0.00 0.00 0.00

05:56:06 PM IST 0.00 36.67 112.50 0.00 51.67 0.00 0.00 0.00 0.00

05:56:07 PM IST 0.00 7.69 131.73 0.00 78.85 0.00 0.00 0.00 0.00

05:56:08 PM IST 0.00 0.00 400.99 0.00 373.27 0.00 0.00 0.00 0.00

^C

 

Average: 0.48 6.74 178.58 0.00 165.70 0.00 0.00 0.00 0.00

 

*/


// Header Files
#include <fcntl.h>         // For file control operations (e.g., open)
#include <stdlib.h>        // For standard library functions (e.g., rand, exit)
#include <stdio.h>         // For input-output operations (e.g., printf)
#include <sys/mman.h>      // For memory mapping (e.g., mmap)
#include <sys/stat.h>      // For file status (e.g., fstat)
#include <sys/types.h>     // For data types (e.g., off_t)
#include <time.h>          // For generating random seeds with time()
#include <unistd.h>        // For file operations (e.g., close)

#define LOWER 0            // LOWER bound for random integer generator
#define UPPER 8589934592   // UPPER bound for random integer generator (8 GB range)

char *addressOfMapBuffer;  // Stores the address of the memory-mapped buffer

// Function to print a separator line for output clarity
void printLine()
{
    printf("---------------------------------------------\n");
}

// Function to read an integer at a specified offset within the memory-mapped file
// Returns the integer read from the file
int readInteger(unsigned long offset)
{
    unsigned long readValue;  // Variable to store the read integer value

    // Convert the value at address (addressOfMapBuffer + offset) to an integer
    sscanf(addressOfMapBuffer + offset, "%lu", &readValue);
    printf("The Value Read is : %-10lu\n", readValue);
    
    return readValue;
}

// Function to write an integer to a specified offset within the memory-mapped file
int writeInteger(unsigned long offset, unsigned long value)
{
    printf("The Value Written is : %-10lu\n", value);

    // Write the integer value to address (addressOfMapBuffer + offset)
    sprintf(addressOfMapBuffer + offset, "%lu", value);
}

// Function to generate a random unsigned long integer within the specified range (LOWER to UPPER)
unsigned long randomIntegerGenerator()
{
    unsigned long lowerRange = LOWER;
    unsigned long upperRange = UPPER;
    
    // Generate a random number within the range using modulo
    unsigned long randomNumber = lowerRange + (rand() % (upperRange - lowerRange + 1));
    return randomNumber;
}

int main(int argc, char **argv)
{
    // Check if the user provided the correct number of arguments
    if (argc != 2)
    {
        printf("Sufficient number of arguments are not provided!\n");
        printf("The expected execution command is : ./a.out <file_name>\n");
        exit(1);
    }

    // Opening the user-specified file with read and write permissions
    int FILE = open(argv[1], O_RDWR, S_IRUSR | S_IWUSR);

    // Structure to hold file information
    struct stat sb;

    // Getting the information (size, permissions, etc.) of the file into the sb structure
    if (fstat(FILE, &sb) == -1)
    {
        perror("Some ERROR occured while getting the file size!");
        exit(1);
    }

    // Mapping the file into virtual memory with read and write permissions, shared with the file
    if ((addressOfMapBuffer = (char *)mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, FILE, 0)) == MAP_FAILED)
    {
        perror("Some ERROR occured while mapping the file!");
        exit(2);
    }

    // Set the seed for random number generation to current time to ensure random values
    srand(time(NULL));
    
    unsigned long offset, writtenValue, readValue; // Variables for storing offset, written, and read values

    // Infinite loop for continuously writing and reading values at random offsets in the file
    while (1)
    {
        // Generate a random integer to write
        writtenValue = randomIntegerGenerator();

        // Generate a random offset within the file's address space
        offset = randomIntegerGenerator();

        // Write the random integer to the generated offset in the memory-mapped file
        writeInteger(offset, writtenValue);

        // Read the integer at the same offset to verify it was written correctly
        readValue = readInteger(offset);

        // Compare the written and read values to verify they match
        if (writtenValue == readValue)
        {
            printf("The value that is read and written are the same!\n");
            printLine();
        }
        else
        {
            printf("The value that is read and written are NOT the same!\n");
            printLine();
        }
    }

    return 0; // Exit the program
}
