#include "reclists.hpp"
#include "solutions.hpp"
//Team Names: Will Meyer, Caleb Clements

// As you implement functions in this file, you should add the
// function-prototype to the solutions.hpp. The function-prototypes
// for append and reverse are already in solutions.hpp.


// int numNodesAtTheTopLevel(list p) {
//     // p is one of
//     //    a null list
//     //    an atom
//     //    a recursive list
//
//     // The function returns the number of nodes at the top-level
//     // of p.
//
//     if( is_null(p) )
//         return 0;
//     if( is_atom(p) )
//         return 1;
//     return 1 + numNodesAtTheTopLevel(cdr(p));
// }
//
//
// int numAtomsAtTheTopLevel(list p) {
// // pre-condition: p is not an atom
//
// // This function receives a recursive list that
// // is either null or a list of lists and counts
// // the number of atoms at its top level.
// // Here is a sample input/output
// // input: (((a b) c) d (a b))  output: 1
// // input: (a b c d e) output: 5
// // input: () output 0
//
// // Notes to Gurman: Because these are small functions, I tend to
// // ask them not to define new variables. That is generally a good
// // programming practice when the repetition of code is a function calls.
// // The code becomes more expressive.
//
//     if (is_null(p))
//     {
//         return 0;
//     }
//     if (is_atom(car(p)))
//     {
//         return 1 + numAtomsAtTheTopLevel(cdr(p));
//     }
// return numAtomsAtTheTopLevel(cdr(p));
// }
//
// bool find(list p, list q) {
//     // p is a list that contains atoms; q is an atom
//     // Does p have an atom whose value is the same as that of q?
//     if (is_null(p))
//     {
//         return false;
//     }
//     if (eq(car(p), q))
//     {
//         return true;
//     }
//     return find(cdr(p), q);
// }
//
// bool areEqual(list p, list q) {
//     // p is a list of atoms
//     // q is a list of atoms
//     // p & q have the same number of atoms
//     // the function returns true if the atoms
//     // in p are the same as those in q and in the same order
//     // p is (a b c d) q is (a b c d). the function returns true
//     // p is (a b c d) q is (b a c d). the function false
//
//     if (is_null(p) && is_null(q))
//         return true;
//     if (!eq(car(p), q))
//     {
//         return true;
//     }
//         return areEqual(cdr(p), q);
// }
//
// bool evenNumberOfAtoms(list p) {
// // p is a list of atoms. It might be empty -- a null list.
// // This function returns true if p contains an even number of
// // atoms. Otherwise, it returns false.
// // For example, given the following list
// // (a b c d e f g h i j)
// // the function returns true as there are 10 atoms on this list.
// // On the other hand given this list
// // (a b c d e)
// // the function should return false as the list contains 5 atoms.
//
// // You SHOULD NOT write a helper function for this one.
//
// // Note to Gurman
// // This function is intended to make them more comfortable with the use of cdr.
// // At some point, I gave them the general version of this problem -- given
// // a recursive list that is not an atom, determine if atoms, when they appear,
// // their number is even. Having come up with the following solution to this
// // problem gives them a chance to solve the general version.
//
//     if (is_null(p))
//     {
//         return true;
//     }
//     if (!is_null(p) && is_null(cdr(p)))
//     {
//         return false;
//     }
//
//     return evenNumberOfAtoms(cdr(cdr(p)));
// }
//
// bool everyOtherAtom(list p, list q) {
//     // each of p and q is a list of atoms or an empty list.
//     // The question is whether the i-th atom of p appears
//     // in the 2*i-th position of q or not.
//     // Example 1:
//     // p is (a)
//     // q is (b a)
//     // everyOtherAtom(p, q) should return true because a, the only
//     // atom of p is at position 1 in p and at position 2 (2 * 1) in q.
//     // Example 2:
//     // (a b c)
//     // (a a c b a c e a)
//     // everyOtherAtom(p, q) should return true because a is at position
//     // 1 in p and position 2 (2 * 1) in q. b is in position 2 in p and
//     // in position 4 (2 * 2) in q. c is in position 3 in p and in position
//     // 6 in q.
//
//     if (is_null(p))
//     {
//         return true;
//     }
//     if (!is_null(p) && (is_null(q) || is_null(cdr(q))))
//     {
//         return false;
//     }
//     if (!eq(car(p), car(cdr(q))))
//     {
//         return false;
//     }
//     return everyOtherAtom(cdr(p), cdr(cdr(q)));
// }


