/*
Name- Samudra Roy
Roll - 002211001114

*/

/*
Assignment Details - Consider a main process which creates three threads Th1, Th2, and Th3. The main process also creates two random quantities (X, Y), both less than 10. These two values will be placed by the main process in the shared memory (One variant of IPC Primitive)  that is accessible by all the three threads Th1, Th2 and Th3. The shared memory will be created by the main process also.  

For each pair of values (X,Y), it is required that some computations will be done by various threads. The thread Th1 will compute A (X*Y) and the thread Th2 will compute B (X*Y)/2). Similarly,  Th3 computes C (X+Y), Th2 again computes D ((X*Y)/(X+Y)), and finally Th1 computes E ((X+Y)(X-Y)). All these values are kept in the shared memory in a tabular fashion as shown below. 

The number of (X,Y) pairs will be taken as an argument from the CLI. It is the responsibility of the main process to populate required numbers of (X,Y)s in the shared memory. The program will only exit when all A,B,C etc. are computed for all given (X,Y) values. Before exiting, all (X,Y)s, As, Bs etc. should be displayed. 

Whenever, the threads complete one phase of computations (A, B, C, D and E), they will go for another pair of (X,Y) values; but they will start all together. This can be achieved by proper synchronization.

Use the proper shell command to display the Shared Memory Status/Info/Statistics and attach this sample output as a comment.

   Example:— 

    Input: N, number of random pairs
   Output Format:

   Pairs(X,Y)	|	A	|	B	|	C	|	D	|	E
      ——————————————————————————
        (1, 2) 	|	2	|	1	|	3	|	.66	|	-3
      ——————————————————————————
        (4, 1)  	|	4	|	2	|	5	|	.8	|	15
    ………


Input Description  - The program expects an integer N 

Output Description - The output consists of the results of various calculations performed by each thread .

Compilation Command (in Linux Bash Terminal) :- gcc  114_7.c   -pthread
Execution Command (in Linux Bash Terminal) :-  ./a.out

*/

/*
Sample Input &OUTPUT:  - 
Enter number of random pairs (max 10): 5

 

Processing pair (4, 3)

 

Processing pair (4, 3)

 

Processing pair (4, 6)

 

Processing pair (4, 5)

 

Processing pair (1, 1)

 

Pairs(X,Y) | A | B | C | D | E

————————————————————————————————————————————————————————————————————

(4,3) | 12.00 | 6.00 | 7.00 | 1.71 | 7.00

(4,3) | 12.00 | 6.00 | 7.00 | 1.71 | 7.00

(4,6) | 24.00 | 12.00 | 10.00 | 2.40 | -20.00

(4,5) | 20.00 | 10.00 | 9.00 | 2.22 | -9.00

(1,1) | 1.00 | 0.50 | 2.00 | 0.50 | 0.00

shell command to display the Shared Memory Status:
    ipcs -m

 

------ Shared Memory Segments --------

key shmid owner perms bytes nattch status

0x00000000 4 samudra 666 84 0


*/

#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include <unistd.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <sys/sem.h>

#include <time.h>

 

#define MAX_PAIRS 10

 

// Structure to hold computation results for each pair (X, Y)

typedef struct {

int X, Y;

float A, B, C, D, E;

} Computation;

 

// Shared memory and semaphore variables

Computation *shared_memory;

int shm_id;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

 

// Function prototypes for computation tasks

void *compute_A(void *arg);

void *compute_B(void *arg);

void *compute_C(void *arg);

void *compute_D(void *arg);

void *compute_E(void *arg);

 

void init_shared_memory(int num_pairs);

void cleanup_shared_memory();

 

