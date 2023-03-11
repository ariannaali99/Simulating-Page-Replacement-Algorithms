/* -------------------------------------------------------------------------- */
/*                AUTHORS: Arianna Ali & Jhun-Thomas Calahatian               */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/*                                Necessary Headers                           */
/* -------------------------------------------------------------------------- */
#include "policies.hpp"

/* -------------------------------------------------------------------------- */
/*                  Member Function Algorithm Implementations                 */
/* -------------------------------------------------------------------------- */

void PageReplacement::fifo(char* traceFile, int events, int frames, char *debug)
{
    clearPageTable();
    populatePageTable(traceFile);
    int read = 0;
    int write = 0;
    int hit = 0;
    int condition = 0;
    int i;
    int j;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    //Iterating through the page table
    for(i = 0; i < events; i++) {
        if(i == 0) {
            mainMemory.push_back(pageTable.at(i));
            read += 1;
        }
        else {
            if(mainMemory.size() >= frames) {
                //check to see if new entry is a hit
                for(j = 0; j < mainMemory.size(); j++) {
                    if(mainMemory.at(j) == pageTable.at(i)) {
                        hit += 1;
                        condition = 1;
                        int dirty = pageTable.at(i).getDirty();
                        if(dirty == 1) {
                            mainMemory.at(j).setDirty(1);
                        }
                        break;
                    }
                }//end for loop
                //if it is not a hit, condition will be equal to 0
                if(condition == 0) {
                    int dirty = mainMemory.at(0).getDirty();
                    if(dirty == 1) {
                        write += 1;
                    }
                    //since the value is not a hit, and thus not in memory
                    //we now have to read from memory and load into the frame
                    read += 1;
                    mainMemory.pop_front();
                    mainMemory.push_back(pageTable.at(i));
                    //mainMemory.push_front(pageTable.at(i));
                }
                condition = 0;
            }
            else {
                //Check if the address is already in memory
                for(j = 0; j < mainMemory.size(); j++) {
                    if(mainMemory.at(j) == pageTable.at(i)) {
                        hit += 1;
                        condition = 1;
                        int dirty = pageTable.at(i).getDirty();
                        if(dirty == 1) {
                            mainMemory.at(j).setDirty(1);
                        }
                        break;
                    }
                }//end for loop
                //if it is not a hit, we simply read from memory and add to queue
                if(condition == 0) {
                    //since the value is not a hit, and thus not in memory
                    //we now have to read from memory and load into the frame
                    read += 1;
                    mainMemory.push_back(pageTable.at(i));
                }
                condition = 0;
            }
        }//end else 
    }//end for loop
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "=== FIFO ===" << endl;
    cout << "Total Disk Reads: " << read << endl;
    cout << "Total Disk Writes: " << write << endl;
    if(strcmp(debug, "debug") == 0){
        cout << "Number of Hits: " << hit << endl;
    }
    std::cout << "Time Elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

}

/* ------------------------ Utility Member Functions ------------------------ */
void PageReplacement::clearPageTable() {

    this->pageTable.clear();

}

void PageReplacement::populatePageTable(char *traceFile) {

    char *fileName = traceFile;
    FILE *filePointer;

    filePointer = fopen(fileName, "r");

    if (filePointer == NULL) {

        fprintf(stderr, "\nCould not open trace file.\n\n");
        exit(1);

    }

    unsigned address;
    char rw;

    //While it is not the end of the file
    while(!feof(filePointer)) {
        
        //Extract
        fscanf(filePointer, "%x %c", &address, &rw);

        //Create entry with the virtual page number, offset, the protection bit by char, and the dirty bit
        PageEntry newEntry = PageEntry(address / PAGE_SIZE, address % PAGE_SIZE, rw, (rw == 'W'));

        //Add it to the page table
        this->pageTable.push_back(newEntry);

    }

   cout << endl;

    //Close the file
    fclose(filePointer);

} //End populatePageTable

/* ----------------------------------- LRU ---------------------------------- */

