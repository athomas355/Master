#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include "config.h"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {

    FILE * cstest_file;
    cstest_file = fopen("cstest", "a");

    char data_to_append[BUFFER_SIZE] = "HH:MM:SS Queue nn File modified by process number xx\n";
    
    //HH:MM:SS Queue nn File modified by process number xx
    //fprintf(cstest_file, "HH:MM:SS Queue nn File modified by process number xx");
    
    fputs(data_to_append, cstest_file);

    fclose(cstest_file);

    return 0;
}