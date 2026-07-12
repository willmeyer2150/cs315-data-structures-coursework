//
// Created by Ali A. Kooshesh on 5/9/21.
//

#ifndef HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP
#define HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP

#include<vector>

class HashTableDictionary {
    // enum { LARGE_TWIN = 3169, SMALL_TWIN = 3167 };
    enum ELEMENT_STATUS {AVAILABLE, DELETED, USED};

public:
    enum PROBE_TYPE {SINGLE, DOUBLE};

    HashTableDictionary(int smallTwin, int largeTwin, PROBE_TYPE probeType);

    bool insert( int v );
    bool member( int v );
    void remove(int v);
    bool empty();
    int size();
    void printStats();
    void printCounts();
    void printMask();

private:
    int SMALL_TWIN, LARGE_TWIN;
    PROBE_TYPE probeType;

    std::vector<int> hashTable;
    std::vector<int> hashTableMask;
    std::vector<int> numProbes; // new vector to track number of probes for inserts

    int numElementsInTable = 0;

    int primaryHashFunction( int  n );
    int secondaryHashFunction( int  n );
    void printMask(ELEMENT_STATUS);


    int numLookups = 0;
    int totalNumberOfLookupIterations = 0;
    int maxValuesInTable = 0;
};


#endif //HASHTABLESOPENADDRESSING_HASHTABLEDICTIONARY_HPP
