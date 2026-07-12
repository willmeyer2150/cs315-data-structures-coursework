#include "UnsortedLinkedListDict.hpp"

// Unsorted singly linked list
// Invariant: None, list is not sorted
// Duplicate policy: allowed
// Remove policy: remove one occurrence
// Complexity: Insert O(1), Lookup O(n) with early exit, Remove O(n)

// Insert a new key into an unsorted list. Order not important.
// Pre: List is not sorted.
// Post: A new node becomes the new head and head now points to the newNode.
void UnsortedLinkedListDict::insert(int key)
{
    Node* newNode = new Node;
    newNode->data = key;
    newNode->next = head;
    head = newNode; // inserts newNode at head
}

// Return true if key is present, false otherwise.
// Pre: List is unsorted
// Post: Returns true if match found, false otherwise. The list doesn't change.
bool UnsortedLinkedListDict::lookup(int key) const
{
    Node* curr = head; // Set a curr to traverse the list

    // Linear scan for key
    while ( curr != nullptr )
    {
        if ( curr->data == key )
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Remove the key from the list.
// Does nothing if the key is not found.
// Pre: List is not sorted.
// Post: If found, removes the first node with data == key. head gets updated if first node is removed. If the list does not have a match, no change.
void UnsortedLinkedListDict::remove(int key)
{
    Node* curr = head;
    Node* prev = nullptr;

    while ( curr != nullptr && curr->data != key )
    {
        prev = curr;
        curr = curr->next;
    }

    if ( curr == nullptr )
    {
        return; // key not found
    }

    if ( prev == nullptr ) // head is key
    {
        head = curr->next;
    }
    else
    {
        prev->next = curr->next;
    }
    delete curr;
}