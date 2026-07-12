#include <iostream>
#include <vector>

// For this lab, you are to write an iterative and a recursive solution to each of the following problems.

bool iterativeMember(const std::vector<int> &numbers, size_t n, int key) {
    // Write an iterative solution for the member problem.
    // Is "key" one of the values in numbers[0 .. n-1]?

    // A few notes on this solution
    // Some students may use one of the following form to solve this problem:
    // for(auto v: numbers)
    // or
    // for(size_t i = 0; i < numbers.size(); i++)

    // Both of these variations, even though they work,
    // are incorrect as they iterate over all elements of "numbers".
    // The point of writing this function iteratively is to prepare them
    // for the recursive version. In the recursive version, before (or after)
    // each recursive call, they will have to reduce the number of the elements
    // of "numbers" that are under consideration, by one. Because of that,
    // the signature of the recursive function will have to have an argument
    // that represents the number of elements of "numbers", that are under
    // consideration, and it is the last element that gets compared to "key".
    // Because of that, this function also receives "n" as an argument to
    // make it possible for them to mimic the recursive version. That is why
    // "n" has been passed to this function. This function usuall get called like this:

    // iterativeMember(numbers, numbers.size(), key);

    for(auto idx = 0; idx < n; idx++)
        if(numbers.at(idx) == key)
            return true;
    return false;  // This is a placeholder to make clion happy
}

bool recursiveMember(const std::vector<int> &numbers, size_t n, int key) {
    // Write a recursive solution to the member problem.
    // Is "key" one of the values in numbers[0 .. n-1]?

    // One of the main confusions here is the expression "n - 1",
    // which appears in two different contexts. "n" is the number
    // of elements of "numbers" that are under consideration.
    // Therefore, numbers.at(n - 1) refers the "n^th" element of
    // "numbers", which is at index "n - 1", while in recursiveMember(numbers, n - 1, key),
    // it reduces the number of element that the recursive call
    // should consider for membership test.


    if( n == 0 )
        return false;

    if( numbers.at(n - 1) == key)
        return true;


    return recursiveMember(numbers, n - 1, key);
}

bool iterativeAreIdentical(const std::vector<int> &numbers1, const std::vector<int> &numbers2, size_t n) {
    // Write an iterative solution to the are-identical problem.
    // Given two vectors each of which has n elements, do they contain the same elements in
    // the same positions?

    // Example 1:
    // numbers1 contains 34, 21, 80, 56, 100
    // numbers2 contains 34, 21, 80, 56, 100
    // iterativeAreIdentical(numbers1, number2, 5) should return true.

    // Example 2:
    // numbers1 contains 32, 21, 80, 56, 100
    // numbers2 contains 34, 100, 30, 56, 21
    // iterativeAreIdentical(numbers1, number2, 5) should return false.

    for(auto i = 0; i < n; i++)
        if(numbers1.at(i) != numbers2.at(i))
            return false;
    return true;
}

bool recursiveAreIdentical(const std::vector<int> &numbers1, const std::vector<int> &numbers2, size_t n) {
    // Write a recursive solution to the are-identical problem.
    // Given two vectors each of which has n elements, do they contain the same elements in
    // the same positions?

    // Example 1:
    // numbers1 contains 34, 21, 80, 56, 100
    // numbers2 contains 34, 21, 80, 56, 100
    // iterativeAreIdentical(numbers1, number2, 5) should return true.

    // Example 2:
    // numbers1 contains 32, 21, 80, 56, 100
    // numbers2 contains 34, 100, 30, 56, 21
    // iterativeAreIdentical(numbers1, number2, 5) should return false.

    if( n == 0 )
        return true;

    if(numbers1.at(n - 1) != numbers2.at(n - 1))
        return false;

    return recursiveAreIdentical(numbers1, numbers2, n - 1);
}

bool iterativePalindrome(const std::string &s) {
    // Given a string, determine if it is a palindrome or not.
    // A string is said to be a palindrome if it is reads the
    // same forward and backward. For example, "dad" and "kayak"
    // are palindromes.
    // Recall that you can use array de-referencing operator
    // to refer to the characters of strings.
    // For example, if s is a string, you could do: s[0], s[1],
    // s[name.length()-1], to refer to the first, second, and
    // the last character of the string, respectively.

    for(size_t leftIdx = 0, rightIdx = s.length() - 1; leftIdx < rightIdx; leftIdx++, rightIdx--)
        if(s.at(leftIdx) != s.at(rightIdx))
            return false;
    return true;
}


