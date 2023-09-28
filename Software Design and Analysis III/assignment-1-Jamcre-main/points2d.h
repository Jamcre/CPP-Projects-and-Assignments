// Name: James Michael Crespo
// Email: james.crespo64@myhunter.cuny.edu
// Description: Class 'Points2D' initializes an object (similar to 2D array), and supports operations such as summation

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <algorithm>

namespace teaching_project
{
    template <typename Object>
    class Points2D
    {
    public:
        // The 'Big five'

        // Zero-parameter constructor.
        // Set sequence_ to nullptr, and size_ to 0
        Points2D() : sequence_{nullptr}, size_{0} {};

        // Copy-constructor.
        // Copies the size and sequence_ from the rhs object to this object.
        // @param rhs : The Points2D object to copy from.
        Points2D(const Points2D &rhs)
        {
            size_ = rhs.size_;
            sequence_ = new std::array<Object, 2>[size_];

            for (size_t i{0}; i < size_; i++)
            {
                sequence_[i][0] = rhs.sequence_[i][0];
                sequence_[i][1] = rhs.sequence_[i][1];
            }
        }

        // Copy-assignment.
        // Copies the size and sequence_ from the rhs object to this object.
        // @param rhs: The Points2D object to copy from.
        // @return   : This Points2D object.
        Points2D &operator=(const Points2D &rhs)
        {
            Points2D copy{rhs};
            std::swap(*this, copy);
            return *this;
        }

        // Move-constructor.
        // Moves the size and sequence_ from the rhs object to this object, and sets the rhs object's size to 0 and sequence_ to nullptr.
        // @param rhs : The Points2D object to move from.
        Points2D(Points2D &&rhs) : sequence_{std::move(rhs.sequence_)}, size_{std::move(rhs.size_)}
        {
            rhs.sequence_ = nullptr;
            rhs.size_ = 0;
        }

        // Move-assignment.
        // Swaps the size and sequence_ of this object with the rhs object.
        // @param rhs : The Points2D object to move from.
        // @return    : This Points2D object.
        Points2D &operator=(Points2D &&rhs)
        {
            std::swap(sequence_, rhs.sequence_);
            std::swap(size_, rhs.size_);
            return rhs;
        }

        // Destructor.
        // Deletes the sequence_ array
        ~Points2D()
        {
            sequence_ = nullptr;
        }

        // End of big-five.

        // One parameter constructor.
        // Constructs a Points2D object with inputted points, dynamically allocates memory for said object, and sets size_ = 1
        // @param item : points that will be added to sequence
        Points2D(const std::array<Object, 2> &item) : sequence_{new std::array<Object, 2>{item}}, size_{1} {}

        // Accessor Function for Sequence Size
        size_t size() const { return size_; }

        // '[]' Overload, const version.
        // Overloading the '[]' to accurate access 'sequence_' array, abort() if 'location' is out-of-range.
        // @param location : an index to a location in the sequence.
        // @returns        : the point at @location.
        const std::array<Object, 2> &operator[](size_t location) const
        {
            if (location > size_)
            {
                std::cout << "ERROR";
                std::abort();
            }
            return sequence_[location];
        }

        // '+' Overload
        // Overloading the '[]' to support summation of sequences
        // @param c1 : A sequence.
        // @param c2 : A second sequence.
        // @return   : Sum of sequences. If the sequences are different sizes, append the result with rest of the larger sequence.
        friend Points2D operator+(const Points2D &c1, const Points2D &c2)
        {
            Points2D sequence_sum;
            size_t small_sequence = std::min(c1.size_, c2.size_), large_sequence = std::max(c1.size_, c2.size_);

            sequence_sum.size_ = large_sequence;
            sequence_sum.sequence_ = new std::array<Object, 2>[large_sequence];

            for (size_t i{0}; i < small_sequence; i++)
            {
                sequence_sum.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                sequence_sum.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }

            if (large_sequence > small_sequence)
            {
                for (size_t i{small_sequence}; i < large_sequence; i++)
                {
                    if (c1.size_ > c2.size_)
                    {
                        sequence_sum.sequence_[i][0] = c1.sequence_[i][0];
                        sequence_sum.sequence_[i][1] = c1.sequence_[i][1];
                    }
                    if (c2.size_ > c1.size_)
                    {
                        sequence_sum.sequence_[i][0] = c2.sequence_[i][0];
                        sequence_sum.sequence_[i][1] = c2.sequence_[i][1];
                    }
                }
            }
            return sequence_sum;
        }

        // '<<' Overload.
        // @return : an output stream
        friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points)
        {
            if (some_points.sequence_ == nullptr)
            {
                out << "()";
            }
            else
            {
                for (size_t i{0}; i < some_points.size_; i++)
                {
                    out << "(" << some_points.sequence_[i][0] << ", " << some_points.sequence_[i][1] << ") ";
                }
            }
            std::cout << std::endl;
            return out;
        }

        // '>>' Overload.
        // @return : an input stream
        friend std::istream &operator>>(std::istream &in, Points2D &some_points)
        {
            Object next_input;
            size_t points, index{0}, counter;

            in >> points;
            some_points.size_ = points;
            some_points.sequence_ = new std::array<Object, 2>[points];

            counter = points * 2;
            while (counter > 0)
            {
                if (!(in >> next_input))
                {
                    std::cout << "Error";
                    std::abort();
                }
                else
                {
                    some_points.sequence_[index][counter % 2] = next_input;
                    counter--;
                    if (counter % 2 == 0)
                    {
                        index++;
                    }
                }
            }
            std::cout << std::endl;
            return in;
        }

    private:
        // Sequence of points.
        std::array<Object, 2> *sequence_;
        // Size of sequence.
        size_t size_;
    };

} // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_
