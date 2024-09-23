#ifndef BIGINT_H
#define BIGINT_H


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class BigInt {
private:

    //store digits in reverse order
    vector<int> digits;

    // helper function to remove leading zeros
    void removeLeadingZeros()
    {
        while (digits.size() > 1 && digits.back() == 0)
        {
            digits.pop_back();
        }
    }

public:

    // defeault constructors initializes BigInt to zero
    BigInt() : digits(1, 0) {}

    BigInt(const int num)
    {
        string result = to_string(num);
        for (int i = result.size() - 1; i >= 0; --i)
        {
            digits.push_back(result[i] - '0'); // converts character to integar equivalent 
        }

    }

    // constructs big int from a string
    BigInt(const string& num)
    {
        for (int i = num.size() - 1; i >= 0; --i)
        {
            digits.push_back(num[i] - '0'); // converts character to integar equivalent 
        }
    }

    // overload addition operator
    /*
Just to give an overview how this works-- it essentially works like addition
tables we did in elementary school so like

           1   2   3
               4   5  +
        ----------------
                   8
               6
           1
  it basically does each number one at a time starting from the end
*/
    BigInt operator+(const BigInt& other) const
    {
        BigInt result;
        result.digits.clear();
        int carry = 0, sum = 0;
        size_t i = 0; // index for iteration

        while (i < digits.size() || i < other.digits.size() || carry != 0)
        {
            sum = carry; // start with carry from previous addition
            if (i < digits.size()) // add digit to sum if possible
            {
                sum += digits[i];
            }
            if (i < other.digits.size()) // add digit to other sum if possible
            {
                sum += other.digits[i];
            }
            carry = sum / 10; // same logic as when adding by hand, if the result if over 10 you drop the ones place and carry the tens digit
            result.digits.push_back(sum % 10); // makes sure the sum is only one digit
            i++;
        }
        result.removeLeadingZeros();
        return result;
    }

    // Overloaded multiplication operator
    BigInt operator*(const BigInt& other) const {
        BigInt result;               // Resultant BigInt for storing product
        result.digits.resize(digits.size() + other.digits.size(), 0); // Initialize result size

        // Multiply each digit of the first number by each digit of the second number
        for (size_t i = 0; i < digits.size(); ++i) {
            int carry = 0;           // Initialize carry for multiplication
            for (size_t j = 0; j < other.digits.size() || carry != 0; ++j) {
                long long mul = result.digits[i + j] + carry +
                    digits[i] * 1LL * (j < other.digits.size() ? other.digits[j] : 0); // Calculate product
                result.digits[i + j] = mul % 10; // Store current digit
                carry = mul / 10;    // Calculate new carry
            }
        }

        result.removeLeadingZeros(); // Remove leading zeros from result
        return result;
    }

    // Overloaded output stream operator for printing BigInt
    friend ostream& operator<<(ostream& os, const BigInt& obj) {
        // Output digits in reverse order (since they are stored in reverse order)
        for (int i = obj.digits.size() - 1; i >= 0; --i) {
            os << obj.digits[i];    // Print each digit
        }
        return os;                  // Return the output stream
    }

};

#endif