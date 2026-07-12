# Dictionary Benchmark

## Student Information

- Will Meyer

## Structure

- `src/`: Contains `Dictionary` interface and `UnsortedVectorDict` implementation.
- `.github/workflows/test.yml`: GitHub Actions CI setup.

## How It Works

1. UnsortedVectorDict.cpp is complete and the main function contains the necessary code to test it. 
2. The output provides the average run-time for the **insert** and **lookup** function. However, only the average run-time values for the unsorted vector variation is meaningful as the other variations have not been implemented yet.    
3. GitHub Actions runs
4. Implented all four structures and added the time for remove in main(). The benchmark inserts N random keys and does M lookups/removes. 
5. Units for testing: (Insert and Remove in microseconds, Avg Lookup in nanoseconds)

## Run Locally

```bash
mkdir build && cd build
cmake ..
make
ctest --output-on-failure
```

## Lab 01



**Collaboration**

I was partnered with Kevin in the lab. Our first instinct was to begin coding the sorted linked list which quickly proved
to be a challenging task. Both of us needed to review the syntax and implementation rules for a singularly linked list.
With the help of Regina, the class tutor, we were able to make progress on the code, and we began to remember how this data
structure functions.

In addition to in person assistance, multiple online resources were used which include looking at examples from the following websites:

https://www.geeksforgeeks.org/
https://www.youtube.com/ - Specifically CodeBeauty's collection of videos on lists
https://stackoverflow.com/

**AI Use**

I used ChatGPT for explanation of concepts, reminders about syntax and also to look at code examples for topics which I had forgotten. 
Specifically, I needed to review implementation of nodes and pointer manipulation for linked lists, and I also needed help in resizing 
vectors. I generally asked ChatGPT to avoid writing the code for me and to just explain the concepts I needed to implement. There were
certainly instances when I needed to see code examples to get started. All final code was written and adapted by me and I understand
how it works.

**Implementaion Details**

Data Structures Implemented

- UnsortedVectorDict: Given
- SortedVectorDict: Vector is sorted in Ascending order.
  - Search for position, then shift right to resize vector and place key in proper place.
  - Look up using logic for Binary Search
  - Remove preserves order by shifting left and popping back.
- UnsortedLinkedListDict: unsorted singly linked list 
  - Insert at head - Constant time complexity - O(1)
  - Lookup using a linear scan 
  - Remove first match by relinking prev->next to curr->next and then deleting node.
- SortedLinkedListDict: singly linked list in ascending order 
  - Insert in first position >= key. 
  - Lookup is a straight forward search. No change to the list.
  - Remove early exits when curr->data > key.

## Final Output

My output times seem rather high. Either my algorithms are not optimized for best efficiency added with the fact that I am working on
an IMAC from 2013 with a much slower processor, or some combination of the two.

/Users/willmeyer/Documents/Dev_Projects/CLion/dictionary-benchmark/cmake-build-debug/DictionaryBenchmark
Unsorted Vector [N=5000] — Insert: 311us, Avg Lookup: 22834ns, Remove: 11155us
Sorted Vector [N=5000] — Insert: 71271us, Avg Lookup: 227ns, Remove: 86us
Unsorted Linked List [N=5000] — Insert: 353us, Avg Lookup: 17145ns, Remove: 9432us
Sorted Linked List [N=5000] — Insert: 37392us, Avg Lookup: 13601ns, Remove: 7423us
Unsorted Vector [N=500000] — Insert: 27641us, Avg Lookup: 2271383ns, Remove: 1110895us
Sorted Vector [N=500000] — Insert: 659211372us, Avg Lookup: 280ns, Remove: 125us
Unsorted Linked List [N=500000] — Insert: 30483us, Avg Lookup: 1682897ns, Remove: 837425us
Sorted Linked List [N=500000] — Insert: 2344233027us, Avg Lookup: 7915623ns, Remove: 4145853us

Process finished with exit code 0
