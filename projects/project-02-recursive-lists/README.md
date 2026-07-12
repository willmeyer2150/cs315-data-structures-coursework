## Student Information

Name: Will Meyer

___

## Collaboration & Sources

This project is the product of my own work with the exception of collaboration with the following:
- Professor Kooshesh clarified the use of `eq()` usage which only takes atoms. He also explained list traversal using
`car` and `cdr`.
  - Functions he assisted on: `equal()`, `intersection()`, `list_union()`. 
- Website Resources: None
- AI Use: Chatgpt was used to understand concepts and the building blocks for these functions:
  - `is_lat()`, `list_pair()`, `firsts()`, `flat()`, `two_the_same()`, `shape()` and `permute()`. 
  - No code was copied from chatgpt. 
  - I prompt for help to be provided without showing the answer. 
  - Exception (Extra Credit – `permute()`): I couldn’t finish this one on my own so I left it incomplete and what work
  I did on it is commented out. Here is the work I tried to complete the `permute()` function.
      - I tried recursively calling permute on the tail cdr(p), but was unable to figure out how to locate the individual beginning points for each permutation.
      - Chatgpt showed the use of a helper to insert a head x into every position of each tail-permutation, and finally append all those results together to get the full set of permutations. 
      - This works because to get permutations of the whole list, you can stick x into every possible position of each permutation of r (a subset of p) (front, middle spots, end).
      - Do this for every permutation of r and then append them all together. That gives all permutations of the original list.
      - Where I got stuck is implementing the recursive “insert x into every position” cleanly (without extra helpers/loops), and correctly grouping results.
___

## Implementation Details

```
**std::ostream& operator<<(std::ostream& os, list p) {}**
  - helper function to write p to os via write_list(p)
  - returns os for chaining cout statements.
  - Example: std::cout << "p = " << p << '\n';
```
___

```
**list append(list p, list q) {}**
- returns a new list of p and q joined together.
  - Base case: if p is empty, just return q.
  - else, construct a list with the first element and recursively call append again on the rest of p and q.
```
___

