#include "SortedLinkedListDict.hpp"

// SortedLinkedListDict
// Invariant: Node list must stay in sorted ascending order by value
// Duplicate Policy: Allowed
// Remove Policy: Remove one Occurrence
// Complexity: Insert O(n), Lookup O(n) with early exit, Remove O(n)

// Insert a new key into the list while maintaining ascending order.
// Pre: List is sorted
// Post: New node with key data is inserted at the first position >= key. The list remains sorted after insert.
void SortedLinkedListDict::insert(int key)
{
    //1. Initialize cursors for the traverse.
    Node* curr = head;
    Node* prev = nullptr;

    //2. Check if list is empty. If list is empty, new node becomes head.
    if (head == nullptr)
    {
        Node* newNode = new Node();
        newNode->data = key;
        newNode->next = nullptr;
        head = newNode;
        return;
    }

    //3. Traverse until correct position is found.
    while (curr != nullptr && curr->data < key)
    {
        prev = curr;
        curr = curr->next;
    }

    //4. Check Head, Middle and Tail for new location.
    Node* newNode = new Node();
    newNode->data = key;

    if (prev == nullptr)         // Place node at beginning if Head is the location for newNode
    {
        newNode->next = curr;
        head = newNode;
    }
    else if (curr == nullptr)   // Place node at end if Tail is the location for newNode
    {
        prev->next = newNode;
        newNode->next = nullptr;
    }
    else                        // Place node somewhere in the middle if that is the location for the newNode.
    {
        newNode->next = curr;
        prev->next = newNode;
    }
}


// Return true if key is present, false otherwise.
// Traversal stops when current node's value > key.
// Pre: List is sorted
// Post: Returns true if match found, false otherwise. The list doesn't change.
bool SortedLinkedListDict::lookup(int key) const
{
    //1. Set a curr to traverse the list
    Node *curr = head;

    //2. Create a traversal loop
    while (curr != nullptr && curr->data < key)
    {
        curr = curr->next;
    }

    //3. Lookup key, if found return true, else, false. If list is empty, return false.
    if (curr != nullptr && curr->data == key)
    {
        return true;
    }
    else
    {
        return false;
    }
}



// Remove the key from the list.
// Does nothing if the key is not found.
// Pre: List is sorted.
// Post: If found, removes the first node with data == key. List remains sorted. If the list does not have a match, no change.
    void SortedLinkedListDict::remove(int key)
    {
        Node* curr = head;
        Node* prev = nullptr;

        while ( curr != nullptr && curr->data < key )
        {
            prev = curr;
            curr = curr->next;
        }

        if ( curr == nullptr || curr->data > key ) // Not found, early exit
        {
            return;
        }


        if ( prev == nullptr )
        {
            head = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        delete curr;
    }





