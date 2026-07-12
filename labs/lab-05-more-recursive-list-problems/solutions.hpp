#ifndef __MYSOLUTION_HPP
#define __MYSOLUTION_HPP

#include <iostream>
#include "reclists.hpp"

/* --- COPY INTO YOUR CPP FOR APPEND, STARTING HERE --- */
list append(list p, list q);
// Neither p nor q is an atom.

// Here is the definition of append:
// append((), q) is q
// append( (a restOfList), q ) is cons(a, append(restOfList, q))

// Therefore, append((a () (b) c), (e F)) is
//   (a () (b) c e F)
/* --- STOP HERE WHEN COPYING CODE FOR APPEND --- */

int numAtoms(list p);
// p is a recursive list. It is not an atom.
// This function counts and returns the number of atoms
// in p, regardless of how deeply they are nested.

list reverseTopLevel(list p);
// p is a list, but it is not an atom.
// reverseTopLevel (shallow reverse) reverses the order of the
// top-level elements of p, but it does not go into those
// lists to reverse them.

// Example
// p is ( a ((b c) e) (f) (g (h)) )
// reverseTopLevel(p) is ( (g (h)) (f) ((b c) e) a )

/* ---- THESE ARE THE LAST 3 PROBLEMS TO DO ---- */

int maxDepth(list p);
// Here is the definition of depth for recursive lists.
// Intuitively, the depth of a list is the maximum
// number of levels of the list.

// Here is a more formal definition:
//       when p is a null list, its depth is 0
//       when p is an atom, its depth is 1
//       otherwise, the depth of p is the larger of
//            the depth of its car plus one, and
//            the depth of its cdr.

// You should feel free to #include <algorithm> and use the
// "max" STL function, which will compute the max of any
// 2 arguments for which the "less-than" operation is defined
// Example: std::max(2, 3) returns 3.

list everyOtherAtom(list p);
// p is a list with an even number of atoms, like () or (a b c d).
// p will NOT be a nested list, an individual atom, or a list with
//   an odd number of elements.

// The first atom in p is at position 1. The second atom is at position 2, etc.

// This function creates and returns a list that consists
// of atoms whose positions in p are odd numbers.

// For example:
// p is (a b c d e f)
// The position of a is 1, of c is 3, and of e is 5. Therefore,
// everyOtherAtom should return (a c e)

bool memberAtLevel(list p, list q, int n);
// p is a recursive list, but is not an atom
// q is an atom
// n >= 1

// Does p have an atom at level n that is equal to q?
// The outermost level is level 1, and the level
// increments as lists nest within it.

// Example 1:
// p = ( a b c )
// q = b
// n = 1
// memberAtLevel(p, q, n) should return true because there is
// an atom in p that is equal to q and is at level 1. This
// function should return false if n is larger than 1.

// Example 2:
// p = ( a b c (c (d) e) (((f))) )
// q = f
// n = 4
// memberAtLevel(p, q, n) should return true as f is at level 4 in p.
// You should draw the internal representation of p to make sure you
// see why f is at level 4.

#endif
