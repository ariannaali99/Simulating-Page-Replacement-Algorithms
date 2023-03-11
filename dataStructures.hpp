/* -------------------------------------------------------------------------- */
/*                AUTHORS: Arianna Ali & Jhun-Thomas Calahatian               */
/* -------------------------------------------------------------------------- */

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H


/* -------------------------------------------------------------------------- */
/*                                Necessary Headers                           */
/* -------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

/* -------------------------------------------------------------------------- */
/*                                  Constants                                 */
/* -------------------------------------------------------------------------- */
#define PAGE_SIZE 4096

/* -------------------------------------------------------------------------- */
/*                                   Classes                                  */
/* -------------------------------------------------------------------------- */

//Class for table entry
class PageEntry {

    /* ---------------------------- Member Variables ---------------------------- */
protected:

    unsigned int pageNo; 
    unsigned int offset;
    
    char protection; //Protection bit should indicate whether the page should be read from or written to   
    int dirty; //page is dirty if address with W is inserted 

    /* ---------------------------- Member Functions ---------------------------- */
public:
    /* ------------------------------ Constructors ------------------------------ */

    PageEntry() {

        this->pageNo = -1;
        this->offset = -1;
        this->protection = ' ';
        this->dirty = -1;

    }

    PageEntry(unsigned int pageNo, unsigned int offset, char protection, int dirty) {
        this->pageNo = pageNo;
        this->offset = offset;
        this->protection = protection;
        this->dirty = dirty;
    }
    /* --------------------------------- Setters -------------------------------- */
    void setPageNo(unsigned int pageNo) {
        this->pageNo = pageNo;
    }
    void setOffset(unsigned int offset) {
        this->offset = offset;
    }
    void setProtection(char protection) {
        this->protection = protection;
    }
    void setDirty(int dirty){
        this->dirty = dirty;
    }


    /* --------------------------------- Getters -------------------------------- */
    const unsigned int getPageNo() const {
        return pageNo;
    }
    const unsigned int getOffset() const {
        return offset;
    }
    const char getProtection() const {
        return protection;
    }
    const char getDirty() const {
        return dirty;
    }

    /* ------------------------ Utility Member Functions ------------------------ */
    bool operator==(const PageEntry & page) const {
        if (pageNo == page.pageNo) {

            return true;

        }
        else {

            return false;

        }
  }

};

class PageEntryHash {

public:

    //Virtual Page Number is returned as a hash function
    size_t operator()(const PageEntry& entry) const {

        return entry.getPageNo();

    }

};

#endif