```
**int numNodesAtTheTopLevel(list p) {}**
- returns the number of nodes at the top level
  - this function was done for us.
```
___
```
**bool is_lat(list p) {}**
- Return trues if the list is entirely made of atoms 
- Base case: if the list is empty, return false since there are no atoms 
- Next case: check if the first item is an atom, if not, return false 
- Otherwise, recursively call the function again with the rest of the list until you reach an empty list
```
___
```
**bool member(list p, list q) {}**
- Returns true if atom p is found anywhere in list q (a deep search).
- Base case: if q is empty, return false.
- If car(q) is an atom:
    - If eq(p, car(q)), return true;
    - Otherwise, recurse on member(p, cdr(q)).
- If car(q) is a list:
    - If member(p, car(q)) is true, return true;
    - Otherwise, recurse on member(p, cdr(q)).
- If never found, recursion ends at the base case and returns false.
```
___
```
**list last(list p) {}**
- Takes a non-empty list and returns the last element.
  - Base case: if cdr(p) is empty, return car(p) (the current element just before the end).
  - Otherwise, recursively call last(cdr(p)) to move through the list.
```
___
```
**list list_pair(list p, list q) {}**
- Takes two lists of atoms of the same length and returns a list of pairs
  - Each pair contains corresponding atoms from p and q. Ex: list_pair((a b c), (d e f)) = ((a d) (b e) (c f)))
- Base case: if lists p and q are empty, return an empty list
- Otherwise: construct a new list of pairs
  - pair = cons(car(p), car(q), null())
  - return cons(pair, list(cdr(p), cdr(q))) to traverse the rest of the list.
```
___
```
**list firsts(list p) {}**
- Takes a list of sublists of atoms and returns a new list of the first element from each sublist.
- Base case: if p is empty, return null().
- Otherwise, construct a new list with car(car(p)) at the front and recursively call firsts(cdr(p)) for the rest.
```
___
```
**list flat(list p) {}**
- Takes a list (not an atom) and returns a list in which all nested parentheses are removed (except the outer set).
- Base case: if p is empty, return null()
- If car(p) is an atom, return cons(car(p), flat(cdr(p))) to get the rest.
- Otherwise, car(p) is a list so append(flat(car(p)), flat(cdr(p))) to finish
```
___
```
**bool two_the_same(list p, list q) {}**
- Takes two lists and returns true if p and q share at least one atom in common.
- Base case: if list p is empty, return false. Nothing to compare.
- If car(p) is a member of q (helper function: member), return true.
- Otherwise, recursively call two_the_same(cdr(p), q) and continue checking until found or base case is met
```
___
```
**bool equal(list p, list q) {}**
- Takes two recursive lists and determines if they are identical:
  - parentheses must match in structure and all atoms must be identical in name and position.
- Base case: if both p and q are empty, return true as they are identical.
- Next case: if one of p or q are empty, return false since they are different lengths.
- if car(p) and car(q) are atoms:
  - if they are not equal, return false;
  - otherwise, recursively call equal(cdr(p), cdr(q)) to check the rest of the list
- if either of car(p) or car(q) is an atom, and the other is not, return false;
- if car(p) and car(q) ar equal, recursively call equal(cdr(p), cdr(q)) to catch the rest
- if all else fails, return false;
```
___
```
**list total_reverse(list p) {}** 
- Takes a recursive list and returns its mirror image.
  - This extends reverse by reversing both the top-level list and all sublists recursively.
- Base case: if p is empty, return null().
- if p is an atom, return p.
- otherwise, append(total_reverse(cdr(p)), cons(total_reverse(car(p)), null())).
  - new tail built from total_reverse(car(p), null())
  - new head built from total_reverse(cdr(p))
```
___
```
**list shape(list p) {}**
- Takes a recursive list (not an atom) and returns a recursive list that consists only of the parentheses structure of the original.
- Base case: if p is empty, return null().
- if car(p) is an atom, construct a new list with null() as the new head and recursively call shape(cdr(p)) to fill in the tail.
- if car(p) is a list, construct the list on shape(car(p)) as the head and shape(cdr(p)) as the tail.
- This eliminates the atoms held in the parenthesis.
```
___
```
**list intersection(list p, list q) {}**
- Takes two lists of distinct atoms (representing sets) and returns a list of atoms that appear in both p and q. 
  - The empty list represents the empty set.
- Base case: if p is empty, return null().
- if car(p) is a member of q, construct a new list with car(p) as head and recursively call intersection(cdr(p), q) to fill in the tail
- if car(p) was not a member, recurse of on intersection(cdr(p),q) to traverse the rest of the list.
```
___
```
**list list_union(list p, list q) {}**
- Takes two lists of distinct atoms (representing sets) and returns a list of the union of p and q, without repetition.
- Base case: if p is empty, just return q.
- if car(p) is not a member of q, (call helper function: member)
  - contruct a new list with car(p) as the head and traverse the rest of list_union(cdr(p), cdr(q)) to fill in the tail
- if car(p) was a member, then skip it by recursing on list_union(cdr(p), q) and continue building.
```
___
```
**list substitute(list old_atom, list new_atom, list p) {}**
- Takes a list of atoms (atoms may repeat) and returns a copy of p with every occurrence of atom old replaced by atom new.
- Base case: if p is empty, return null().
- if car(p) matches the old_atom
  - construct a new list with new_atom as the new head and recursively call substitute(old_atom, new_atom, cdr(p)) to move through the rest of list.
- if car(p) did not match the old atom
  - construct the list with car(p) as the head and continue looking for the old_atom by recursively calling substitute(old_atom, new_atom, cdr(p)).
If the old_atom was found, the new list will now contain new_atom in its place.
```
___
```
**list remove(list p, list a) {}**
- Takes a list of atoms and an atom a, and returns a list that does not contain a.
  - All occurrences of a are removed.
- Base case: if p is empty, return p.
- if car(p) is equal to atom a,
  - recursively call remove(cdr(p), a) to skip it and move through the rest of list.
- if car(p) was not equal to atom a.
  - construct a new list by keeping car(p) at the head and continue traversing the list by recursively calling remove(cdr(p), a)
- The result will be a list without atom a. 
```

___
```
**bool subset(list p, list q) {}** 
- Takes two lists (neither of which is an atom) and returns true if every atom in p also appears in q (treating them as sets).
- Base case: if p is empty, return null().
- if car(p) is an atom, check if it isn't a member of q
  - if it isn't, return false;
  - otherwise, recursively call subset(cdr(p), q)
- if car(p) was a list
  - recursively call subset(car(p),q) and subset(cdr(p), q) to traverse the entire list.
- If every atom of p is also in q, return true, otherwise, false.
```
___
```
**list permute(list p) {}**
incomplete
```
___

## Testing & Status

Local & CLion: Built and ran successfully.  
Blue Server: Built and ran successfully.

CMake version of project was set to (v.4.0) - this caused a failure to run on Blue.  
Set CMake file version to 3.27.7 to match blue 

CMakeLists.txt Changes:

`cmake_minimum_required(VERSION 3.27)`  
`set(CMAKE_CXX_STANDARD 17)`  
`set(CMAKE_CXX_STANDARD_REQUIRED ON)`


Remove any non-portable internal headers, e.g.:

// DELETE (private libc++ header; breaks under GCC/libstdc++):  
// #include <__ranges/reverse_view.h>


Test inputs: sampleInputForRecLists.txt plus additional manual test cases
- (empty, single, nested, duplicates).

Preconditions: Followed assignment preconditions; invalid inputs may throw error.
