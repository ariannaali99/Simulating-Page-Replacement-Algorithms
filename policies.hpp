/* -------------------------------------------------------------------------- */
/*                AUTHORS: Arianna Ali & Jhun-Thomas Calahatian               */
/* -------------------------------------------------------------------------- */

#ifndef POLICIES_H
#define POLICIES_H

/* -------------------------------------------------------------------------- */
/*                                Necessary Headers                           */
/* -------------------------------------------------------------------------- */
#include "dataStructures.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <deque>
#include <chrono>
using namespace std;

/* -------------------------------------------------------------------------- */
/*                                   Classes                                  */
/* -------------------------------------------------------------------------- */

class PageReplacement
{

private:
    // Member variables
    std::deque<PageEntry> pageTable;
    
    //Main memory
    std::deque<PageEntry> mainMemory;
    int frames;
    int events;

public:
    /* ---------------------------- Policy Functions ---------------------------- */
    void fifo(char *traceFile, int events, int frames, char *debug);
    void lru(char *traceFile, int events, int nFrames, char *debug);
    void vms(char *traceFile, int events, int nFrames, float p, char *debug);

    /* ------------------------ Utility Member Functions ------------------------ */
    void clearPageTable();
    void populatePageTable(char *traceFile);
};

#endif