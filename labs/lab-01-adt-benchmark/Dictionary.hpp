#pragma once

// This class serves as a super class of ADTs that
// implement Dictionary operations.

class Dictionary {
public:
    virtual void insert(int key) = 0;
    virtual bool lookup(int key) const = 0;
    virtual void remove(int key) = 0;
    virtual ~Dictionary() = default;
};