/*

  Name - Samudra Roy
  Roll - 002211001114
  
*/

/*

Assignment Details - Create two processes. Transfer 1GB file from process1 to process2 using a
                     Socket. Now, transfer that file from process2 to process1 using the same
                     Socket.Now, compare the two files to make sure that the same file has returned back.
                     Also, print the time required to do this double transfer. Attach this output to the
                     source file as a comment. Please note that, you can see the socket which your program creates. There
                     are also various bash shell commands available to see the sockets created by
                     the program. So, once your program creates the socket, make sure you use
                     proper command to see the socket info and paste that output as a comment in
                     your source file.

Input Description  - No input

Output Description - The time required for the round about travel is printed on the screen.

*/



/*


Command for creating a 1GB file :- fallocate -l 1G initialBigFile.txt

NOTE - This file has to be created in the same directory as that of the program

 

Compilation Command (in Linux Bash Terminal) :- gcc 114_3.c

 

Execution Command (in Linux Bash Terminal) :- ./a.out initialBigFile.txt

 

*/

/*

Sample Input - No input

Sample Output -

 

Output :- (PROGRAM OUTPUT)


>>> Server side socket is created successfully!

>>> Server bind to server is suceessful!

>>> Server is now listening suceessfully at port 8069

>>> Client side socket is created successfully!

>>> Client connected to the server successfully!

>>> Server connected to the client successfully!

>>> Comparing the files...

>>> The files are compared and found to be the same

>>> The round-about time for the file transfer is : 323 milliseconds

>>> Cleaning the created files!

>>> The created files are cleaned!

 

Output :- (CHECKING THE SOCKET DETAILS)

Linux Bash Command :- ss -t -a

State           Recv-Q       Send-Q                    Local Address:Port                     Peer Address:Port       Process       
LISTEN          0            1024                            0.0.0.0:mysql                         0.0.0.0:*                        
LISTEN          0            128                             0.0.0.0:25672                         0.0.0.0:*                        
LISTEN          0            4096                      127.0.0.53%lo:domain                        0.0.0.0:*                        
LISTEN          0            5                               0.0.0.0:44321                         0.0.0.0:*                        
LISTEN          0            128                             0.0.0.0:44322                         0.0.0.0:*                        
LISTEN          0            128                             0.0.0.0:44323                         0.0.0.0:*                        
LISTEN          0            32                        192.168.122.1:domain                        0.0.0.0:*                        
LISTEN          0            5                               0.0.0.0:4330                          0.0.0.0:*                        
LISTEN          0            511                             0.0.0.0:http                          0.0.0.0:*                        
LISTEN          0            511                             0.0.0.0:81                            0.0.0.0:*                        
LISTEN          0            128                             0.0.0.0:ssh                           0.0.0.0:*                        
LISTEN          0            70                            127.0.0.1:33060                         0.0.0.0:*                        
LISTEN          0            10                            127.0.0.1:6640                          0.0.0.0:*                        
LISTEN          0            128                           127.0.0.1:ipp                           0.0.0.0:*                        
LISTEN          0            1024                          127.0.0.1:11211                         0.0.0.0:*                        
TIME-WAIT       0            0                             127.0.0.1:53202                       127.0.0.1:epmd                     
ESTAB           0            0                             10.0.2.15:59214                   34.107.243.93:https                    
TIME-WAIT       0            0                             127.0.0.1:8069                        127.0.0.1:52116                    
ESTAB           0            0                             127.0.0.1:44904                       127.0.0.1:epmd                     
LAST-ACK        0            1                  192.168.1.105%enp0s8:33562                    91.189.91.98:http  



Output :-

Linux Bash Command :- ls – l

 ls -l
total 2578472
-rwxrwxr-x 1 samudra samudra      21424 Nov 11 18:13 a.out
-rw-rw-r-- 1 samudra samudra 1073741824 Nov 11 18:12 initialBigFile.txt
-rw-rw-r-- 1 samudra samudra  492814336 Nov 11 18:13 process1_temporary_file
-rw-rw-r-- 1 samudra samudra 1073741824 Nov 11 18:13 process2_temporary_file
-rw-rw-r-- 1 samudra samudra      18676 Nov 11 17:18 114_3.c


*/