bool recursivePalindrome(const std::string &s, size_t leftIdx, size_t rightIdx) {
   // Given a string, determine if the characters in the range
   // s[leftIdx] ... s[rightIdx] form a palindrome or not.
   // Write this one recursively.

   if(leftIdx >= rightIdx)
       return true;

    if(s.at(leftIdx) != s.at(rightIdx))
        return false;

   return recursivePalindrome(s, leftIdx + 1, rightIdx - 1);
}

int countInversionsIteratively(const std::vector<int> &v, size_t n) {
    // Two consecutive values in a vector are inverted at index i if
    // v.at(i) > v.at(i+1). The assumption is that i+1 < n.

    // A sorted list with n elements does not have any inversion
    // because v.at(i) <= v.at(i+1) when 0 <= i < n - 1.

    // This function counts and returns the number of inversions
    // in the first n elements of v.

    // For example, if v contains {5, 8, 10, 6, 7},
    // this function should return 1 as 10 is larger
    // than 6 -- the only inversion in this list.

    auto numInversions = 0;
    for(size_t i = 1; i < n; i++)
        if(v.at(i) < v.at(i - 1))
            numInversions++;
    return numInversions;
}

int countInversionsRecursively(const std::vector<int> &v, size_t n) {
     // Count and return the number of inversion in the first n
     // elements of v, recursively.

     if(n <= 1)
         return 0;

     if(v.at(n - 1) < v.at(n - 2))
         return 1 + countInversionsRecursively(v, n - 1);
     return  countInversionsRecursively(v, n - 1);
}

bool iterativePalindrome2(const std::string &s) {
    // Given a string, determine if it is a palindrome or not.
    // This time, s could contain non-letter characters.
    // Your task is to ignore those and only compare the letters
    // to determine if s is a palindrome or not.

    // For example, the string "a man, a plan, a canal, panama"
    // is a palindrome if you were to ignore the non-letter
    // characters.

    // You should NOT preprocess the string. That is,
    // you can not write a loop to collect the letters
    // into a string and then process this new string.
    // That is, you should only have one loop.

    size_t leftIdx = 0, rightIdx = s.length() - 1;
    while(leftIdx < rightIdx) {
        if(! isalpha(s.at(leftIdx)))
            leftIdx++;
        else if(! isalpha(s.at(rightIdx)))
            rightIdx--;
        else if(s.at(leftIdx) != s.at(rightIdx))
            return false;
        else {
            leftIdx++;
            rightIdx--;
        }
    }

    return true;
}


bool recursivePalindrome2(const std::string &s, int leftIdx, int rightIdx) {
    // Given a string, determine if the characters in the range
    // s[leftIdx] ... s[rightIdx] form a palindrome or not.
    // Write this one recursively.

    // You should NOT preprocess the string.

    // You should NOT preprocess the string. That is,
    // you can not write a loop to collect the letters
    // into a string and then process this new string.
    if(leftIdx >= rightIdx)
        return true;

    if(! isalpha(s.at(leftIdx)))
        return recursivePalindrome2(s, leftIdx + 1, rightIdx);

    if(! isalpha(s.at(rightIdx)))
        return recursivePalindrome2(s, leftIdx, rightIdx - 1);

    if(s.at(leftIdx) != s.at(rightIdx))
        return false;

    return recursivePalindrome2(s, leftIdx + 1, rightIdx - 1);
}


void iterativeIntersection(const std::vector<int> &values1,
                          const std::vector<int> &values2,
                          std::vector<int> &result, size_t values1NumElements, size_t values2NumElements) {
    // "values1" and "values2", two independent vectors, have "values1NumElements" and
    // "values2NumElements" values. This function finds the elements that are on both lists and
    // adds them to "result".


    // Example:
    // values1 contains: 1, 2, 13, 4, 15, 6, 7
    // values1NumElements is 7

    // values2 contains: 5, 2, 10, 4, 21, 6
    // values2NumElements is 6

    // std::vector<int> result = {}  -- an empty vector
    // After having called iterativeIntersection(values1, values2, result, 7, 6)
    // result should contain: 2, 4, 6. These are elements that are on both lists.

    // You will have to write a helper function to solve this problem. This function
    // performs a lookup and based on the outcome, the calling function decide whether
    // to add an element to the "result" or not.

    for(size_t i = 0; i < values1NumElements; i++)
        if(iterativeMember(values2, values2NumElements, values1.at(i)))
            result.push_back(values1.at(i));

}

