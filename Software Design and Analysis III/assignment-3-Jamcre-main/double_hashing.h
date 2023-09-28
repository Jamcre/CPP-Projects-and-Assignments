// NAME: James Michael Crespo
// DESCRIPTION: Implementation of double hashing

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace
{

    // Internal method to test if a positive number is prime.
    bool IsPrimeDouble(size_t n)
    {
        if (n == 2 || n == 3)
            return true;

        if (n == 1 || n % 2 == 0)
            return false;

        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;

        return true;
    }

    // Internal method to return a prime number at least as large as n.
    int NextPrimeDouble(size_t n)
    {
        if (n % 2 == 0)
            ++n;
        while (!IsPrimeDouble(n))
            n += 2;
        return n;
    }

} // namespace

// Double hashing implementation.
// Adjusted naming for double hashing
template <typename HashedObj>
class HashTableDouble
{
public:
    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

    // Table Constructor, with R value of 89
    explicit HashTableDouble(size_t size = 101) : array_(NextPrimeDouble(size))
    {
        MakeEmpty();
        R = 89;
    }

    // Table Constructor, with user provided R value
    explicit HashTableDouble(int r_value, size_t size = 101) : array_(NextPrimeDouble(size))
    {
        MakeEmpty();
        // Check if user R value is valid (is Prime)
        if (!IsPrimeDouble(r_value))
        {
            r_value = NextPrimeDouble(r_value);
        }
        R = r_value;
    }

    bool Contains(const HashedObj &x) const
    {
        return IsActive(FindPos(x));
    }

    /*--------------------------------- START ----------------------------------*/

    /*--------------------------------- PART A ---------------------------------*/

    // Returns the total number of elements in Hash Table
    size_t getTotalElements()
    {
        return current_size_;
    }

    // Returns the size of the Hash Table
    size_t getSize()
    {
        return array_.size();
    }

    // Returns the load factor of the Hash Table
    float getLoadFactor()
    {
        return (float(getTotalElements()) / getSize());
    }

    // Returns the total number of collisions in Hash Table
    size_t getTotalCollisions()
    {
        return total_collisions;
    }

    // Returns the average number of collisions in Hash table
    float getAverageCollisions()
    {
        return (float(getTotalCollisions()) / getTotalElements());
    }

    /*--------------------------------- PART B ---------------------------------*/

    // Returns the total number of probes needed to determine if a queried word is in Hash Table
    size_t getTotalProbes()
    {
        return total_probes;
    }

    /*----------------------------------- END ----------------------------------*/

    void MakeEmpty()
    {
        current_size_ = 0;
        for (auto &entry : array_)
            entry.info_ = EMPTY;
    }

    bool Insert(const HashedObj &x)
    {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;

        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;

        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();
        return true;
    }

    bool Insert(HashedObj &&x)
    {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;

        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;

        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();

        return true;
    }

    bool Remove(const HashedObj &x)
    {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
            return false;

        array_[current_pos].info_ = DELETED;
        return true;
    }

private:
    struct HashEntry
    {
        HashedObj element_;
        EntryType info_;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element_{e}, info_{i} {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element_{std::move(e)}, info_{i} {}
    };

    std::vector<HashEntry> array_;
    size_t current_size_;
    /*--------------------------------- PART A ---------------------------------*/
    // Collision counter to be used in FindPos(), 'mutable' needed because FindPos() is a const member
    mutable size_t total_collisions;
    /*--------------------------------- PART B ---------------------------------*/
    // Probe counter to be used in FindPos(), 'mutable' needed because FindPos() is a const member
    mutable size_t total_probes;
    /*----------------------------- DOUBLE HASHING -----------------------------*/
    // R value for double hashing function
    int R;
    size_t Hash2(const HashedObj &x) const
    {
        static std::hash<HashedObj> hf;
        return R - (hf(x) % R);
    }
    /*----------------------------------- END ----------------------------------*/

    bool IsActive(size_t current_pos) const
    {
        return array_[current_pos].info_ == ACTIVE;
    }

    size_t FindPos(const HashedObj &x) const
    {
        size_t current_pos = InternalHash(x);
        total_probes = 1; // 1st Probe

        while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x)
        {
            // Compute ith probe.
            current_pos = InternalHash(x) + total_probes * Hash2(x) % array_.size();
            total_probes++;     // Increment probe counter each loop iteration
            total_collisions++; // Increment collision counter each loop iteration
            if (current_pos >= array_.size())
                current_pos -= array_.size();
        }
        return current_pos;
    }

    void Rehash()
    {
        std::vector<HashEntry> old_array = array_;

        // Create new double-sized, empty table.
        array_.resize(NextPrimeDouble(2 * old_array.size()));
        for (auto &entry : array_)
            entry.info_ = EMPTY;

        // Copy table over.
        current_size_ = 0;
        for (auto &entry : old_array)
            if (entry.info_ == ACTIVE)
                Insert(std::move(entry.element_));
    }

    size_t InternalHash(const HashedObj &x) const
    {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size();
    }
};

#endif // DOUBLE_HASHING_H