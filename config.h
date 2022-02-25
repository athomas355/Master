#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#define NUM_OF_PROCESSES 20
#define FILENAME "master.c"
#define BLOCK_SIZE 20

int largest(int arr[], int n);
void process_i(const int i);
bool * attach_choosing_memory(char *filename, int size);
bool detach_choosing_memory(bool *memory);
bool destroy_choosing_memory(char *filename);
int * attach_number_memory(char *filename, int size);
bool detach_number_memory(int *memory);
bool destroy_number_memory(char *filename);

bool *choosing;
int *number;

#endif