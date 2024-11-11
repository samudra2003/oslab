
/*

 Name - Samudra Roy
 Roll - 002211001114


*/

/*
Assignment Details - The objective of this assignment is to create a deadlock. For this purpose
define two global variables (Total_1 and Total_2) and initialize both of them to 1000. You should
also have two mutexes to protect these two global variables. You need to create two threads also.
The function of each of the threads is to generate a random quantity (not more than 50) and subtract that
quantity from one of the Total and add that quantity to the other Total. While manipulating the Totals, 
each Thread should lock both the mutex and then unlock it after changing the Totals.
The order of locking and unlocking the Mutex is very important, because that’s what creates a Deadlock.
Once you correctly identify this order, you should upload the program. Also, include that information (as comment in your source file) 
how to avoid this kind of Deadlock.
If these two Threads, Two Totals and Two Mutex are not good enough for Deadlock;
Then you need to create one more Thread, one more Total and and one more Mutex; and carry on the same experiment.
Make sure there are enough printf in your program so that it can be clearly understood that there is a Deadlock.
One way to ensure enough printf is to display the total of Total_1 and Total_2 all the time after every operation on it.


Input Description  - No input
Output Description - Deadlock condition
*/

/*
Compilation Command (in Linux Bash Terminal) :- gcc 114_5.c  -pthread
Execution Command (in Linux Bash Terminal) :- ./a.out
*/

/*
Deadlock Sequence -

   In the provided code, deadlock is prevented by following a consistent locking order across both threadFunc1 and threadFunc2.
   Specifically, each thread locks mtx1 first, followed by mtx2, and releases them in the reverse order (mtx2 first, then mtx1).
   This approach ensures that both threads acquire the mutexes in the same sequence, thus eliminating the possibility of a cyclic
   dependency where one thread waits indefinitely for a resource locked by the other.
   If we were to intentionally create a deadlock, we could alter the locking order in one of the threads.
   For instance, if threadFunc2 were modified to lock mtx2 before mtx1, then a situation could arise where
   threadFunc1 locks mtx1 and waits for mtx2, while threadFunc2 simultaneously locks mtx2 and waits for mtx1.
   This scenario creates a cycle where each thread waits on the other, resulting in a deadlock.
   By maintaining a consistent locking order as demonstrated in the code,
   we avoid this cyclic dependency and ensure smooth execution without deadlock.


*/

