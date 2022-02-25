#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "config.h"

#define IPC_RESULT_ERROR (-1)

//https://www.geeksforgeeks.org/c-program-find-largest-element-array/
int largest(int arr[], int n) {
    int i ;

    int max = arr[0];

    for(i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }

        return max;
    }

}

//Bakery Algorithm
// void process_i(const int i) {

//     do{
//         choosing[i] = true;
//         number[i] = 1 + largest(number, 20);
//         choosing[i] = false;
//         int j = 0;
//         for(j; j < 20; j++) {
//             while(choosing[j]);
//             while(((number[j] != 0) && (number[j] < number[i])) || ((number[j] == number[i]) && (j < i)));
//         }

//         //critical section

//         number[i] = 0;

//         //remainder section

//     }
//     while(1);
// }

static int get_shared_block(char *filename, int size) {
    key_t key;

    key = ftok(filename, 0);
    if(key == IPC_RESULT_ERROR) {
        return IPC_RESULT_ERROR;
    }

    return shmget(key, size, 0644 | IPC_CREAT);
}

bool * attach_choosing_memory(char *filename, int size) {
    int shared_block_id = get_shared_block(filename, size);
    bool *result;

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    result = shmat(shared_block_id, NULL, 0);

    if(result == (bool *)IPC_RESULT_ERROR) {
        return NULL;
    }

    return result;
}

bool detach_choosing_memory(bool *memory) {
    return (shmdt(memory) != IPC_RESULT_ERROR);
}

bool destroy_choosing_memory(char *filename) {
    int shared_block_id = get_shared_block(filename, 0);

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}

int * attach_number_memory(char *filename, int size) {
    int shared_block_id = get_shared_block(filename, size);
    int *result;

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    result = shmat(shared_block_id, NULL, 0);

    if(result == (bool *)IPC_RESULT_ERROR) {
        return NULL;
    }

    return result;
}

bool detach_number_memory(int *memory) {
    return (shmdt(memory) != IPC_RESULT_ERROR);
}

bool destroy_number_memory(char *filename) {
    int shared_block_id = get_shared_block(filename, 0);

    if(shared_block_id == IPC_RESULT_ERROR) {
        return NULL;
    }

    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}



