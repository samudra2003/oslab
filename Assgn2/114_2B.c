/*

 Name - Samudra Roy 
 Roll - 002211001114
*/

/*

 Assignment Details - Create two processes. Transfer 1GB file from process1 to process2 using a
 FIFO. Now, transfer the same file from process2 to process1 using another
 FIFO. Now, compare the two files to make sure that the same file has returned
 back. Also, print the time required to do this double transfer. Attach this output
 to the source file as a comment.
 To create FIFO, you can either use shell command or system call.
 To create a large file you can use the relevant command.
 Use „ls –l‟ command to show the FIFO and the large file. Attach this output to
 the source file as a comment.

 Input Description - No input

 Output Description - The time required for the round about travel is printed on the screen.

*/

/*

 Compilation Command - gcc  114_2B.c 
 Execution Command - ./a.out

*/

/*

 Sample Input - No input
 Sample Output -
 
 >>> Opened the file initialFile.txt for reading

>>> Writing to FIFO fifo1

>>> Writing to FIFO fifo1 is completed

>>> Opened the file receivedFile.txt for writing

>>> Reading from FIFO fifo1

>>> Reading from fifo2 and writing to the file receivedBackFile.txt to compare received back file with the initial file sent by process1

>>> Writing to FIFO fifo2 from the file receivedFile.txt

>>> Writing to fifo2 is completed

>>> File received from process 1

>>> Writing to FIFO fifo2 from the file receivedFile.txt

>>> Writing to fifo2 is completed

>>> Both the files are same, there is no mismatch!

>>> The round-about time for transferring the file between process1 and process2 and back to process1 is 24 milliseconds

 

Output of 'ls – l':

total 60

-rw-rw-r-- 1 samudra samudra 26308 Nov 11 16:27 114_1B.c.

-rwxrwxr-x 1 samudra samudra 16672 Nov 11 16:57 a.out

prw-rw-r-- 1 samudra samudra 0 Nov 11 16:55 fifo1

prw-rw-r-- 1 samudra samudra 0 Nov 11 16:55 fifo2

-rw-rw-r-- 1 samudra samudra 0 Nov 11 16:56 initialFile.txt

-rw-rw-r-- 1 samudra samudra 0 Nov 11 16:57 receivedBackFile.txt

-rw-rw-r-- 1 samudra samudra 0 Nov 11 16:57 receivedFile.txt


*/

