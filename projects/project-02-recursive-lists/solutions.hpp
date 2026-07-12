#ifndef __MY_SOLUTION_HPP__
#define __MY_SOLUTION_HPP__

#include<iostream>
#include"reclists.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, list p);
list append();
int numNodesAtTheTopLevel(list p);
list append(list p, list q);
list reverseTopLevel(list p);
bool is_lat(list p);
bool member(list p, list q);
list last(list p);
list list_pair(list p, list q);
list firsts(list p);
list flat(list p);
bool two_the_same(list p, list q);
bool equal(list p, list q);
list total_reverse(list p);
list shape(list p);
list intersection(list p, list q);
list list_union(list p, list q);
list substitute(list old_atom, list new_atom, list p);
list remove(list p, list a);
bool subset(list p, list q);

// list permute(list p); // incomplete implementation -- See README for details.


#endif