int main() {

int num_pairs;

 

// Take number of random pairs as input

printf("Enter number of random pairs (max %d): ", MAX_PAIRS);

scanf("%d", &num_pairs);

if (num_pairs <= 0 || num_pairs > MAX_PAIRS) {

printf("Invalid number of pairs.\n");

return 1;

}

 

// Initialize random number generator

srand(time(NULL));

 

// Initialize shared memory

init_shared_memory(num_pairs);

 

// Create threads

pthread_t threads[5]; // 5 threads for A, B, C, D, and E computations

 

// Generate random (X, Y) pairs and store them in shared memory

for (int i = 0; i < num_pairs; i++) {

shared_memory[i].X = rand() % 9 + 1; // Random X between 1 and 9

shared_memory[i].Y = rand() % 9 + 1; // Random Y between 1 and 9

}

 

// Process each pair of (X, Y)

for (int i = 0; i < num_pairs; i++) {

// Lock the shared memory for this pair

pthread_mutex_lock(&mutex);

 

// Assign pair (X, Y) and perform computations

printf("\nProcessing pair (%d, %d)\n", shared_memory[i].X, shared_memory[i].Y);

 

// Create threads for computation

pthread_create(&threads[0], NULL, compute_A, (void *)&shared_memory[i]);

pthread_create(&threads[1], NULL, compute_B, (void *)&shared_memory[i]);

pthread_create(&threads[2], NULL, compute_C, (void *)&shared_memory[i]);

pthread_create(&threads[3], NULL, compute_D, (void *)&shared_memory[i]);

pthread_create(&threads[4], NULL, compute_E, (void *)&shared_memory[i]);

 

// Wait for all threads to finish

for (int j = 0; j < 5; j++) {

pthread_join(threads[j], NULL);

}

 

// Unlock shared memory after processing

pthread_mutex_unlock(&mutex);

}

 

// Print results in tabular format

printf("\nPairs(X,Y) | A | B | C | D | E\n");

printf("————————————————————————————————————————————————————————————————————\n");

for (int i = 0; i < num_pairs; i++) {

printf("(%d,%d) | %10.2f | %10.2f | %10.2f | %10.2f | %10.2f\n",

shared_memory[i].X, shared_memory[i].Y,

shared_memory[i].A, shared_memory[i].B,

shared_memory[i].C, shared_memory[i].D,

shared_memory[i].E);

}

 

// Cleanup shared memory

cleanup_shared_memory();

return 0;

}

 

// Compute A = X * Y

void *compute_A(void *arg) {

Computation *comp = (Computation *)arg;

comp->A = comp->X * comp->Y;

return NULL;

}

 

// Compute B = (X * Y) / 2

void *compute_B(void *arg) {

Computation *comp = (Computation *)arg;

comp->B = (comp->X * comp->Y) / 2.0;

return NULL;

}

 

// Compute C = X + Y

void *compute_C(void *arg) {

Computation *comp = (Computation *)arg;

comp->C = comp->X + comp->Y;

return NULL;

}

 

// Compute D = (X * Y) / (X + Y)

void *compute_D(void *arg) {

Computation *comp = (Computation *)arg;

if (comp->X + comp->Y != 0)

comp->D = (comp->X * comp->Y) / (float)(comp->X + comp->Y);

else

comp->D = 0.0;

return NULL;

}

 

// Compute E = (X + Y) * (X - Y)

void *compute_E(void *arg) {

Computation *comp = (Computation *)arg;

comp->E = (comp->X + comp->Y) * (comp->X - comp->Y);

return NULL;

}

 

// Initialize shared memory for storing computation results

void init_shared_memory(int num_pairs) {

key_t key = ftok("shmfile", 65); // Create a unique key

shm_id = shmget(key, num_pairs * sizeof(Computation), 0666 | IPC_CREAT);

if (shm_id == -1) {

perror("shmget failed");

exit(1);

}

 

// Attach shared memory

shared_memory = (Computation *)shmat(shm_id, NULL, 0);

if (shared_memory == (Computation *)-1) {

perror("shmat failed");

exit(1);

}

}

 

// Cleanup shared memory

void cleanup_shared_memory() {

// Detach shared memory

if (shmdt(shared_memory) == -1) {

perror("shmdt failed");

}

 

// Remove shared memory segment

if (shmctl(shm_id, IPC_RMID, NULL) == -1) {

perror("shmctl failed");

}

}