void recursiveIntersection(const std::vector<int> &values1,
                          const std::vector<int> &values2,
                           std::vector<int> &result, size_t values1NumElements, size_t values2NumElements) {
    // "values1" and "values2", two independent vectors, have "values1NumElements" and
    // "values2NumElements" values. This function finds the elements that are on both lists and
    // adds them to "result".


    // Example:
    // values1 contains: 1, 2, 13, 4, 15, 6, 7
    // values1NumElements is 7

    // values2 contains: 5, 2, 10, 4, 21, 6
    // values2NumElements is 6

    // std::vector<int> result = {}  -- an empty vector
    // After having called iterativeIntersection(values1, values2, result, 7, 6)
    // result should contain: 2, 4, 6. These are elements that are on both lists.


    // You will have to write a recursive helper function to solve this problem. This function
    // performs a lookup and based on the outcome, the calling function decide whether
    // to add an element to the "result" or not.

    if(values1NumElements == 0)
        return;

    if(recursiveMember(values2, values2NumElements, values1.at(values1NumElements - 1)))
        result.push_back(values1.at(values1NumElements - 1));
    recursiveIntersection(values1, values2, result, values1NumElements - 1, values2NumElements);

}

void testMember( bool (*member)(const std::vector<int> &, size_t, int)) {

    std::vector<int> numbers = {10, 20, 65, 23, 66, 42, 12, 55};
    std::cout << "Testing iterative member begins. \n";
    std::cout << "Do not expect any output if the function works properly.\n";

    // Yes cases:
    for(auto v: numbers) {
        if (!member(numbers, numbers.size(), v)) {
            std::cout << "Iterative member fails. " << v
                      << " is a member, but the function returned false.\n";
            exit(1);
        }
    }

    // No cases
    std::vector<int> numbers2 = {9, 22, 68, 28, 60, 38, 120, 50};
    for(auto v: numbers2) {
        if (member(numbers, numbers.size(), v)) {
            std::cout << "Iterative member fails. " << v
                      << " is not a member, but the function returned true.\n";
            exit(1);
        }
    }

    std::cout << "Testing iterative member ends...\n";
}

void testAreIdentical(bool (*areIdentical)(const std::vector<int> &, const std::vector<int> &, size_t n), int id) {

    // The role of "id" is to, in case of an error, to make it easuer to
    // determine where it occurred. In its absence, the error messages
    // have to be more verbose.

    std::vector<int> numbers1 = {10, 28, 65, 23, 66, 42, 12, 55};
    std::vector<int> numbers2 = {10, 28, 65, 23, 70, 42, 12, 55};

    std::cout << "Testing are identical begins...\n";
    if( areIdentical(numbers1, numbers1, numbers1.size()) )
        std::cout << "Are Identical works! (" << id << ")" << std::endl;
    else
        std::cout << "iterativeAreIdentical doesn't work! (" << id << ")" << std::endl;

    if( areIdentical(numbers1, numbers2, numbers1.size()) )
        std::cout << "iterativeAreIdentical doesn't work! (" << id + 1 << ")" << std::endl;
    else
        std::cout << "Are Identical works! (" << id + 1 << ")" << std::endl;
    std::cout << "Testing are identical begins...\n";

}

void testInteractivePlaindrome() {
    std::string s1 = "madam", s2 = "madman";

    if(iterativePalindrome(s1))
        std::cout << "iterativePalindrome works! (1)" << std::endl;
    else
        std::cout << "iterativePalindrome doesn't work! (1)" << std::endl;


    if(! iterativePalindrome(s2))
        std::cout << "iterativePalindrome works! (3)" << std::endl;
    else
        std::cout << "iterativePalindrome doesn't work! (3)" << std::endl;

}

