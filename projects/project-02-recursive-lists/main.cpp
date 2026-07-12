#include<iostream>
#include"reclists.hpp"
#include"solutions.hpp"

// Test numNodesAtTheTopLevel()
void testNumNodesAtTheTopLevel() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "The number of nodes at the top level of the input list is: "
        << numNodesAtTheTopLevel(p) << std::endl;
}

// Test is_lat()
void testIs_Lat() {
    std::cout << "Enter a list: ";
    list p2 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p2);
    if (is_lat(p2)) {
        std::cout << "The list is entirely made of atoms: " << std::endl;
    }
    else {
        std::cout << "The list is not entirely made of atoms: " << std::endl;
    }
}


// Test member()
void testMember() {
    std::cout << "Enter an atom: ";
    list p3 = read_list();
    std::cout << "Echoing the atom that you entered below." << std::endl;
    write_list(p3);
    std::cout << "Enter a list: ";
    list p4 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p4);
    if (member(p3, p4)) {
        std::cout << "Atom " << p3 << " is in list " << p4 << "." << std::endl;
    }
    else {
        std::cout << "Atom " << p3 << " is not in list " << p4 << "." << std::endl;

    }
}


void testLast() {
    std::cout << "Enter a list: ";
    list p = read_list();
    write_list(p);
    std::cout << "The last element in the list is: " << std::endl;
    std::cout << last(p) << std::endl;
}

void testList_Pair() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "Enter a list: ";
    list q = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(q);
    std::cout << "The list of pairs from " << p << " and " << q << " are: " << std::endl;
    std::cout << list_pair(p,q) << std::endl;
}


void testFirsts() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "The list of first elements in this list are " << firsts(p) << std::endl;
}

void testFlat() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "The flattened list is " << flat(p) << std::endl;
}

void testTwo_The_Same() {
    std::cout << "Enter a list: ";
    list p1 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p1);
    std::cout << "Enter a list: ";
    list p2 = read_list();
    write_list(p2);
    if (two_the_same(p1, p2)) {
        std::cout << "The list has 1 of the same element." << std::endl;
    }
    else {
        std::cout << "The lists do not share any elements." << std::endl;
    }
}


void testTotal_Reverse() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "The total reverse, mirror image of " << p << " is: " << total_reverse(p) << std::endl;
}


void testShape() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "The structure of this list is: " << shape(p) << std::endl;
}


void testEqual() {
    std::cout << "Enter a list: " << std::endl;
    list p1 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p1);
    std::cout << "Enter a list: " << std::endl;
    list p2 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p2);
    if (equal(p1, p2)) {
        std::cout << "Lists are equal." << std::endl;
    }
    else {
        std::cout << "Lists are not equal." << std::endl;
    }
}

void testIntersection() {
    std::cout << "Enter a list: ";
    list p1 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p1);
    std::cout << "Enter a list: ";
    list p2 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p2);
    std::cout << "The intersection of list " << p1 << " and " << p2 << " is " << intersection(p1, p2) << std::endl;
}


void testList_Union() {
    std::cout << "Enter a list: ";
    list p1 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p1);
    std::cout << "Enter a list: ";
    list p2 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p2);
    std::cout << "The union of list " << p1 << " and " << p2 << " is " << list_union(p1, p2) << std::endl;
}


void testSubstitute() {
    std::cout << "Enter the atom to replace: ";
    list p1 = read_list();
    std::cout << "Echoing the atom to replace. " << std::endl;
    write_list(p1);
    std::cout << "Enter the replacement atom: " << std::endl;
    list p2 = read_list();
    std::cout << "Echoing the atom the new replacement atom. " << std::endl;
    write_list(p2);
    std::cout << "Enter a list: " << std::endl;
    list p3 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p3);
    std::cout << "The altered list is " << substitute(p1,p2, p3) << std::endl;
}

void testRemove() {
    std::cout << "Enter a list: ";
    list p = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p);
    std::cout << "Enter an atom to remove: ";
    list p2 = read_list();
    std::cout << "Echoing the atom that you entered below." << std::endl;
    write_list(p2);
    std::cout << "Here is the list with the atom removed: " << remove(p, p2) << std::endl;
}

void testSubset() {
    std::cout << "Enter a list: ";
    list p1 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p1);
    std::cout << "Enter a list: ";
    list p2 = read_list();
    std::cout << "Echoing the list that you entered below." << std::endl;
    write_list(p2);
    if (subset(p1, p2)) {
        std::cout << "Lists are equal." << std::endl;
    }
    else {
        std::cout << "Lists are not equal." << std::endl;
    }
}


// void testPermute() {
//     std::cout << "Enter a list: ";
//     list p = read_list();
//     std::cout << "Echoing the list that you entered below." << std::endl;
//     write_list(p);
//     std::cout << "The permutations of p are: " << permute(p) << std::endl;
// }

int main()
{
    testNumNodesAtTheTopLevel();
    testIs_Lat();
    testMember();
    testLast();
    testList_Pair();
    testFirsts();
    testFlat();
    testTwo_The_Same();
    testEqual();
    testTotal_Reverse();
    testShape();
    testIntersection();
    testList_Union();
    testSubstitute();
    testRemove();
    testSubset();

    // testPermute();


    return 0;
}