// Header files
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// Macro definitions for temporary file names, max buffer size, localhost IP, and port number
#define TEMP_FILE1 "process1_temporary_file"
#define TEMP_FILE2 "process2_temporary_file"
#define MAXLEN 1024
#define LOCALHOST "127.0.0.1" // IP address of the local host
#define PORT 8069 // Port number

// Method to get the time elapsed in milliseconds since invoking this function
long getTimeElapsed()
{
    struct timeval timeElapsed;
    gettimeofday(&timeElapsed, NULL);
    return timeElapsed.tv_sec * 1000 + timeElapsed.tv_usec / 1000;
}

// Method for cleaning up temporary files created during execution
void cleanFiles()
{
    printf(">>> Cleaning the created files!\n");
    remove(TEMP_FILE1);
    remove(TEMP_FILE2);
    remove("initialBigFile.txt");
    printf(">>> The created files are cleaned!\n");
}

// Method to compare two files and check for any mismatch
int compareFiles(char *firstFile, char *secondFile)
{
    int fileID1, fileID2; // File IDs for both files

    // Open the first file
    if ((fileID1 = open(firstFile, O_RDONLY)) == -1)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    // Open the second file
    if ((fileID2 = open(secondFile, O_RDONLY)) == -1)
    {
        perror(">>> Error in opening the file!\n");
        close(fileID1);
        return -1;
    }

    // Buffers to store file contents for comparison
    char buffer1[MAXLEN];
    char buffer2[MAXLEN];

    int returnValue = 1;

    while (true)
    {
        // Read data into buffers for comparison
        int len1 = read(fileID1, buffer1, MAXLEN);
        int len2 = read(fileID2, buffer2, MAXLEN);

        // Check for read errors
        if (len1 == -1 || len2 == -1)
        {
            perror(">>> Error in reading the file!\n");
            returnValue = -1;
            break;
        }

        // If lengths differ, files are not identical
        if (len1 != len2)
        {
            returnValue = 0;
            break;
        }

        // Reached end of both files, they match
        if (len1 == 0)
        {
            break;
        }

        // Compare data byte-by-byte
        for (int i = 0; i < len1; i++)
        {
            if (buffer1[i] != buffer2[i])
            {
                returnValue = 0; // Files are different
                break;
            }
        }

        if (returnValue == 0)
        {
            break;
        }
    }

    // Close both files
    close(fileID1);
    close(fileID2);

    return returnValue;
}

// Method to get the file size in bytes
long getFileSize(char *fileName)
{
    FILE *file;

    // Open the file and check for errors
    if ((file = fopen(fileName, "r")) == NULL)
    {
        perror(">>> Error in fopen. Unable to determine file size\n");
        return -1;
    }

    // Move pointer to the end of the file
    fseek(file, 0, SEEK_END);

    // Get size of the file
    long fileSize = ftell(file);

    // Close the file
    fclose(file);

    return fileSize;
}

// Method for sending a file via socket
int sendFile(char *sourceFile, int destination)
{
    long fileSize = getFileSize(sourceFile);

    if (fileSize == -1)
    {
        return -1;
    }

    // Prepare buffer for sending data
    char buffer[MAXLEN];
    *((long *)buffer) = fileSize;

    // Send the file size to the destination
    if (send(destination, buffer, sizeof(long), 0) < 0)
    {
        perror(">>> Error in sending the file!\n");
        return -1;
    }

    int fileID = open(sourceFile, O_RDONLY);

    if (fileID == -1)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    int returnValue = 1;

    // Loop until entire file is sent
    while (1)
    {
        long bufferRead = read(fileID, buffer, MAXLEN);

        if (bufferRead < 0)
        {
            perror(">>> Error in reading the file!\n");
            returnValue = -1;
            break;
        }

        if (bufferRead == 0) // End of file
            break;

        if (send(destination, buffer, bufferRead, 0) == -1)
        {
            returnValue = -1;
            break;
        }
    }

    // Close the file
    close(fileID);
    return returnValue;
}

