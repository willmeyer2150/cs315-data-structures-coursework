#include "reclists.hpp"
#include "solutions.hpp"

// All function documentation found in README.md

#include <filesystem>

// helper function to chain cout statements in main for testing
std::ostream& operator<<(std::ostream& os, list p)
{
    write_list(p);
    return os;
}

// As you implement functions in this file, you should add the
// function-prototype to the solutions.hpp.
//

list append(list p, list q)
{
    if (is_null(p))
    {
        return q;
    }
    return cons(car(p), append(cdr(p), q));
}


int numNodesAtTheTopLevel(list p)
{
    // p is one of
    //    a null list
    //    an atom
    //    a recursive list

    // The function returns the number of nodes at the top-level
    // of p.

    if( is_null(p) )
        return 0;
    if( is_atom(p) )
        return 1;
    return 1 + numNodesAtTheTopLevel(cdr(p));
}


bool is_lat(list p)
{
//     Takes a list (possibly empty) but not an atom and returns true if the list consists entirely of atoms. For example:
//
// is_lat((a b c)) = true
// is_lat((a (b) c)) = false
//
// Remember: No loops.

    if( is_null(p))
    {
        return false;
    }
    if ((!is_atom(car(p))))
    {
        return false;
    }
    else
    {
        return is_lat(cdr(p));
    }
}


bool member(list p, list q)
{
    // Takes an atom p and a list q (possibly empty but not an atom). Returns true if p appears anywhere in q. If the inputs do not meet these conditions, behavior is undefined.
    //
    // Base case: If q is empty, return false.
    if (is_null(q))
    {
        return false;
    }
    if (is_atom(car(q)))
    {
        if (eq(p, car(q)))
        {
            return true;
        }
        else
        {
            return member(p, cdr(q));
        }
    }
    if (member(p, car(q)))
    {
        return true;
    }
    else
    {
        return member(p,cdr(q));
    }
}


list last(list p)
{
    //
    // Takes a non-empty list (not an atom) and returns its last element. This must be done without using reverse. For example:
    //
    // last((a b c)) = c

    if (is_null(cdr(p)))
    {
        return car(p);
    }
    else
    {
        return last(cdr(p));
    }
}


list list_pair(list p, list q)
{
//     Takes two lists of atoms of the same length and returns a list of pairs, where each pair contains corresponding atoms from p and q. For example:
//
// list_pair((a b c), (d e f)) = ((a d) (b e) (c f))

    if (is_null(p) && is_null(q))
    {
        return null();
    }
    else
    {
        return cons(cons(car(p), cons(car(q), null())), list_pair(cdr(p), cdr(q)));
    }
}


list firsts(list p)
{
//     Takes as input a list whose elements are lists of atoms and returns a list of the first element from each sublist. For example:
//
// firsts(((a b c) (d e f) (c d b a))) = (a d c)

    if (is_null(p))
    {
        return null();
    }
    return cons(car(car(p)), firsts(cdr(p)));
}


list flat(list p) {
//     Takes a list (not an atom) and returns a list in which all nested parentheses are removed (except the outer set). For example:
//
// flat((a (b) (c d))) = (a b c d)
    if (is_null(p))
    {
        return null();
    }
    if (is_atom(car(p)))
    {
        return cons(car(p), flat(cdr(p)));
    }
    else
    {
        return append(flat(car(p)), flat(cdr(p)));
    }
}


bool two_the_same(list p, list q)
{
    // Takes two lists (not atoms) and returns true if p and q contain at least one atom in common.

    if (is_null(p))
    {
        return false;
    }
    if (is_atom(car(p)))
    {
        if (member(car(p), q))
        {
            return true;
        }
        else
        {
            return two_the_same(cdr(p), q);
        }
    }
    else
    {
        return two_the_same(car(p), q) || two_the_same(cdr(p), q);
    }
}


 bool equal(list p, list q)
{
    // Takes two recursive lists and determines if they are identical: parentheses must match in structure and all atoms must be identical in name and position. This is an extension of eq.
    if (is_null(p) && is_null(q))
    {
        return true;
    }
    if (is_null(p) || is_null(q))
    {
        return false;
    }
    if (is_atom(car(p)) && is_atom(car(q)))
    {
        if (!eq(car(p), car(q)))
        {
            return false;
        }
        return equal(cdr(p), cdr(q));
    }
    if (is_atom(car(p)) || is_atom(car(q)))
    {
        return false;
    }
    if (equal(car(p), car(q)))
    {
        return equal(cdr(p), cdr(q));
    }
    return false;
}