int numNodesAtTheTopLevel(list p) {
    // p is one of
    //    a null list
    //    an atom
    //    a recursive list

    // The function returns the number of nodes at the top-level
    // of p.

    // p could be null, an atom or a recursive list
    // Let's return the number of nodes at top level of p

    // base case - when the list is empty

    if (is_null(p)) {
        return 0;
    }

    if (is_atom(p)) {
        return 1;
    }
    return ! + numNodesAtTheTopLevel(cdr (p));
}


int numAtomsAtTheTopLevel(list p) {
// pre-condition: p is not an atom

// This function receives a recursive list that
// is either null or a list of lists and counts
// the number of atoms at its top level.
// Here is a sample input/output
// input: (((a b) c) d (a b))  output: 1
// input: (a b c d e) output: 5
// input: () output 0

// Notes to Gurman: Because these are small functions, I tend to
// ask them not to define new variables. That is generally a good
// programming practice when the repetition of code is a function calls.
// The code becomes more expressive.

    // So we know p is not an atom, it is a list
    // We want to output the number of atoms at the top level only, not the nodes, the atoms. car(p)
    // Base Case : We have an empty list

    if (is_null(p)) {
        return 0;
    }
    // Next case: If car(p) is an atom, return 1 and add it to the next recursive call of cdr(p)
    if (is_atom(car(p))) {
        return 1 + numAtomsAtTheTopLevel(cdr(p));
    }
    return numAtomsAtTheTopLevel(cdr(p));

}

bool find(list p, list q) {
    // p is a list that contains atoms; q is an atom
    // Does p have an atom whose value is the same as that of q?

    // We are given two lists, and we want to know if list p has an atom whole value is the same as that of q (an atom)
    // Base case: If list p is empty, return false
    if (is_null(p)) {
        return false;
    }
    // Next case: If car(p) is equal to q, return true
    if (eq(car(p), q)) {
        return true;
    }
    return find(cdr(p), q);

}

bool areEqual(list p, list q) {
    // p is a list of atoms
    // q is a list of atoms
    // p & q have the same number of atoms
    // the function returns true if the atoms
    // in p are the same as those in q and in the same order
    // p is (a b c d) q is (a b c d). the function returns true
    // p is (a b c d) q is (b a c d). the function false

    // Base case, p is empty
    if (is_null(p))
        return false;
    if (eq(car(p), car(q))) {
        return true;
    }
    return areEqual (cdr(p), cdr(q));
}

bool evenNumberOfAtoms(list p) {
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
// Base case, if list p is empty, we will return false.
    if (is_null(p)) {
        return true;
    }
// Next Case: if list p has one item in it, cdr(p) is null, return false
    if (is_null(cdr(p))) {
        return false;
    }
    return evenNumberOfAtoms(cdr(cdr(p)));

// Note to Gurman
// This function is intended to make them more comfortable with the use of cdr.
// At some point, I gave them the general version of this problem -- given
// a recursive list that is not an atom, determine if atoms, when they appear,
// their number is even. Having come up with the following solution to this
// problem gives them a chance to solve the general version.


}

bool everyOtherAtom(list p, list q) {
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

    // Base case: if p is empty, success
    if (is_null(p))
        return true;

    // Base case: if q is too short (null or only one element left), fail
    if (is_null(q) || is_null(cdr(q)))
        return false;

    // Compare atom from p with 2*i-th atom from q
    if (!eq(car(p), car(cdr(q))))
        return false;

    // Recurse: next atom in p, skip 2 in q
    return everyOtherAtom(cdr(p), cdr(cdr(q)));

}

int numAtomsInCommon(list p, list q) {
    // p and q are two lists of atoms and the atoms in each list are distinct.
    // This function returns the number of atoms that p and q have in common.

    // Base case if list p is empty, return 0.
    if (is_null(p)) {
        return 0;
    }
    // Next case, if by finding q in car(p), return 1 + recursive call
    if (find(q, car(p))) {
        return 1 + numAtomsInCommon(cdr(p), q);
    }
    return numAtomsInCommon(cdr(p), q);

}

int countAllAtoms(list p) {
    if (is_null(p)) {
        return 0;
    }
    // If car(p) is an atom, count it (+1) and recurse on the rest of the list
    if (is_atom(car(p)))
    return 1 + countAllAtoms(cdr(p));
    else
        return countAllAtoms(car(p)) + countAllAtoms(cdr(p));
}

int countListLength(list p) {
    if (is_null(p)) {
        return 0;
    }
    return 1 + countListLength(cdr(p));

}