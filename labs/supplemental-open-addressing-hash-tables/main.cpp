#include <iostream>

#include "HashTableDictionary.hpp"
#include "SmallIntMixedOperations.hpp"
#include<iostream>
#include<fstream>
#include<random>

enum Actions {
    INSERT,
    DELETE,
    MEMBER
};


Actions generateAction() {
    static const int ACTION_RANGE = 10;

    enum ActionProbability {
        INSERT_PROB = 0,    // Probability of insert is 40% -- 4 (0, 1, 2, and 3) out of [0, 10).
        DELETE_PROB = 4,    // Probability of delete is 10% -- 1 (4) out of [0, 10).
        MEMBER_PROB = 5     // Probability of member is 50% -- 5 (5, 6, 7, 8, and 9) out of [0, 10).
    };

    int action = rand() % ACTION_RANGE;
    if( action < DELETE_PROB )
        return INSERT;
    else if( action < MEMBER_PROB)
        return DELETE;
    else
        return MEMBER;
}

void testHashtable(HashTableDictionary &hashTable, int numTestsToRun) {

    const int rangeOfValuesToBeGeneratedForTests = 10000;

    const int randomGenSeed = 49;
    srand(randomGenSeed);

    SmallIntMixedOperations smallIntInvertedList(rangeOfValuesToBeGeneratedForTests);

    int numTestFinished = 0;

    while ( numTestFinished < numTestsToRun ) {
        Actions action = generateAction();
        if (action == INSERT) {
            int valueToInsert = rand() % rangeOfValuesToBeGeneratedForTests;
            std::cout << "Action is INSERT -- value to insert is: " << valueToInsert << std::endl;
            if(hashTable.member(valueToInsert)) {
                std::cout << "However, " << valueToInsert << " is already a member. Will skip it.\n";
                continue;
            }
            hashTable.insert(valueToInsert);
            smallIntInvertedList.insert(valueToInsert);
        } else if (action == DELETE ) {
            if (hashTable.empty())
                std::cout << "Action is DELETE: Will ignore delete as the queue is empty.\n";
            else {
                if(smallIntInvertedList.empty()) {
                    std::cout << "Hashtable has elements that are not in the inverted list. This is a bug.\n";
                    exit(1);
                }
                int valueToDelete = smallIntInvertedList.aRandomValue();
                std::cout << "Action is DELETE: value to be deleted is: " << valueToDelete << std::endl;
                hashTable.remove(valueToDelete);
                smallIntInvertedList.remove(valueToDelete);
            }
        } else {  // must be member
            if (hashTable.empty()) {
                if (!smallIntInvertedList.empty()) {
                    std::cout << "Hashtable is empty but the inverted list is not. This is a bug.\n";
                    std::cout << "Inverted list has " << smallIntInvertedList.numElements() << std::endl;
                    std::cout << "The elements are:\n";
                    smallIntInvertedList.print();
                    exit(1);
                }
                std::cout << "Action is MEMBER: Will ignore member as the hashtable is empty.\n";
            } else {
                int valueToFind = smallIntInvertedList.aRandomValue();
                std::cout << "Action is MEMBER: The value to test member is: " << valueToFind;
                if( hashTable.member(valueToFind))
                    std::cout << " and it was found.\n";
                else {
                    std::cout << " and it is not in the table. This is a bug. Terminating...\n";
                    exit(1);
                }
            }
        }
        numTestFinished++;
    }

    if( hashTable.empty()) {
        std::cout << "The queue is empty after having run the tests.\n";
    } else {
       std::cout << "Testing is finished. The table has " << hashTable.size() << std::endl;
       std::cout << "The inverted list has " << smallIntInvertedList.numElements() << std::endl;
    }
}

int main(int argc, char *argv[]) {

    // When readFromInput is false, it runs unit test using an Oracle.
    // First leave it "false" and run it to see the types of stats that it collects
    // and prints. Then, set it to "true" to perform the tasks that you have been asked
    // to do for the lab.
    const bool readFromInput = true;


  if( readFromInput ) {
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " nameOfInputFile\n";
        exit(1);
    }

    std::fstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( !inputStream.is_open() ) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...\n";
        exit(2);
    }


    HashTableDictionary hashDictionary(31, 37, HashTableDictionary::DOUBLE);
      // HashTableDictionary hashDictionary(31, 37, HashTableDictionary::DOUBLE);

    int v;
    while( inputStream >> v)
        hashDictionary.insert(v);

     hashDictionary.printCounts();
    hashDictionary.printMask();
      hashDictionary.printStats();
  } else {

      int smallTwin =  3167, largeTwin = 3169;
      HashTableDictionary hashTable(smallTwin, largeTwin, HashTableDictionary::SINGLE);
      const int numberOfTestToRun = 10000;
      std::cout << "Will run " << numberOfTestToRun << std::endl;
      testHashtable(hashTable, numberOfTestToRun);
      std::cout << "Testing completed.\n";

//      hashTable.printStats();
      hashTable.printMask();
  }

    return 0;
}
