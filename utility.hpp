/* -------------------------------------------------------------------------- */
/*                AUTHORS: Arianna Ali & Jhun-Thomas Calahatian               */
/* -------------------------------------------------------------------------- */

#ifndef UTILITY_H
#define UTILITY_H

/* -------------------------------------------------------------------------- */
/*                                Necessary Headers                           */
/* -------------------------------------------------------------------------- */

#include <stdio.h>  //printf, scanf, NULL
#include <stdlib.h> //malloc, free
#include <unistd.h>

/* -------------------------------------------------------------------------- */
/*                        General or Utility Functions                        */
/* -------------------------------------------------------------------------- */

void extractcmdline(int argc, char *argv[], char *&traceFile, int &nFrames, char *&policy, int &p, char *&debug_quiet){
    //Base case: No arguments provided from the command line (e.g., ./memsim)
    if(argc < 5) {

        //Print error and exit with abnormal status
        if(argc < 2) {

            fprintf(stderr, "\nNo arguments provided.\n\n");
        
        } //End nested if
        else {

            fprintf(stderr, "\nNot enough arguments provided.\n\n");

        } //End else

        exit(1);

    } //End if
    else if(argc > 6) {

        fprintf(stderr, "\nToo many arguments provided.\n\n");
        exit(1);

    }


    //Declare and Initialize Variables with Memory Allocation
    int traceFileArgSize = strlen(argv[1]);
    traceFile = (char*) malloc(traceFileArgSize);

    nFrames = 0;

    int policyArgSize = strlen(argv[3]);
    policy = (char*) malloc(policyArgSize);

    p = 0;

    int debug_quiet_ArgSize;

    
    //Extract cmd line arguments into variables
    strcpy(traceFile, argv[1]);

    nFrames = strtol(argv[2], NULL, 10);

    strcpy(policy, argv[3]);

    if(argc == 5) {

        //Memory Allocate for the last argument and extract cmd line argument into variable
        debug_quiet_ArgSize = strlen(argv[4]);
        debug_quiet = (char*) malloc(debug_quiet_ArgSize);
        strcpy(debug_quiet, argv[4]);

    } //End if
    else {
        //percentage of the total program memory to be used in the secondary buffer
        p = strtol(argv[4], NULL, 10);

        //If p is not in range between 1 and 100
        if(p < 1 || p > 100) {

            fprintf(stderr, "Invalid argument for p, please let p be a number in the range 1-100.\n\n");
            exit(1);

        } //End nested if

        //Memory Allocate for the last argument and extract cmd line argument into variable
        debug_quiet_ArgSize = strlen(argv[5]);
        debug_quiet = (char*) malloc(debug_quiet_ArgSize);
        strcpy(debug_quiet, argv[5]);

    } //End Else

} //end func

int countEventsInTrace(char *traceFile) {

    char *fileName = traceFile;
    FILE *filePointer;
    int eventsInTrace = 0;
    char currentChar;

    //filePointer = fopen(traceFile, "r");
    filePointer = fopen(fileName, "r");

    if (filePointer == NULL) {

        fprintf(stderr, "\nCould not open trace file.\n\n");
        exit(1);
        return -1;

    }
    
    for(currentChar = getc(filePointer); currentChar != EOF; currentChar = getc(filePointer)) {
        
        if(currentChar == '\n') {
            
            ++eventsInTrace;
            
        } //End if
        
    } //End for

    //Close the file
    fclose(filePointer);

    return eventsInTrace;

} //End countEventsInTrace

void debugPrint(char *traceFile, int nFrames, char *policy, int p, char *debug_quiet, int events) {

    /* ------------------------ DEBUGGING: Print Contents ----------------------- */
    printf("Trace File: %s\n", traceFile);
    printf("Total Memory Frames: %d\n", nFrames);
    printf("Events in Trace: %d\n", events);
    printf("Policy: %s\n", policy);
    printf("Percentage: %d\n", p);
    printf("Debug/Quiet: %s\n", debug_quiet);
    /* ---------------------- END DEBUGGING: Print Contents --------------------- */

}
void standardPrint(int nFrames, int events) {

    /* ------------- Print Number of Traces and Total Memory Frames ------------- */
    printf("Total Memory Frames: %d\n", nFrames);
    printf("Events in Trace: %d\n", events);

}

#endif