// Method for receiving a file via socket
int receiveFile(char *destinationFile, int source)
{
    char buffer[MAXLEN];

    // Receive the file size
    if (recv(source, buffer, sizeof(long), 0) < 0)
    {
        perror(">>> Error in receiving the file!\n");
        return -1;
    }

    long fileSize = *((long *)buffer);

    int destinationID = open(destinationFile, O_WRONLY | O_CREAT, 0666);

    if (destinationID < 0)
    {
        perror(">>> Error in opening the file!\n");
        return -1;
    }

    long toReceive = fileSize;

    int returnValue = 1;

    // Loop until the entire file is received
    while (toReceive > 0)
    {
        int bytesRead = recv(source, buffer, MAXLEN, 0);

        if (bytesRead < 0)
        {
            perror(">>> Error in reading!\n");
            returnValue = -1;
            break;
        }

        if (write(destinationID, buffer, bytesRead) < 0)
        {
            perror(">>> Error in writing!\n");
            returnValue = -1;
            break;
        }

        toReceive -= bytesRead;
    }

    close(destinationID);
    return returnValue;
}

// Creating the server
int createServer()
{
    int serverID = socket(AF_INET, SOCK_STREAM, 0);

    if (serverID < 0)
    {
        perror(">>> Unable to create server side socket!\n");
        return serverID;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bzero(&server_address.sin_zero, 8);

    if (bind(serverID, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror(">>> Error in binding to the server!\n");
        close(serverID);
        return -1;
    }

    if (listen(serverID, 1) < 0)
    {
        perror(">>> Error in server listening!\n");
        close(serverID);
        return -1;
    }

    return serverID;
}

// Method to accept connection from client
int acceptConnection(int serverID)
{
    int connectionfd;
    struct sockaddr_in clientAddress;
    unsigned int addressLength = sizeof(clientAddress);

    connectionfd = accept(serverID, (struct sockaddr *)&clientAddress, &addressLength);

    if (connectionfd < 0)
    {
        perror(">>> Server could not accept connection!\n");
        return -1;
    }

    return connectionfd;
}

// Client-side connection method
int connectToServer()
{
    int clientID = socket(AF_INET, SOCK_STREAM, 0);

    if (clientID < 0)
    {
        perror(">>> Error in creating client side socket!\n");
        return clientID;
    }

    struct sockaddr_in clientAddress;
    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(PORT);
    clientAddress.sin_addr.s_addr = inet_addr(LOCALHOST);
    bzero(&clientAddress.sin_zero, 8);

    if (connect(clientID, (struct sockaddr *)&clientAddress, sizeof(clientAddress)) < 0)
    {
        perror(">>> Client could not connect!\n");
        close(clientID);
        return -1;
    }

    return clientID;
}

// Process1 (server-side function)
void process1(char *sourceFile)
{
    int serverID = createServer();

    if (serverID < 0)
    {
        perror(">>> Creation of server failed!\n");
        exit(EXIT_FAILURE);
    }

    int connectID = acceptConnection(serverID);

    if (connectID < 0)
    {
        perror(">>> Connection failed!\n");
        exit(EXIT_FAILURE);
    }

    long startingTime = getTimeElapsed();

    if (sendFile(sourceFile, connectID) < 0)
    {
        close(connectID);
        close(serverID);
        exit(EXIT_FAILURE);
    }

    if (receiveFile(TEMP_FILE1, connectID) < 0)
    {
        close(connectID);
        close(serverID);
        exit(EXIT_FAILURE);
    }

    long endingTime = getTimeElapsed();

    close(connectID);
    close(serverID);

    int result = compareFiles(sourceFile, TEMP_FILE1);

    if (result < 0)
    {
        perror(">>> The file could not be read!\n");
        exit(EXIT_FAILURE);
    }
    else if (result == 0)
    {
        printf(">>> Files do not match!\n");
        exit(EXIT_FAILURE);
    }

    printf(">>> Successfully completed in %ld ms!\n", endingTime - startingTime);
}

// Process2 (client-side function)
void process2()
{
    int connectID = connectToServer();

    if (connectID < 0)
    {
        perror(">>> Error in connection creation!\n");
        exit(EXIT_FAILURE);
    }

    if (receiveFile(TEMP_FILE2, connectID) < 0)
    {
        close(connectID);
        exit(EXIT_FAILURE);
    }

    if (sendFile(TEMP_FILE2, connectID) < 0)
    {
        close(connectID);
        exit(EXIT_FAILURE);
    }

    close(connectID);
}

// Main function
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf(">>> Correct format: ./process <source_file>\n");
        exit(EXIT_FAILURE);
    }

    if (fork() == 0)
    {
        process1(argv[1]);
    }
    else
    {
        sleep(1); // Ensure process1 has time to initialize
        process2();
        wait(NULL);
        cleanFiles();
    }

    return 0;
}
