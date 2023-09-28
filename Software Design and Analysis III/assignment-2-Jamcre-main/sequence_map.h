// Name: James Michael Crespo
// Email: james.crespo64@myhunter.cuny.edu
// Description: Class 'SequenceMap' initializes an object (similar to 2D array), and supports operations such as summation

#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <cstddef>
#include <sstream>
#include <algorithm>

class SequenceMap
{
public:
    // BIG FIVE
    // Zero-parameter constructor.
    SequenceMap() = default;

    // Copy-constructor.
    SequenceMap(const SequenceMap &rhs)
    {
        recognition_sequence_ = rhs.recognition_sequence_;
        for (size_t i{0}; i < rhs.enzyme_acronyms_.size(); i++)
        {
            enzyme_acronyms_.push_back(rhs.enzyme_acronyms_[i]);
        }
    }

    // Copy-assignment.
    SequenceMap &operator=(const SequenceMap &rhs)
    {
        SequenceMap copy = rhs;
        std::swap(*this, copy);
        return *this;
    }
    // Move-constructor.
    SequenceMap(SequenceMap &&rhs)
    {
        recognition_sequence_ = rhs.recognition_sequence_;
        enzyme_acronyms_ = std::move(rhs.enzyme_acronyms_);
    }

    // Move-assignment.
    SequenceMap &operator=(SequenceMap &&rhs)
    {
        std::swap(recognition_sequence_, rhs.recognition_sequence_);
        std::swap(enzyme_acronyms_, rhs.enzyme_acronyms_);
        return rhs;
    }

    // Destructor.
    ~SequenceMap()
    {
        recognition_sequence_ = "";
        enzyme_acronyms_.clear();
    }
    // END BIG FIVE

    // 2 Paramater-constructor.
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro)
    {
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back(an_enz_acro);
    }

    // 1 Parameter-constructor.
    SequenceMap(const std::string &a_rec_seq)
    {
        recognition_sequence_ = a_rec_seq;
        enzyme_acronyms_.push_back("");
    }

    // Overload '<' operator
    bool operator<(const SequenceMap &rhs) const
    {
        return (recognition_sequence_ < rhs.recognition_sequence_);
    }

    // Overload '>' operator
    bool operator>(const SequenceMap &rhs) const
    {
        return (recognition_sequence_ > rhs.recognition_sequence_);
    }

    // Merge other Seq_Map to current Seq_Map
    void Merge(const SequenceMap &other_sequence)
    {
        for (size_t i{0}; i < other_sequence.enzyme_acronyms_.size(); i++)
        {
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }

    // Overload '<<' operator
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &some_seq_map)
    {
        for (size_t i{0}; i < some_seq_map.enzyme_acronyms_.size(); i++)
        {
            out << some_seq_map.enzyme_acronyms_[i] << " ";
        }
        return out;
    }

private:
    std::string recognition_sequence_;
    std::vector<std::string> enzyme_acronyms_;
};
#endif