/*


Sample Input  - No input
Sample Output -
Output :- (PROGRAM OUTPUT)
Thread 2 - Total_1: 964, Total_2: 1036, Sum: 2000
Thread 1 - Total_1: 922, Total_2: 1078, Sum: 2000
Thread 2 - Total_1: 951, Total_2: 1049, Sum: 2000
Thread 2 - Total_1: 963, Total_2: 1037, Sum: 2000
Thread 1 - Total_1: 925, Total_2: 1075, Sum: 2000
Thread 2 - Total_1: 954, Total_2: 1046, Sum: 2000
Thread 1 - Total_1: 924, Total_2: 1076, Sum: 2000
Thread 2 - Total_1: 968, Total_2: 1032, Sum: 2000
Thread 1 - Total_1: 935, Total_2: 1065, Sum: 2000
Thread 2 - Total_1: 939, Total_2: 1061, Sum: 2000
Thread 1 - Total_1: 928, Total_2: 1072, Sum: 2000
Thread 2 - Total_1: 937, Total_2: 1063, Sum: 2000
Thread 1 - Total_1: 926, Total_2: 1074, Sum: 2000
Thread 2 - Total_1: 937, Total_2: 1063, Sum: 2000
Thread 1 - Total_1: 928, Total_2: 1072, Sum: 2000
Thread 1 - Total_1: 896, Total_2: 1104, Sum: 2000
Thread 2 - Total_1: 944, Total_2: 1056, Sum: 2000
Thread 1 - Total_1: 936, Total_2: 1064, Sum: 2000
Thread 2 - Total_1: 958, Total_2: 1042, Sum: 2000
Thread 1 - Total_1: 930, Total_2: 1070, Sum: 2000
Thread 2 - Total_1: 980, Total_2: 1020, Sum: 2000
Thread 2 - Total_1: 1010, Total_2: 990, Sum: 2000
Thread 1 - Total_1: 964, Total_2: 1036, Sum: 2000
Thread 1 - Total_1: 956, Total_2: 1044, Sum: 2000
Thread 2 - Total_1: 975, Total_2: 1025, Sum: 2000
^Z
[1]+  Stopped                 ./a.out



Deadlock Avoidance Program :


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global variables to hold the totals
int Total_1 = 1000;
int Total_2 = 1000;

// Mutexes to protect access to each total
pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

// Function executed by the first thread
void* threadFunc1(void* arg) {
    while (1) {
        // Generate a random quantity between 1 and 50
        int quantity = rand() % 50 + 1;

        // Lock mtx1 first, then mtx2 to avoid deadlock
        pthread_mutex_lock(&mtx1);
        pthread_mutex_lock(&mtx2);

        // Perform the operation:
        // Subtract the quantity from Total_1 and add it to Total_2
        Total_1 -= quantity;
        Total_2 += quantity;

        // Print the updated totals and their sum
        printf("Thread 1 - Total_1: %d, Total_2: %d, Sum: %d\n", Total_1, Total_2, Total_1 + Total_2);

        // Unlock the mutexes in reverse order of locking
        pthread_mutex_unlock(&mtx2);
        pthread_mutex_unlock(&mtx1);

        // Small delay to allow thread switching
        usleep(100000);
    }
    return NULL;
}

// Function executed by the second thread
void* threadFunc2(void* arg) {
    while (1) {
        // Generate a random quantity between 1 and 50
        int quantity = rand() % 50 + 1;

        // Lock mtx1 first, then mtx2 to avoid deadlock (consistent order with threadFunc1)
        pthread_mutex_lock(&mtx1);
        pthread_mutex_lock(&mtx2);

        // Perform the operation:
        // Subtract the quantity from Total_2 and add it to Total_1
        Total_2 -= quantity;
        Total_1 += quantity;

        // Print the updated totals and their sum
        printf("Thread 2 - Total_1: %d, Total_2: %d, Sum: %d\n", Total_1, Total_2, Total_1 + Total_2);

        // Unlock the mutexes in reverse order of locking
        pthread_mutex_unlock(&mtx2);
        pthread_mutex_unlock(&mtx1);

        // Small delay to allow thread switching
        usleep(100000);
    }
    return NULL;
}

int main() {
    // Seed the random number generator to get different values on each run
    srand(time(NULL));

    // Declare thread variables
    pthread_t t1, t2;

    // Create the first thread and start threadFunc1
    pthread_create(&t1, NULL, threadFunc1, NULL);

    // Create the second thread and start threadFunc2
    pthread_create(&t2, NULL, threadFunc2, NULL);

    // Join the threads (this is not reached due to infinite loops in the threads)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

*/


// Deadlock Creation code:-
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int Total_1 = 1000;
int Total_2 = 1000;
pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;

void *threadFunc1(void *arg)
{
    while (1)
    {
        int quantity = rand() % 50 + 1;

        // Lock mtx1 first, then mtx2
        pthread_mutex_lock(&mtx1);
        usleep(10000); // Delay to increase the chance of deadlock
        pthread_mutex_lock(&mtx2);

        // Perform the operation
        Total_1 -= quantity;
        Total_2 += quantity;

        // Print the updated totals
        printf("Thread 1 - Total_1: %d, Total_2: %d, Sum: %d\n", Total_1, Total_2, Total_1 + Total_2);

        // Unlock mutexes
        pthread_mutex_unlock(&mtx2);
        pthread_mutex_unlock(&mtx1);

        usleep(100000); // Small delay to allow thread switching
    }
    return NULL;
}

void *threadFunc2(void *arg)
{
    while (1)
    {
        int quantity = rand() % 50 + 1;

        // Lock mtx2 first, then mtx1 (opposite order to create deadlock)
        pthread_mutex_lock(&mtx2);
        usleep(10000); // Delay to increase the chance of deadlock
        pthread_mutex_lock(&mtx1);

        // Perform the operation
        Total_2 -= quantity;
        Total_1 += quantity;

        // Print the updated totals
        printf("Thread 2 - Total_1: %d, Total_2: %d, Sum: %d\n", Total_1, Total_2, Total_1 + Total_2);

        // Unlock mutexes
        pthread_mutex_unlock(&mtx1);
        pthread_mutex_unlock(&mtx2);

        usleep(100000); // Small delay to allow thread switching
    }
    return NULL;
}

int main()
{
    srand(time(NULL)); // Seed the random number generator

    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, threadFunc1, NULL);
    pthread_create(&t2, NULL, threadFunc2, NULL);

    // Join the threads (although they'll get stuck in deadlock)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}

