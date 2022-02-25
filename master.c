#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "config.h"

int main(int argc, char* argv[]) {
    
    //declarations
    int num_process = 20;
    int time = 0;

    //parse command line
    if(argc == 4) {
        time = atoi(argv[2]);
        num_process = atoi(argv[3]);
    } 
    else {
        printf("Error: wrond command line input\n");
        exit(1);
    }

    //take out later
    printf("%d\n", time);
    printf("%d\n", num_process);

    //check the number of processes is not more than 20
    if(num_process > 20) {
        printf("Error: number of processes cannot exceed more than 20\n");
        exit(1);
    }

    //setup shared memory
    choosing = attach_choosing_memory(FILENAME, BLOCK_SIZE);
    number = attach_number_memory(FILENAME, BLOCK_SIZE);
    // if(choosing == NULL || number == NULL) {
    //     printf("master: ERROR: couldn't attach to memory\n");
    //     return (-1);
    // }

    //fork and execs slaves
    char str_buffer[8];
    char* slave_argv[3];
    slave_argv[0] = "slave";
    slave_argv[1] = str_buffer;
    slave_argv[2] = NULL;
    int i;
    for(i = 0; i < num_process; i++) {
        sprintf(str_buffer, "%d", i);
        slave_argv[1] = str_buffer;

        int status = fork();
        if(status == 0) {
            if(execve("slave", slave_argv, NULL) == -1) {
                printf("master: ERROR: exec failed.\n");
            }

            printf("exec succeeded.\n"); 
        }
        else if(status == -1) {
            printf("master: ERROR: fork failed.\n");
            exit(-1);
        }
        else {
            printf("Here in parent\n");
            wait(NULL);
        }
    }

    //deallocate shared memory
    detach_choosing_memory(choosing);
    detach_number_memory(number);

    destroy_choosing_memory(FILENAME);
    destroy_number_memory(FILENAME);

    return 0;
}