void testRecursivePalindrome() {
    std::string s1 = "madam", s2 = "madman";

    if(recursivePalindrome(s1, 0, s1.length() - 1))
        std::cout << "recursivePalindrome works! (2)" << std::endl;
    else
        std::cout << "recursivePalindrome doesn't work! (2)" << std::endl;

    if(! recursivePalindrome(s2, 0, s2.length() - 1))
        std::cout << "recursivePalindrome works! (4)" << std::endl;
    else
        std::cout << "recursivePalindrome doesn't work! (4)" << std::endl;

}

void testInteractivePlaindrome2() {
    std::string s3 = "a man, a plan, a canal, panama", s4 = "a man, no plan, a canal, panama";

    if(iterativePalindrome2(s3))
        std::cout << "iterativePalindrome2 works! (5)" << std::endl;
    else
        std::cout << "iterativePalindrome2 doesn't work! (5)" << std::endl;

    if(! iterativePalindrome2(s4))
        std::cout << "iterativePalindrome2 works! (5)" << std::endl;
    else
        std::cout << "iterativePalindrome2 doesn't work! (5)" << std::endl;

}

void testRecursivePlaindrome2() {
    std::string s3 = "a man, a plan, a canal, panama", s4 = "a man, no plan, a canal, panama";

    if(recursivePalindrome2(s3, 0, s3.length() - 1))
        std::cout << "recursivePalindrome2 works! (6)" << std::endl;
    else
        std::cout << "recursivePalindrome2 doesn't work! (6)" << std::endl;

    if(! recursivePalindrome2(s4, 0, s4.length() - 1))
        std::cout << "recursivePalindrome2 works! (6)" << std::endl;
    else
        std::cout << "recursivePalindrome2 doesn't work! (6)" << std::endl;

}

void testCountInversions(int (*countInversions)(const std::vector<int> &, size_t), int id) {
    std::vector<int> increasing = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        decreasing = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        mixed = {1, 10, 2, 9, 3, 8, 4, 7, 5, 5};
    int mixedInversions = 4;

    if(countInversions(increasing, increasing.size()) == 0)
        std::cout << "Count Inversions works! (" << id << ")\n";
    else
        std::cout << "Count Inversions doesn't work! (" << id << ")\n";

    if(countInversions(decreasing, increasing.size()) == decreasing.size() - 1)
        std::cout << "Count Inversions works! (" << id + 1 << ")\n";
    else
        std::cout << "Count Inversions doesn't work! (" << id + 1 << ")\n";

    if(countInversions(mixed, increasing.size()) == mixedInversions)
        std::cout << "Count Inversions works! (" << id + 2 << ")\n";
    else
        std::cout << "Count Inversions doesn't work! (" << id + 2 << ")\n";

}

void testIntersection(void (*intersection)(const std::vector<int> &values1,
                                   const std::vector<int> &values2,
                                   std::vector<int> &result,
                                   size_t values1NumElements, size_t values2NumElements),
                      int id) {

    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
            v2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
            v3 = {10, 11, 12, 13, 14},
            result;


    // a full intersection

    std::cout << "Testing intersection begins...\n";
    std::cout << "No output will be printed if all tests pass.\n";
    intersection(v1, v2, result, v1.size(), v2.size());
    if(result.size() != v1.size()) {
        std::cout << "Intersection fails (" << id << ")\n";
        return;
    }

    for(auto v: result)
        if(!iterativeMember(v1, v1.size(), v)) {
            std::cout << "Intersection fails (" << id + 1 << ")\n";
            return;
        }


    // v1 and v3 have only one value in common

    std::vector<int> result2;
    intersection(v1, v3, result2, v1.size(), v3.size());

    if(result2.size() != 1) {
        std::cout << "Intersection fails (" << id + 2 << ")\n";
        return;
    }

    if(result2.at(0) != 10)
        std::cout << "Intersection fails (" << id + 3 << ")\n";

    std::cout << "Testing intersection ends...\n";
}

int main() {
    // Here is how you can create a vector and initialize it.

    testMember(iterativeMember);
    testMember(recursiveMember);

    testAreIdentical(iterativeAreIdentical, 1);
    testAreIdentical(recursiveAreIdentical, 3);

    testInteractivePlaindrome();
    testRecursivePalindrome();

    testInteractivePlaindrome2();
    testRecursivePlaindrome2();

    testCountInversions(countInversionsIteratively, 1);
    testCountInversions(countInversionsRecursively, 4);

    testIntersection(iterativeIntersection, 1);
    testIntersection(recursiveIntersection, 5);

    return 0;
}
