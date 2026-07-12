#include <iostream>
#include <fstream>

#include "BinSearchTree.hpp"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main( int argc, char *argv[] ) {
    // Use this as a starting point to test the functions
    // that you add to BinSearchTree.


    if( argc != 2 ) {
        std::cout << "usage: executable name-of-input-file\n";
        exit(1);
    }
    std::fstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if(!inputStream.is_open()) {
        std::cout << "Unable to open the input file " <<
                  argv[1] << std::endl;
        std::cout << "Terminating...\n";
        exit(2);
    }


    BinSearchTree *tree = new BinSearchTree();
    int aValue;
    while( inputStream >> aValue )
        tree->insert( aValue );

    // The size() function has not been implemented yet. It currently returns 0
    // so the program can compile and run. Your first task is to write a proper
    // recursive implementation of find(). Once that is done, move on to writing
    // the recursive version of size().

    // testing size()
    std::cout << "The size of the tree is " << tree->size() << "." << std::endl;

    // testing find()
    if (tree->find(54))
        std::cout << "find says 54 is in the tree." << std::endl;
    else
        std::cout << "find says 54 is not in the tree." << std::endl;

    // testing iterFind()
    if (tree->iterFind(54))
        std::cout << "iterFind says 54 is in the tree." << std::endl;
    else
        std::cout << "iterFind 54 is not in the tree." << std::endl;

    // testing inorderListing()
    std::cout << "The in order listing of the tree is: " << std::endl;
    tree->inorderListing();

    // testing maxDepth()
    std::cout << "The maximum depth of the tree is: " << tree->maxDepth() <<  std::endl;

    // testing iterInsert
    tree->iterInsert(115);
    std::cout << "The new in order listing of the tree is: " << std::endl;
    tree->inorderListing();

    // testing destructor
    tree->~BinSearchTree();
    std::cout << "The current tree contains: " << std::endl;
    tree->inorderListing();

    std::cout << "The size of the tree is " << tree->size() << "." << std::endl;




    return 0;
}
