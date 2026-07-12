#include <iostream>

#include "heap.hpp"
#include "priority_queue.hpp"
#include "TreeNode.hpp"

bool verifyPrefixFree(const TreeNode* root) {
    if (root == nullptr) return true;

    if (root->hasSymbol() && root->isLeaf())
        return false;

    return verifyPrefixFree(root->leftSubtree()) && verifyPrefixFree(root->rightSubtree());
}



bool minCompare(const std::pair<int,int>& a,
                const std::pair<int,int>& b) {
    return a.first < b.first;   // smaller keys = higher priority
}


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> heap;
    heap.push_back(0);

    std::cout << "Inserting values: 10, 4, 15, 20, 1, 8\n:";

    heapInsert(heap, 10);
    printHeap(heap);

    heapInsert(heap, 4);
    printHeap(heap);

    heapInsert(heap, 15);
    printHeap(heap);

    heapInsert(heap, 20);
    printHeap(heap);

    heapInsert(heap, 1);
    printHeap(heap);

    heapInsert(heap, 8);
    printHeap(heap);

    std::cout << "Deleting minimum: ";

    while (heap.size() > 1) {
        std::cout << "Min = " << heap[1] << " ";
        heapDeleteMin(heap);
        printHeap(heap);
    }


    PriorityQueue pq(minCompare);

    pq.insert({5, 100});   // priority = 5, payload = 100
    pq.insert({2, 200});
    pq.insert({8, 300});
    pq.insert({1, 400});

    std::cout << "Min element = " << pq.findMin().first
              << " (payload " << pq.findMin().second << ")\n";

    std::cout << "\nExtracting elements in priority order:\n";
    while (!pq.empty()) {
        auto p = pq.extractMin();
        std::cout << p.first << "  (payload " << p.second << ")\n";
    }

    TreeNode* A = new TreeNode('A');
    TreeNode* B = new TreeNode('B');
    TreeNode* C = new TreeNode('C');
    TreeNode* internal = new TreeNode(-1, B, C);
    TreeNode* root = new TreeNode(-1, A, internal);

    std::cout << "Prefix free: " << verifyPrefixFree(root) << "\n";
    delete root;
    return 0;
}