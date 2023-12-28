/**
 * @file bigint.hpp
 * @author Jingxuan Liu
 * @brief A program of class for arbitrary-precision integers
 * @version 0.1
 * @date 2023-12-27
 * @copyright Copyright (c) 2023 Jingxuan Liu
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;

class bigInt
{
public:
    /**
     * @brief Constructor with no arguments:
     * define a arbitrary-precision integers that has value 0.
     */
    bigInt();

    /**
     * @brief Constructor with one arguments:
     * define a arbitrary-precision integers that has value of input.
     * @param _int a signed 64-bit integer.
     */
    bigInt(const int64_t&);

    /**
     * @brief Constructor with one arguments:
     * define a arbitrary-precision integers that has value of input.
     * @param _str a string.
     */
    bigInt(const string&);

    /**
     * @brief Change or initialize the value of bigint.
     * takes a signed 64-bit integer and converts it to an arbitrary-precision integer.
     * @param _int a signed 64-bit integer.
     */
    void set_value(const int64_t&);

    /**
     * @brief Change or initialize the value of bigint.
     * takes a string and converts it to an arbitrary-precision integer.
     * @param _int a string.
     */
    void set_value(const string&);

    /**
     * @brief Change or initialize the sign of bigint.
     * takes a char and make it to an sign of arbitrary-precision integer.
     * @param _sign a char.
     */
    void set_sign(const char&);

    /**
     * @brief Get the size of value.
     * @return The size of the value.
     */
    size_t size () const;

    /**
     * @brief Get the digit of value by index.
     * @param index a size_t integer.
     * @return The digit stored in that index.
     */
    uint8_t get(const size_t) const;

    /**
     * @brief Get the sign of the bigint.
     * @return The value of the sign variable.
     */
    char get_sign() const;

    /**
     * @brief Get the value of the bigint.
     * @return The value of the value variable.
     */
    vector<uint8_t> get_value() const;

    /**
     * @brief Overloaded binary operator +=:
     * add another bigint to this bigint.
     * @param other The bigint to add.
     * @return The this bigints after the add.
     */
    bigInt& operator+=(const bigInt&);

    /**
     * @brief Overloaded binary operator -=:
     * subtract another bigint from this bigint.
     * @param other The bigint for sub.
     * @return The this bigints after the sub.
     */
    bigInt& operator-=(const bigInt&);

    /**
     * @brief Overloaded binary operator *=:
     * multiply another bigint to this bigint.
     * @param other The bigint to multiply.
     * @return The this bigints after the multiply.
     */
    bigInt& operator*=(const bigInt&);

    /**
     * @brief Overloaded binary operator =:
     * Assign a string or signed 64_bit integer to a bigint.
     * @param _str (or _int) The string or integer.
     * @return The this bigints that has the value of the input.
     */
    bigInt& operator=(int64_t);
    bigInt& operator=(string);


    /**
     * @brief Eception to be thrown if input string for constructor contain invalid char.
     */
    inline static invalid_argument invalid_string = invalid_argument("Input a invalid string that contain the char can't cover to digit.");

private:
    vector<uint8_t> value; //store the digit of the integer.
    char sign; // store the sign of the integer.
};

/**
 * @brief Overloaded binary operator <<:
 * print out a bigInt through a stream.
 * @param out The stream.
 * @param bigint The bigint to print.
 * @return The stream.
 */
ostream& operator<<(ostream&, const bigInt&);

/**
 * @brief Overloaded binary operator +:
 * add two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return Sum of two bigint.
 */
bigInt operator+(bigInt, const bigInt&);

/**
 * @brief Overloaded binary operator -:
 * subtract two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return Difference of two bigint.
 */
bigInt operator-(bigInt, const bigInt&);

/**
 * @brief Overloaded binary operator *:
 * multiply two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return Product of two bigint.
 */
bigInt operator*(bigInt, const bigInt&);

/**
 * @brief Overloaded unary operator -:
 * negation the bigint.
 * @param _bigint The bigint.
 * @return Bigint that has negation sign.
 */
bigInt operator-(bigInt);

/**
 * @brief Overloaded binary operator <:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs < rhs, otherwise false.
 */
bool operator<(const bigInt&, const bigInt&);

/**
 * @brief Overloaded binary operator <=:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs <= rhs, otherwise false.
 */
bool operator<=(const bigInt&, const bigInt&);

/**
 * @brief Overloaded binary operator >:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs > rhs, otherwise false.
 */
bool operator>(const bigInt&, const bigInt&);

/**
 * @brief Overloaded binary operator >=:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs >= rhs, otherwise false.
 */
bool operator>=(const bigInt&, const bigInt&);

/**
 * @brief Overloaded binary operator ==:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs == rhs, otherwise false.
 */
bool operator==(const bigInt&, const bigInt&);

/**
 * @brief Overloaded binary operator !=:
 * compare two bigints.
 * @param lhs The left side bigint.
 * @param rhs The right side bigint.
 * @return True if lhs != rhs, otherwise false.
 */
bool operator!=(const bigInt&, const bigInt&);


// Helper funcitons:

/**
 * @brief Check the it's a invalid string.
 * @param _str The string.
 * @return True if every char in str can cover to digit, otherwise false.
 */
bool isValid(string);

/**
 * @brief Add two vectors that represent non-negative numbers:
 * @param lhs The left side vector.
 * @param rhs The right side vector.
 * @return A vector that represent sum of two vectors.
 */
vector<uint8_t> Add(const vector<uint8_t>&, const vector<uint8_t>&);

/**
 * @brief Sub two vectors that represent non-negative numbers:
 * @param lhs The left side vector.
 * @param rhs The right side vector.
 * @return A vector that represent difference of two vectors.
 */
vector<uint8_t> Sub(const vector<uint8_t>&, const vector<uint8_t>&);

/**
 * @brief Multiply two vectors that represent non-negative numbers:
 * @param lhs The left side vector.
 * @param rhs The right side vector.
 * @return A vector that represent product of two vectors.
 */
vector<uint8_t> Mul(const vector<uint8_t>&, const vector<uint8_t>&);

/**
 * @brief Remove the leading 0 elements in the vector:
 * @param value The vecotr that may conation leading 0.
 * @return A vector that removed leading 0 elements.
 */
void removeZeroHeader(vector<uint8_t>&);

/**
 * @brief Compare if left vector is less than right vector:
 * vector represent the non-negative numbers.
 * @param lhs The left side vector.
 * @param rhs The right side vector.
 * @return True if lhs less than rhs, otherwise false.
 */
bool isLess(const vector<uint8_t>&, const vector<uint8_t>&);