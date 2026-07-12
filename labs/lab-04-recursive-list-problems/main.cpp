#include<iostream>
#include"reclists.hpp"
#include"solutions.hpp"

// Get a list from the user for a specific purpose,
// and output that list
list get_list(std::string purpose) {
    std::cout << "Enter a list for " << purpose << ": ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    return p;
}

void testNumNodesAtTheTopLevel() {
    // Test this numNodesAtTheTopLevel 3 times.

    auto p = get_list("testing numNodesAtTheTopLevel");
    std::cout << "The number of nodes at the top-level is " << numNodesAtTheTopLevel(p) << std::endl;

    p = get_list("testing numNodesAtTheTopLevel");
    std::cout << "The number of nodes at the top-level is " << numNodesAtTheTopLevel(p) << std::endl;

    p = get_list("testing numNodesAtTheTopLevel");
    std::cout << "The number of nodes at the top-level is " << numNodesAtTheTopLevel(p) << std::endl;
}

void testNumAtomsAtTheTopLevel() {
    // Test this numAtomsAtTheTopLevel 3 times.

    auto p = get_list("testing numAtomsAtTheTopLevel");
    std::cout << "The number of atoms at the top-level is " << numAtomsAtTheTopLevel(p) << std::endl;

    p = get_list("testing numAtomsAtTheTopLevel");
    std::cout << "The number of atoms at the top-level is " << numAtomsAtTheTopLevel(p) << std::endl;

    p = get_list("testing numAtomsAtTheTopLevel");
    std::cout << "The number of atoms at the top-level is " << numAtomsAtTheTopLevel(p) << std::endl;
}

void testFind() {
    auto p = get_list("testing find");
    auto q = get_list("testing find");
    if (find(p, q))
    std::cout << "found\n";
    else
    std::cout << "not found\n";
}

void testareEqual() {
    auto p = get_list("testing areEqual");
    auto q = get_list("testing areEqual");
    if (areEqual(p, q))
        std::cout << "equal\n";
    else
        std::cout << "not equal\n";
}

void testevenNumberOfAtoms() {
    auto p = get_list("testing evenNumberOfAtoms");
    if (evenNumberOfAtoms(p)) {
        std::cout << "evenNumberOfAtoms\n";
    }
    else {
        std::cout << "not evenNumberOfAtoms\n";
    }
}

void testeveryOtherAtom() {
    auto p = get_list("testing everyOtherAtom");
    auto q = get_list("testing everyOtherAtom");
    if (everyOtherAtom(p, q)) {
        std::cout << "everyOtherAtom\n";
    }else {
        std::cout << "not everyOtherAtom\n";
    }
}

void testcountAllAtoms() {
    auto p = get_list("testing countAllAtoms");
    std::cout << "Number of atoms is " << countAllAtoms(p) << std::endl;
}

void testcountListLength() {
    auto p = get_list("testing findMaxAtoms");
    std::cout << "The list length is " << countListLength(p) << std::endl;
}

int main()
{
    // testNumNodesAtTheTopLevel();
    // testNumAtomsAtTheTopLevel();
    // testFind();
    // testareEqual();
    // testevenNumberOfAtoms();
    // testeveryOtherAtom();
    //testcountAllAtoms();
    testcountListLength();
    return 0;
}