void PageReplacement::lru(char *traceFile, int events, int nFrames, char *debug) {

    clearPageTable();
    populatePageTable(traceFile);

    //For when it is written as page fault
    int hit = 0;
    int pageFaultRead = 0;
    int write = 0;

    //Set capacity to the page table size
    deque<PageEntry> cacheQueue;

    deque<PageEntry>::iterator cacheIterator;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    //Algorithm Start

    for(auto i : pageTable) {

        //Find page entry i in the cacheQueue
        cacheIterator = find(cacheQueue.begin(), cacheQueue.end(), i);

        //If it is NOT in the cacheQueue
        if(cacheIterator == cacheQueue.end()) {

            //It is a page fault and thus must read from memory
            ++pageFaultRead;

            //If the cacheQueue is full
            if(cacheQueue.size() == nFrames) {

                if(cacheQueue.begin()->getDirty() == 1) {

                    ++write;

                }

                //Remove the LRU entry and push it new entry to the queue
                cacheQueue.erase(cacheQueue.begin());
                cacheQueue.push_back(i);

            } //End if case for when cacheQueue is full

            //Otherwise it is NOT full
            else {
                
                //Push the new entry into the back of the queue
                cacheQueue.push_back(i);

            } //End else case when cacheQueue is NOT full
            
        } //End if case if entry i is NOT in the cache queue

        //Otherwise it IS in the cacheQueue
        else {
            hit += 1;
            
            //if cache iter is dirty then we change i dirty 
            if(cacheIterator->getDirty() == 1) {

                i.setDirty(1);

            }

            //Erase from cache and push it back to the queue
            cacheQueue.erase(cacheIterator);
            cacheQueue.push_back(i);
            

        } //End else case if entry i IS in the cacheQueue

    } //End for to iterate through the queue
    
    //Algorithm End

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    

    cout << "=== LRU ===" << endl;
    cout << "Total Disk Reads: " << pageFaultRead << endl;
    cout << "Total Disk Writes: " << write << endl;
    if(strcmp(debug, "debug") == 0) {
        cout << "Total Hits: " << hit << endl;
    }
    std::cout << "Time elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

} //End LRU