list total_reverse(list p)
{
    // Takes a recursive list and returns its mirror image. This extends reverse by reversing both the top-level list and all sublists recursively.

    if (is_null(p))
    {
        return null();
    }
    if (is_atom(p))
    {
        return p;
    }
    return append(total_reverse(cdr(p)), cons(total_reverse(car(p)), null()));
}


list shape(list p)
{
    // Takes a recursive list (not an atom) and returns a recursive list that consists only of the parentheses structure of the original.
    if (is_null(p))
    {
        return null();
    }
    if (is_atom(car(p)))
    {
        return cons(null(), shape(cdr(p)));
    }
    else
    {
        return cons(shape(car(p)), shape(cdr(p)));
    }
}


list intersection(list p, list q)
{
    // Takes two lists of distinct atoms (representing sets) and returns a list of atoms that appear in both p and q. The empty list represents the empty set.
    if ( is_null(p) )
    {
        return null();
    }
    if (member(car(p), q))
    {
        return cons(car(p), intersection(cdr(p), q));
    }
    return intersection(cdr(p), q);
}


list list_union(list p, list q)
{
    // Takes two lists of distinct atoms (representing sets) and returns a list of the union of p and q, without repetition.
    if (is_null(p))
    {
        return q;
    }
    if ((!member(car(p), q)))
    {
        return cons(car(p),list_union(cdr(p), q));
    }
    return list_union(cdr(p), q);
}


list substitute(list old_atom, list new_atom, list p)
{
//     Takes a list of atoms (atoms may repeat) and returns a copy of p with every occurrence of atom old replaced by atom new. For example:
//
// substitute(a, x, (a b a c)) = (x b x c)

    if (is_null(p))
    {
        return null();
    }
    if (eq(car(p), old_atom))
    {
        return cons(new_atom, substitute(old_atom, new_atom, cdr(p)));
    }
    return cons(car(p), substitute(old_atom, new_atom, cdr(p)));
}


list remove(list p, list a)
{
//     Takes a list of atoms and an atom a, and returns a list that does not contain a. All occurrences of a are removed. For example:
//
// remove((a b a c b), a) = (b c b)
    if (is_null(p))
    {
        return p;
    }
    if (eq(car(p), a))
    {
        return remove(cdr(p), a);
    }
    return cons(car(p), remove(cdr(p), a));
}


bool subset(list p, list q)
{
    //     Takes two lists (neither of which is an atom) and returns true if every atom in p also appears in q (treating them as sets). For example:
    //
    // subset(((a) b), ((a) b c)) = true
    // subset(((a b) c), (c (a b) d)) = true
    // subset(((a b) c), (c d)) = false
    // subset((a b), (a b c d)) = true
    // subset((a d), (a b c)) = false
    // ((a b) c), (c (a b) d)

    if (is_null(p))
    {
        return true;
    }
    if (is_atom(car(p)))
    {
        if (!member(car(p), q))
        {
            return false;
        }
        else
        {
            return subset(cdr(p), q);
        }
    }
    else
    {
        return subset(car(p), q) && subset(cdr(p), q);
    }
}


// Below is the incomplete extra credit problem. See README.md for details on work done.

// list insert_all_positions(list x, list r) {
//     if (is_null(r)) {
//         return cons(cons(x, null()), null());
//     }
// }
//


// list permute(list p) {
    // Takes a list of atoms and returns a list whose elements are all distinct permutations of p. For example:
    //
    // permute((a b c)) = ((a b c) (a c b) (b a c) (b c a) (c a b) (c b a))
    //
    // The order of permutations may vary. This problem is optional and worth 10 points extra credit.
    //
// }
//     if (is_null(p)) {
//         return cons(null(), null());
//     }
//
//     list x = car(p);
//     list r = cdr(p);
//     list p2 = permute(cdr(p));
//
//     if (is_null(r)) {
//         return null();
//     }
//     append (insert_all_positions(x, car(r)), insert_all_positions(x, cdr(r)));
// }




