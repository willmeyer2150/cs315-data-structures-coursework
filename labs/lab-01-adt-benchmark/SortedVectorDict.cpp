#include "SortedVectorDict.hpp"

// SortedVectorDict
// Invariant: Vector must stay in sorted ascending order by value
// Duplicate Policy: Allowed
// Remove Policy: Remove one occurrence
// Complexity: Insert O(n), Lookup O(logn) with early exit, Remove O(n)

// Insert a new key into the list while maintaining ascending order.
// Pre: Vector is sorted.
// Post: Data remains sorted and vector increases in size by 1.
void SortedVectorDict::insert(int key)
{
    // 1.Search for the insertion index - first element >= key
    std::size_t i = 0;
    while ( i < data.size() && data[i] < key )
    {
        ++i;
    }
    // 2. Increase vector by 1
    data.push_back(0);

    // 3. Shift elements to the right starting at the back.
    for ( std::size_t j = data.size() -1; j > i; --j )
    {
        data[ j ] = data[ j - 1 ];
    }
    data[i] = key; // Place new element
}

// Return true if key is present, false otherwise.
// Traversal stops when current node's value > key.
// Pre: Vector is sorted.
// Post: Uses binary search to return presence of key in a vector.
bool SortedVectorDict::lookup(int key) const {
size_t low  = 0;
size_t high = data.size();

// binary search
while (low < high)
{
    size_t mid = low + (high - low) / 2 ;
    if ( data[mid] == key ) // Key found, return true
    {
        return true;
    }
    else if ( data[mid] < key )
    {
        low = mid + 1;      // Searches the right half
    }
    else
    {
        high = mid;    // Searches the left half
    }
}
return false;
}

// Remove the key from the list.
// Does nothing if the key is not found.
// Pre: Vector is sorted.
// Post: If key is found at index i, elements (i + 1) are shifted left by 1. Size of vector decreases by 1. Remains sorted after removal. If key is not found, nothing changed.
void SortedVectorDict::remove(int key)
{
    size_t low  = 0;
    size_t high = data.size();

// binary search - half open interval check [low, high)
    while (low < high)  // Loop ends when low == high
    {
        size_t mid = low + (high - low) / 2; // Find the mid point
            if ( data[mid] < key )  // move to right half
        {
            low = mid + 1;
        }
        else                        // Move to the left half
        {
            high = mid;
        }
    }

    if ( low == data.size() || data[low] != key )    // if  Key not present
    {
        return;
    }

    // Shift tail left by 1
    size_t i = low;
    for ( size_t j = i + 1; j < data.size(); ++j )
    {
        data[ j - 1 ] = data[j];
    }
    data.pop_back(); // Delete last element
}