//
// Created by Ali A. Kooshesh on 5/9/21.
//

#include "HashTableDictionary.hpp"
#include<iostream>
#include<iomanip>
#include<algorithm>

HashTableDictionary::HashTableDictionary(int small, int large, PROBE_TYPE type): SMALL_TWIN{small}, LARGE_TWIN{large}, probeType{type} {
    hashTable.resize(large);
    hashTableMask.resize(large, AVAILABLE);
    numProbes.resize(large, 0); // initialize vector
}

bool HashTableDictionary::insert( int v ) {
    // Returns whether the insert was successful.

    if( numElementsInTable == LARGE_TWIN) {
        std::cout << "Table is full. This is a serious problem. Terminating\n";
        exit(1);
    }

    if(member(v))
        return false;
    int probeCounts = 1;
    int idx = primaryHashFunction( v );
    int idx2 = secondaryHashFunction( v );
    while( hashTableMask.at(idx) == USED ) {
        idx = (idx + idx2) % LARGE_TWIN;
        probeCounts++;
    }

    numProbes[idx] = probeCounts;

    hashTable.at(idx) = v;
    hashTableMask.at(idx) = USED;
    numElementsInTable++;
    if( maxValuesInTable < numElementsInTable )
        maxValuesInTable = numElementsInTable;
    return true;
}

int HashTableDictionary::size() {
    return numElementsInTable;
}

void HashTableDictionary::remove(int v) {
    if( ! member(v) )
        return;

    int idx = primaryHashFunction( v );
    int idx2 = secondaryHashFunction( v );
    while( hashTableMask.at(idx) != AVAILABLE && hashTable.at(idx) != v ) {
        idx = (idx + idx2) % LARGE_TWIN;
    }

    hashTableMask.at(idx) = DELETED;
    numElementsInTable--;
}

bool HashTableDictionary::member( int v )  {
    // Returns true if v a member. Otherwise, it returns false

    numLookups++;

    int idx = primaryHashFunction( v );
    int idx2 = secondaryHashFunction( v );
    int numComparisons = 0;

    totalNumberOfLookupIterations++;
    while( numComparisons <= LARGE_TWIN && hashTableMask.at(idx) != AVAILABLE &&
            ( hashTableMask.at(idx) == DELETED || hashTable.at(idx) != v ) ) {
        idx = (idx + idx2) % LARGE_TWIN;
        numComparisons++;
        totalNumberOfLookupIterations++;
    }
    return  hashTable.at(idx) == v;
}

bool HashTableDictionary::empty() {
    return numElementsInTable == 0;
}

void HashTableDictionary::printStats() {
    if( numLookups == 0 ) {
        std::cout << "No lookups were performed.\n";
    } else {
        std::cout << "A total of " << numLookups << " lookups were performed.\n";
        std::cout << "Average number of operations per lookup is: " << double(totalNumberOfLookupIterations) / double(numLookups)
                  << std::endl;
    }
    std::cout << "Maximum number of values in the table during the operations was " << maxValuesInTable << std::endl;
    if(maxValuesInTable > 0 )
        std::cout << "The percentage of free elements was " <<
            double(LARGE_TWIN - maxValuesInTable) / double(LARGE_TWIN) * 100.0 << std::endl;
}


void inRed(char c) {
    std::cout << "\x1b[31m" << c << "\x1b[0m";
}

void inBlue(char c) {
    std::cout << "\x1b[34m" << c << "\x1b[0m";
}
void inYellow(char c) {
    std::cout << "\x1b[33m" << c << "\x1b[0m";
}

void inGreen(char c) {
    std::cout << "\x1b[32m" << c << "\x1b[0m";
}

void inMagenta(char c) {
    std::cout << "\x1b[35m" << c << "\x1b[0m";
}

void inCyan(char c) {
    std::cout << "\x1b[36m" << c << "\x1b[0m";
}

void HashTableDictionary::printMask(ELEMENT_STATUS es) {
    for(size_t i = 0; i < LARGE_TWIN; i++) {
        if(hashTableMask.at(i) == USED)
            inRed(es == USED ? '-' : ' ');
        else if (hashTableMask.at(i) == AVAILABLE)
            inYellow(es == AVAILABLE ? '-' : ' ');
        else if( hashTableMask.at(i) == DELETED)
            inGreen(es == DELETED ? '-' : ' ');
        else {
            std::cout << "\nUnrecognize element type with value: " << hashTableMask.at(i) << "." << std::endl;
            exit(1);
        }
        if(  (i + 1) % 100 == 0)
            std::cout << '.' << std::endl;
    }
    std::cout << std::endl;
}

void HashTableDictionary::printMask() {
    std::cout << "Elements in use map.\n";
    printMask(USED);
    std::cout << "\nElements deleted map.\n";
    printMask(DELETED);
    std::cout << "\nElements available map.\n";
    printMask(AVAILABLE);
}

void HashTableDictionary::printCounts() {
    std::cout << std::setw(2) << ' ';
    for(size_t i = 0; i < LARGE_TWIN; i++) {
        std::cout << std::setw(5) << i;
    }
    std::cout << std::endl << std::setw(2) << ' ';
    for(size_t i = 0; i < LARGE_TWIN; i++) {
        if(hashTableMask.at(i) == USED)
            std::cout << std::setw(5) << hashTable.at(i);
        else
            std::cout << std::setw(5) << "-";
    }

    std::cout << std::setw(5) << ' ' << std::endl;

    std::cout << std::endl;
    std::cout << "______________________________" << std::endl;
    std::cout << std::setw(2) << "|Index" << std::setw(2) << ' '
                                << "|Value" << std::setw(2) << ' '
                                << "|Num_Probes  |"
                                << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (size_t i = 0; i < LARGE_TWIN; i++) {
        if (hashTableMask.at(i) == USED) {
            std::cout << "|" << std::setw(4) << i << std::setw(4) << "|";
            std::cout << std::setw(4) << hashTable.at(i) << std::setw(4) << "|";
            std::cout << std::setw(6) << numProbes.at(i) << std::setw(7) << "|" << std::endl;
        }
        else {
            std::cout << "|" << std::setw(4) << i << std::setw(4) << "|";
            std::cout << std::setw(4) << "-" << std::setw(4) << "|";
            std::cout << std::setw(6) << "-" << std::setw(7) << "|" << std::endl;
        }
    }
    std::cout << "------------------------------" << std::endl;
    std::cout << std::endl;
}

int HashTableDictionary::primaryHashFunction( int  n ) {
    return n % LARGE_TWIN;
}

int HashTableDictionary::secondaryHashFunction( int  n ) {
    if(probeType == SINGLE)
        return 1;
    int idx = n % SMALL_TWIN;
    return idx == 0 ? 1 : idx;
}
