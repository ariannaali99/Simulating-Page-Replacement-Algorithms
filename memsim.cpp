/* -------------------------------------------------------------------------- */
/*                AUTHORS: Arianna Ali & Jhun-Thomas Calahatian               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                Necessary Headers                           */
/* -------------------------------------------------------------------------- */
#include <iostream>
#include "utility.hpp"
#include "dataStructures.hpp"
#include "policies.hpp"
 

/* -------------------------------------------------------------------------- */
/*                                    Main                                    */
/* -------------------------------------------------------------------------- */
int main(int argc, char *argv[]) {

    //Declare and Initialize Variables with Memory Allocation
    char *traceFile;
    int nFrames;
    char *policy;
    int p;
    char *debug_quiet;

    PageReplacement pageReplacementAlgo;

    extractcmdline(argc, argv, traceFile, nFrames, policy, p, debug_quiet);
    int events = countEventsInTrace(traceFile);

    //CLI Output Formatting
    std::cout << std::endl;

    /* ---------------------------------- Debug --------------------------------- */
    if(strcmp(debug_quiet, "debug") == 0) {
        cout << "== Information == " << std::endl;
        debugPrint(traceFile, nFrames, policy, p, debug_quiet, events);

    } else {

        cout << "== Information == " << std::endl;
        standardPrint(nFrames, events);

    }

    /* -------------------------------- Algorithm ------------------------------- */
    if(strcmp(policy, "fifo") == 0) {

        pageReplacementAlgo.fifo(traceFile, events, nFrames, debug_quiet);

    }
    else if(strcmp(policy, "lru") == 0) {

        pageReplacementAlgo.lru(traceFile, events, nFrames, debug_quiet);

    }
    else if(strcmp(policy, "vms") == 0) {

        if(p == 100) {

            std::cout << "NOTE: 100 percent of the total program memory is in secondary buffer, calling LRU." << std::endl;
            pageReplacementAlgo.lru(traceFile, events, nFrames, debug_quiet);

        }
        else {

            pageReplacementAlgo.vms(traceFile, events, nFrames, (float) p / 100, debug_quiet);

        }

    }

    //CLI Output Formatting
    std::cout << std::endl;

    //Exit Program sucessfully
    return 0;

} //End main