// Header files
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// Method to get the time elapsed since the invoking of this function
long getTimeElapsed() {
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

// Method to compare two files and check if there is any mismatch or not
void compareFiles(FILE *firstFile, FILE *secondFile) {
    char firstFileChar = getc(firstFile);
    char secondFileChar = getc(secondFile);
    
    int lineNumber = 1;
    int totalErrors = 0;
    
    // Loop through both files character by character
    while (firstFileChar != EOF && secondFileChar != EOF) {
        if (firstFileChar == '\n' && secondFileChar == '\n') {
            lineNumber++;
        }
        // Check if there is a mismatch at any position
        if (firstFileChar != secondFileChar) {
            totalErrors++;
            printf(">>> Mismatch occurred at line number : %d\n", lineNumber);
        }
        
        firstFileChar = getc(firstFile);
        secondFileChar = getc(secondFile);
    }
    
    if (totalErrors == 0) {
        printf(">>> Both the files are same, there is no mismatch!\n");
    }
}

int main() {
    int startingTime = getTimeElapsed(); // Store the start time for measuring the round-trip duration
    
    // Define FIFO names for inter-process communication
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    
    // Create named pipes (FIFOs) for process communication
    mknod(fifo1, S_IFIFO | 0666, 0);
    mknod(fifo2, S_IFIFO | 0666, 0);
    
    // Fork the process to create a parent-child process setup
    int processID = fork();
    
    if (processID == 0) { // Child process
        // Read data from fifo1, write it into a file, and then send it back to the parent process
        
        int fd = open(fifo1, O_RDONLY); // Open fifo1 for reading
        const char *receivedFile = "receivedFile.txt";
        FILE *receivedfp = fopen(receivedFile, "w");
        
        if (receivedfp == NULL)
            printf(">>> Failed to open the file %s for writing\n", receivedFile);
        else
            printf(">>> Opened the file %s for writing\n", receivedFile);
        
        if (fd > 0) {
            printf(">>> Reading from FIFO fifo1\n");
            char str[100];
            // Read from fifo1 and write the data into receivedFile
            while (read(fd, str, sizeof(str))) {
                fputs(str, receivedfp);
            }
            printf(">>> File received from process 1\n");
            close(fd); // Close fifo1 after reading
        } else {
            printf(">>> Failed to open FIFO fifo1 for reading\n");
        }
        
        fclose(receivedfp); // Close the receivedFile
        
        // Send the received file content back to the parent process using fifo2
        receivedfp = fopen(receivedFile, "r");
        fd = open(fifo2, O_WRONLY);
        if (fd > 0) {
            printf(">>> Writing to FIFO fifo2 from the file %s\n", receivedFile);
            char buffer[100];
            // Read from receivedFile and write the data to fifo2
            while (fgets(buffer, sizeof(buffer), receivedfp)) {
                int len = strlen(buffer);
                int n = write(fd, buffer, len);
                if (n != len)
                    perror("write");
            }
            printf(">>> Writing to fifo2 is completed\n");
        }
    } else { // Parent process
        // Create a large file (1GB) named 'initialFile.txt' using shell command:
        // Command : fallocate -l 1G initialFile.txt
        const char *initialFile = "initialFile.txt";
        FILE *fp = fopen(initialFile, "r");
        
        if (fp == NULL)
            printf(">>> Failed to open the file %s for reading\n", initialFile);
        else
            printf(">>> Opened the file %s for reading\n", initialFile);
        
        int fd = open(fifo1, O_WRONLY); // Open fifo1 for writing
        if (fd > 0) {
            printf(">>> Writing to FIFO fifo1\n");
            char str[100];
            // Write data from initialFile to fifo1 for the child process to read
            while (fgets(str, sizeof(str), fp)) {
                int len = strlen(str);
                int n = write(fd, str, len);
                if (n != len)
                    perror("write");
            }
            printf(">>> Writing to FIFO fifo1 is completed\n");
        } else {
            printf(">>> Failed to open FIFO fifo1 for writing\n");
        }
        
        close(fd); // Close fifo1
        fclose(fp); // Close initialFile
        
        // Receive the file back from fifo2 and store it in receivedBackFile.txt for comparison
        fd = open(fifo2, O_RDONLY); // Open fifo2 for reading
        const char *receivedBackFile = "receivedBackFile.txt";
        FILE *receivedbackfp = fopen(receivedBackFile, "w");
        
        if (fd > 0) {
            printf(">>> Reading from fifo2 and writing to the file %s to compare received back file with the initial file sent by process1\n", receivedBackFile);
            char buffer[100];
            // Read data from fifo2 and write to receivedBackFile
            while (read(fd, buffer, sizeof(buffer))) {
                fputs(buffer, receivedbackfp);
            }
        } else {
            perror("read");
        }
        
        close(fd); // Close fifo2
        fclose(receivedbackfp); // Close receivedBackFile
        
        int endingTime = getTimeElapsed(); // Store the end time for calculating the round-trip duration
        
        // Calculate the total time taken for the round-trip file transfer
        int totalTimeTaken = endingTime - startingTime;
        
        // Compare initialFile and receivedBackFile to verify the integrity of the transferred file
        fp = fopen(initialFile, "r");
        receivedbackfp = fopen(receivedBackFile, "r");
        compareFiles(fp, receivedbackfp);
        
        fclose(fp); // Close initialFile
        fclose(receivedbackfp); // Close receivedBackFile
        
        printf(">>> The round-about time for transferring the file between process1 and process2 and back to process1 is %d milliseconds\n", totalTimeTaken);
    }
    
    return 0;
}
