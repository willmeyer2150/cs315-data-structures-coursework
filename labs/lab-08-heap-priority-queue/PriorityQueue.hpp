//
// Created by Kooshesh on 10/15/25.
//

#include <vector>

// pragma once;

class PriorityQueue {
public:
    explicit PriorityQueue();
    bool insert(int v);
    void deleteMin();
    [[nodiscard]] int findMin() const;
    [[nodiscard]] bool empty() const;
    unsigned long size();

private:
    std::vector<int> heap;

};


