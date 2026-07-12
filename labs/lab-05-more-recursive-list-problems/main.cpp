#include <iostream>
#include "reclists.hpp"
#include "solutions.hpp"

list get_list(std::string purpose);
void test_append();
void test_numAtoms();
void test_maxDepth();
void test_everyOtherAtom();
void test_memberAtLevel();
void test_reverseTopLevel();

// Comment each function call and its definition below
//    back in to test it
// Go down to the implementation of each test function
//    and write down your 3 tests in its initial comment.
int main() {
    test_append();
    // test_numAtoms();
    //test_maxDepth();
    //test_everyOtherAtom();
    //test_memberAtLevel();
    //test_reverseTopLevel();
    return 0;
}

// Get a list from the user for a specific purpose,
// and output that list
list get_list(std::string purpose) {
    std::cout << "Enter a list for " << purpose << ": ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    return p;
}


void test_append() {
// Write your 3 test cases in this comment:
// 1. p = ( a ( b ) ( c d ) )
//    q = ( e ( fg ( h ) ) i j )
//    result should be: ( a ( b ) ( c d ) e ( fg ( h ) ) i j )
// 2. p =
//    q =
//    result should be:
// 3. p =
//    q =
//    result should be:


    list p = get_list("append (original list)");
    list q = get_list("append (add-on)");
    std::cout << "Appending q to p: ";
    write_list(append(p,q));

}

void test_numAtoms() {
// Write your 3 test cases in this comment:
// p = ((a (b (c) d (e)) c) (((e f) g) h) (i) (((j) k) l))
//    result should be: 14
// 2. p =
//    result should be:
// 3. p =
//    result should be:


    list p = get_list("number of atoms");
    std::cout << "Number of atoms in p: " << numAtoms(p) << std::endl;

}

void test_reverseTopLevel() {
// Write your 3 test cases in this comment:
// 1. p =
//    result should be:
// 2. p =
//    result should be:
// 3. p =
//    result should be:

/* Remove this comment when you're ready
    list p = get_list("reverse top level");
    write_list(reverseTopLevel(p));
*/
}

void test_maxDepth() {
// Write your 3 test cases in this comment:
// 1. p =
//    result should be:
// 2. p =
//    result should be:
// 3. p =
//    result should be:

/* Remove this comment when you're ready
    list p = get_list("max depth");
    std::cout << "Maximum depth of p: " << maxDepth(p) << std::endl;
*/
}

void test_everyOtherAtom() {
// Write your 3 test cases in this comment:
// 1. p =
//    result should be:
// 2. p =
//    result should be:
// 3. p =
//    result should be:

/* Remove this comment when you're ready
    list p = get_list("every other atom");
    write_list(everyOtherAtom(p));
*/
}

void test_memberAtLevel() {
// Write your 3 test cases in this comment:
// 1. p =
//    q =
//    n =
//    result should be:
// 2. p =
//    q =
//    n =
//    result should be:
// 3. p =
//    q =
//    n =
//    result should be:

/* Remove this comment when you're ready
    int level;
    std::string result;
    list p = get_list("memberAtLevel (original list)");
    list q = get_list("atom to check");
    std::cout << "Level to check: ";
    std::cin >> level;
    result = memberAtLevel(p, q, level) ? "Yes" : "No";
    std::cout << "Atom found at level " << level << "? " << result << std::endl;
*/
}