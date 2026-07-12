#pragma once
#include <vector>
#include "Dictionary.hpp"

class SortedVectorDict : public Dictionary {
public:
    void insert(int key) override;
    bool lookup(int key) const override;
    void remove(int key) override;

private:
    std::vector<int> data;

};