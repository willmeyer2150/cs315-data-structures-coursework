#ifndef __MYSOLUTION_HPP
#define __MYSOLUTION_HPP

#include<iostream>
#include"reclists.hpp"

int numNodesAtTheTopLevel(list p);
// The above is a sample problem whose solution appears in
// solutions.cpp. main.cpp demonstrates how to test this
// problem.
// input lists for testing numNodesAtTheTopLevel:
// (((a b) c) d (a b))
// (a b c d e)
// ()

// Write a solution for each of the following problems and test
// each using three input lists. Write the input lists that you
// use for testing teach function below its description, similar
// to the above example.


int numAtomsAtTheTopLevel(list p);
    // pre-condition: p is not an atom

// This function receives a recursive list that
// is either null or a list of lists and counts
// the number of atoms at its top level.

// Here is a sample input/output
// input: (((a b) c) d (a b))  output: 1
// input: (a b c d e) output: 5
// input: () output 0

bool find(list p, list q);
// p is a list that contains atoms q; is an atom
// does p have an atom whose value is the same as that of q?

// To compare atoms, you will have to use function eq defined below.
// It is a builtin function just as car and cdr.
// bool eq(list p, list q);
// eq returns true if (i) each of p and q is an atom and
// (ii) the two atoms contain the same sequence of characters.
// For example,
// suppose p contain atom cs315 and q also contains cs315,
// then eq(p, q) will return true. On the other hand,
// if p contains cs315 and q contains cs215, the
// eq(p, q) returns false. It also returns false if
// either of the two lists is not an atom.

bool areEqual(list p, list q);
// p is a list of atoms
// q is a list of atoms
// p & q have the same number of atoms
// the function returns true if the atoms
// in p are the same as those in q and in the same order

// p is (a b c d) q is (a b c d). the function returns true
// p is (a b c d) q is (b a c d). the function false


bool evenNumberOfAtoms(list p);
// p is a list of atoms. It might be empty -- a null list.
// This function returns true if p contains an even number of
// atoms. Otherwise, it returns false.
// For example, given the following list
// (a b c d e f g h i j)
// the function returns true as there are 10 atoms on this list.
// On the other hand given this list
// (a b c d e)
// the function should return false as the list contains 5 atoms.

// You SHOULD NOT write a helper function for this one.

bool everyOtherAtom(list p, list q);
// each of p and q is a list of atoms or an empty list.
// The question is whether the i-th atom of p appears
// in the 2*i-th position of q or not.
// Example 1:
// p is (a)
// q is (b a)
// everyOtherAtom(p, q) should return true because a, the only
// atom of p is at position 1 in p and at position 2 (2 * 1) in q.
// Example 2:
// (a b c)
// (a a c b a c e a)
// everyOtherAtom(p, q) should return true because a is at position
// 1 in p and position 2 (2 * 1) in q. b is in position 2 in p and
// in position 4 (2 * 2) in q. c is in position 3 in p and in position
// 6 in q.

int numAtomsInCommon(list p, list q);

int countAllAtoms(list p);

int countListLength(list p);

#endif