/* -------------------------- VMS / Segmented FIFO -------------------------- */
void PageReplacement::vms(char *traceFile, int events, int nFrames, float p, char *debug) {

    clearPageTable();
    populatePageTable(traceFile);
    int hit = 0;

    //Cache / Buffers
    deque<PageEntry> cacheQueue1;
    deque<PageEntry> cacheQueue2;

    //Cache / Buffer Iterators
    deque<PageEntry>::iterator cacheIterator;

    //Cache / Buffer Sizes
    int cacheSize1 = round(nFrames * (1 - p));
    int cacheSize2 = round(nFrames * p);

    /* ---------------------------------- Debug --------------------------------- */
    if(strcmp(debug, "debug") == 0) {

        std::cout << "VMS Extra Information:" << std::endl;
        std::cout << "> Percentage (Decimal): " << p << std::endl;
        std::cout << "> Primary Buffer Size: " << cacheSize1 << std::endl;
        std::cout << "> Secondary Buffer Size: " << cacheSize2 << std::endl;
        std::cout << std::endl;

    } //End if

    //Read Write Counters
    int pageFaultRead = 0;
    int write = 0; 

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    /* --------------------------- VMS ALGORITHM START -------------------------- */

    //Iterate through page table
    for(auto i : pageTable) {
        
        // The primary buffer is NOT filled
        if (cacheQueue1.size() < cacheSize1)
        {
            if(cacheQueue1.size() == 0) {
                ++pageFaultRead;
                cacheQueue1.push_back(i);
            }

            //Find page entry i within the primary buffer
            cacheIterator = find(cacheQueue1.begin(), cacheQueue1.end(), i);

            //If page entry i is NOT within the primary buffer
            if(cacheIterator == cacheQueue1.end()) {
                
                //Page fault, read from memory
                ++pageFaultRead;

                //Push page entry i to the back of the queue
                cacheQueue1.push_back(i);
                
            } //End if case if entry i is NOT within the primary buffer
            
            //If page entry IS in the primary buffer
            else {
                hit += 1;
                //Do nothing but check for dirty bit
                if(i.getDirty() == 1) {
                    cacheIterator->setDirty(1);
                }
            }

        } // End if case when primary buffer is NOT filled

        // Otherwise, the primary buffer IS filled
        else {

            //Find page entry i within the primary buffer
            cacheIterator = find(cacheQueue1.begin(), cacheQueue1.end(), i);

            //If page entry i is NOT within the primary buffer
            if(cacheIterator == cacheQueue1.end()) {
                
                //Search the secondary buffer for page entry i
                cacheIterator = find(cacheQueue2.begin(), cacheQueue2.end(), i);
            
                //When the secondary buffer is NOT full
                if(cacheQueue2.size() < cacheSize2) {
                    //check to see if page entry i is in here

                    //If page entry i is NOT within the secondary cache buffer (nor primary buffer)
                    if(cacheIterator == cacheQueue2.end()) {

                        //Push the information of the front of the primary buffer into the back of the secondary buffer
                        cacheQueue2.push_back(cacheQueue1.front());

                        //Pop the front of the primary buffer since the page has been moved to secondary buffer
                        cacheQueue1.pop_front();

                        //Push page entry i into the primary buffer
                        cacheQueue1.push_back(i);

                        //Since it is not a HIT, we have a page read
                        ++pageFaultRead;

                    } //End if case for when entry i is NOT within the secondary nor primary buffer

                    //Otherwise entry i IS in the secondary cache buffer
                    else {
                        hit += 1;
                        //Then, we store the top of the FIFO queue in temp 
                        PageEntry temp = cacheQueue1.front();
                        
                        //Then we must pop the top of the FIFO queue
                        cacheQueue1.erase(cacheQueue1.begin());
                        
                        //check to see if existing page entry in cache was dirty 
                        if(cacheIterator->getDirty() == 1) {
                            i.setDirty(1);
                        }
                        cacheQueue1.push_back(i);
 
                        //Delete that entry, where LRU entry matches with i is located
                        cacheQueue2.erase(cacheIterator);

                        //Push temp which was the front of the FIFO to the LRU
                        cacheQueue2.push_back(temp);

                    } //End else case for when entry i IS in the secondary cache buffer
                    
                } //End case if second cache buffer is NOT full
                
                //If second cache buffer is full 
                else {

                    //If page entry i is NOT within the secondary cache buffer (nor primary buffer)
                    if(cacheIterator == cacheQueue2.end()) {

                        //First we must pop the front of the LRU and check to see if any writes occurred
                        if(cacheQueue2.front().getDirty() == 1) {
                            ++write;
                        }
                        cacheQueue2.pop_front();

                        //Push the information of the front of the primary buffer into the back of the secondary buffer
                        cacheQueue2.push_back(cacheQueue1.front());

                        //Pop the front of the primary buffer since the page has been moved to secondary buffer
                        cacheQueue1.pop_front();

                        //Push page entry i into the primary buffer
                        cacheQueue1.push_back(i);

                        //Since it is not a HIT, we have a page read
                        ++pageFaultRead;

                    } //End if case for when entry i is NOT within the secondary nor primary buffer

                    //Otherwise entry i IS in the secondary cache buffer
                    else {
                        hit += 1;
                        //Then, we store the top of the FIFO queue in temp 
                        PageEntry temp = cacheQueue1.front();
                        
                        //Then we must pop the top of the FIFO queue
                        cacheQueue1.erase(cacheQueue1.begin());
                        
                        //check to see if existing page entry in cache was dirty 
                        if(cacheIterator->getDirty() == 1) {
                            i.setDirty(1);
                        }
                        cacheQueue1.push_back(i);
 
                        //Delete that entry, where LRU entry matches with i is located
                        cacheQueue2.erase(cacheIterator);

                        //Push temp which was the front of the FIFO to the LRU
                        cacheQueue2.push_back(temp);

                    } //End else case for when entry i IS in the secondary cache buffer
                    
                } //End else case when secondary buffer is full

            } //End if case when page entry i is NOT in the primary buffer
            
            //It is in the Primary Buffer
            else {

                hit += 1;

                //Checking to see if new page is dirty
                if(i.getDirty() == 1) {

                    cacheIterator->setDirty(1);

                }

            }

        } //End else case when primary buffer IS filled

    } //End for loop iterating through page table


    /* ---------------------------- VMS ALGORITHM END --------------------------- */
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();   

    cout << "=== VMS ===" << endl;
    cout << "Total Disk Reads: " << pageFaultRead << endl;
    cout << "Total Disk Writes: " << write << endl;
    if(strcmp(debug, "debug") == 0) {
        cout << "Total Hits: " << hit << endl;
    }
    std::cout << "Time Elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

} //End VMS