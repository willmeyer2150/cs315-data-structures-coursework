#include "UnsortedVectorDict.hpp"

void UnsortedVectorDict::insert(int key) {
    data.push_back(key);
}

std::size_t UnsortedVectorDict::lookup_idx(int key) const {

    // Performs a linear search on an unsorted container.
    // Returns index i (0 <= i < data.size() and data[i] == key); otherwise returns data.size() ("not found").

    for (auto i = 0; i < data.size(); i++) {
        if (data[i] == key)
            return i;
    }
    return data.size();

}


bool UnsortedVectorDict::lookup(int key) const {

    auto idx = lookup_idx(key);
    return idx != data.size();
}

void UnsortedVectorDict::remove(int key) {

    // If key is a member, replaces it with the last item on the list.

    auto idx = lookup_idx(key);
    if(idx != data.size()) {
        data[idx] = data.back();
        data.pop_back();
    }
}
