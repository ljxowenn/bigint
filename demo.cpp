/**
 * @file demo.cpp
 * @author Jingxuan Liu
 * @brief The implementation for the bigint class
 * @version 0.1
 * @date 2023-12-27
 * @copyright Copyright (c) 2023 Jingxuan Liu
 */

#include <iostream>
#include "bigint.hpp"
using namespace std;

bigInt::bigInt()
{
    set_value(0);
}

bigInt::bigInt(const int64_t &_int)
{
    set_value(_int);
}

bigInt::bigInt(const string &_str)
{
    set_value(_str);
}

void bigInt::set_value(const int64_t &_int)
{
    value.clear();
    if (_int >= 0)
        sign = '+';
    else
        sign = '-';
    int64_t temp = abs(_int); //temp int for while loop
    do
    {
        uint8_t digit = (uint8_t)(temp % 10);
        value.push_back(digit);

        temp /= 10;
    } while (temp > 0) ;
}

void bigInt::set_value(const string &_str)
{
    value.clear();
    if (!isValid(_str))
        throw invalid_string;
    for (size_t i = _str.size() - (size_t)1; i > 0; --i)
        value.push_back(uint8_t(_str.at(i) - '0'));
    if (_str.at(0) == '-')
        sign = '-';
    else if (_str.at(0) == '+')
        sign = '+';
    else
    {
        sign = '+';
        value.push_back(uint8_t(_str.at(0) - '0'));
    }
    // remove the zero header.
    removeZeroHeader(value);
}

void bigInt::set_sign(const char& _sign)
{
    sign = _sign;
}

size_t bigInt::size() const
{
    return value.size();
}

uint8_t bigInt::get(const size_t index) const
{
    return value.at(index);
}

char bigInt::get_sign() const
{
    return sign;
}

vector<uint8_t> bigInt::get_value() const
{
    return value;
}

ostream& operator<<(ostream& out, const bigInt& bigint)
{
    out << bigint.get_sign();
    for (size_t i = bigint.size() - (size_t)1; i > 0; --i) // we loop in a oppsite way,
        out << (int)bigint.get(i); // print out the number in right order.
    out << (int)bigint.get(0);
    return out;
}

bigInt& bigInt::operator=(int64_t _int)
{
    set_value(_int);
    return *this;
}

bigInt& bigInt::operator=(string _str)
{
    set_value(_str);
    return *this;
}

bool isValid(string _str)
{
    if ((_str.at(0) != '+' && _str.at(0) != '-') && (_str.at(0) < '0' || _str.at(0) > '9'))
        return false;

    for (size_t i = 1; i < _str.size(); ++i)
    {
        if (_str.at(i) < '0' || _str.at(i) > '9')
         return false;
    }

    return true;
}

void removeZeroHeader(vector<uint8_t>& value) 
{
    // we go through the index that is zero header.
    while (!value.empty() && value.back() == (uint8_t)0) {
        value.pop_back(); // remove the 0 header
    }

    if (value.empty()) 
        value.push_back(0); // If all zero, we consider it as number 0.
}

bool isLess(const vector<uint8_t>& lhs, const vector<uint8_t>& rhs)
{
    if (lhs.size() < rhs.size())
        return true;
    else if (lhs.size() > rhs.size())
        return false;

    for (size_t i = lhs.size() - (size_t)1; i > 0; --i)
    {
        if (lhs.at(i) < rhs.at(i))
            return true;
    }
    if (lhs.at(0) < rhs.at(0))
        return true;

    return false;
}


vector<uint8_t> Add(const vector<uint8_t>& lhs, const vector<uint8_t>& rhs)
{
    int64_t carry = 0;
    size_t i = 0;
    uint8_t digit1 = 0; 
    uint8_t digit2 = 0;
    vector<uint8_t> result;

    while (i < lhs.size() || i < rhs.size() || carry)
    {
        if (i < lhs.size())
            digit1 = lhs.at(i);
        else
            digit1 = 0;
        if (i < rhs.size())
            digit2 = rhs.at(i);
        else
            digit2 = 0;
        
        int64_t sum = digit1 + digit2 + carry;
        carry = sum / 10; // check if we have carry.

        result.push_back(uint8_t(sum % 10));
        
        ++i;
    } 

    // handle the zero header
    removeZeroHeader(result);

    return result;
}

vector<uint8_t> Sub(const vector<uint8_t>& lhs, const vector<uint8_t>& rhs)
{
    int64_t borrow = 0;
    size_t i = 0;
    uint8_t digit1 = 0;
    uint8_t digit2 = 0;
    vector<uint8_t> result;

    while (i < lhs.size() || i < rhs.size() || borrow)
    {
        if (i < lhs.size())
            digit1 = lhs.at(i);
        else
            digit1 = 0;
        if (i < rhs.size())
            digit2 = rhs.at(i);
        else
            digit2 = 0;

        int64_t diff = digit1 - digit2 - borrow;
        if (diff < 0) // check if we have borrow.
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        
        result.push_back((uint8_t)diff);
        ++i;
    }

    // handle the zero header
    removeZeroHeader(result);
    
    return result;
}

vector<uint8_t> Mul(const vector<uint8_t>& lhs, const vector<uint8_t>& rhs)
{
    int64_t carry;
    vector<uint8_t> result;
    vector<uint8_t> temp;

    for (size_t i = 0; i < rhs.size(); ++i)
    {
        carry = 0;
        temp.clear();
        temp.resize(i, 0);
        for (size_t j = 0; (j < lhs.size()) || carry; ++j)
        {
            int64_t product = rhs.at(i) * lhs.at(j) + carry;
            temp.push_back(uint8_t(product % 10));
            carry = product / 10;
        }
        if (carry)
            temp.push_back((uint8_t)carry);

        result = Add(result, temp);
    }

     // handle the zero header
    removeZeroHeader(result);

    return result;
}

bigInt& bigInt::operator+=(const bigInt& other)
{
    if (sign == '+')
    {
        switch (other.sign)
        {
        case '+': // +(left + right)
            value = Add(value, other.value);
            break;
        case '-': // +(left - right)
            if (isLess(value, other.value))
            {
                value = Sub(other.value, value);
                sign = '-';
            }
            else
                value = Sub(value, other.value);
            break;
        }
    }
    else if (sign == '-')
    {
        switch (other.sign)
        {
        case '+': // +(right - left)
            if (isLess(other.value, value))
                value = Sub(value, other.value);
            else
            {
                value = Sub(other.value, value);
                sign = '+';
            }
            break;
        case '-': // -(left + right)
            value = Add(value, other.value);
            break;
        }
    }

    return *this;
}

bigInt operator+(bigInt lhs, const bigInt& rhs)
{
    lhs += rhs;
    return lhs;
}

bigInt& bigInt::operator-=(const bigInt& other)
{
    if (sign == '+')
    {
        switch (other.sign)
        {
        case '+': // +(left - right)
            if (isLess(value, other.value))
            {
                value = Sub(other.value, value);
                sign = '-';
            }
            else
                value = Sub(value, other.value);
            break;
        case '-': // +(left + right)
            value = Add(value, other.value);
            break;
        }
    }
    else if (sign == '-')
    {
        switch (other.sign)
        {
        case '+': // -(left + right)
            value = Add(value, other.value);
            break;
        case '-': // +(right - left)
            if (isLess(other.value, value))
                value = Sub(value, other.value);
            else
            {
                value = Sub(other.value, value);
                sign = '+';
            }
            break;
        }
    }

    return *this;
}

bigInt operator-(bigInt lhs, const bigInt& rhs)
{
    lhs -= rhs;
    return lhs;
}

bigInt& bigInt::operator*=(const bigInt& other)
{
    if (sign == '+' && other.sign == '-')
        sign = '-';
    else if (sign == '-' && other.sign == '-')
        sign = '+';

    value = Mul(value, other.value);

    return *this;
} 

bigInt operator*(bigInt lhs, const bigInt& rhs)
{
    lhs *= rhs;
    return lhs;
}

bigInt operator-(bigInt _bigint)
{
    if (_bigint.get_sign() == '-')
        _bigint.set_sign('+');
    else
        _bigint.set_sign('-');
    
    return _bigint;
}

bool operator<(const bigInt& lhs, const bigInt& rhs)
{
    vector<uint8_t> left = lhs.get_value();
    vector<uint8_t> right = rhs.get_value();
    char ls = lhs.get_sign();
    char rs = rhs.get_sign();

    if ((ls == '-') && (rs == '+'))
        return true;
    else if ((ls == '+') && (rs == '-'))
        return false; 
    else if ((ls == '-') && (rs == '-'))
        return !isLess(left, right);

    return isLess(left, right);;
}

bool operator<=(const bigInt& lhs, const bigInt& rhs)
{
    if ((lhs == rhs) || (lhs < rhs))
        return true;
    return false;
}

bool operator>(const bigInt& lhs, const bigInt& rhs)
{
    if ((lhs.get_sign() == '-') && (rhs.get_sign() == '+'))
        return false;
    else if ((lhs.get_sign() == '+') && (rhs.get_sign() == '-'))
        return true;

    if (lhs.size() > rhs.size())
        return true;
    else if (lhs.size() < rhs.size())
        return false;

    if ((lhs.get_sign() == '-') && (rhs.get_sign() == '-'))
        return (lhs < rhs);
    
    return !(lhs < rhs);
}

bool operator>=(const bigInt& lhs, const bigInt& rhs)
{
    if ((lhs == rhs) || (lhs > rhs))
        return true;
    return false;
}

bool operator==(const bigInt& lhs, const bigInt& rhs)
{
    if ((lhs.size() != rhs.size()) || (lhs.get_sign() != rhs.get_sign()))
        return false;
    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (lhs.get(i) != rhs.get(i))
            return false;
    }

    return true;
}

bool operator!=(const bigInt& lhs, const bigInt& rhs)
{
    return !(lhs == rhs);
}


int main()
{

    // Test Constructor with default
    bigInt defaultInt;
    cout << "Default Constructor (0): " << defaultInt << "\n";

    // Test Constructor with int64_t
    bigInt int64(-9223372036854775807); // 
    cout << "Constructor with int64_t (" << int64 << "): " << int64 << "\n";

    // Test Constructor with string 
    bigInt stringInt("100000000000000000000"); 
    cout << "Constructor with string (" << stringInt << "): " << stringInt << "\n";
    bigInt invalidString("-000010000");
    cout << "Constructor with 0 leading string (" << invalidString << "): " << invalidString << "\n";

    // Test Constructor with = operator
    bigInt opInt;
    bigInt opString;
    opInt = 123445;
    opString = "-64443221";
    cout << "Constructor with = (" << opInt << "), (" << opString << "): " << opInt << ", " << opString << "\n";

    // Test Addition
    bigInt sum = int64 + stringInt;
    cout << "Addition (" << int64 << " + " << stringInt << "): " << sum << "\n";
    
    // Test Subtraciton
    bigInt difference = stringInt - int64;
    cout << "Subtraction (" << stringInt << " - " << int64 << "): " << difference << "\n";

    // Test Multiplication
    bigInt product = int64 * stringInt;
    cout << "Multiplication (" << int64 << " * " << stringInt << "): " << product << "\n";

    // Test Negation
    bigInt negated = -stringInt;
    cout << "Negation (" << stringInt << "): " << negated << "\n";

    // Test Comparison
    cout << "Comparison (" << int64 << " == " << stringInt << "): " << (int64 == stringInt) << "\n";
    cout << "Comparison (" << int64 << " != " << stringInt << "): " << (int64 != stringInt) << "\n";
    cout << "Comparison (" << int64 << " < " << stringInt << "): " << (int64 < stringInt) << "\n";
    cout << "Comparison (" << int64 << " > " << stringInt << "): " << (int64 > stringInt) << "\n";
    cout << "Comparison (" << int64 << " <= " << stringInt << "): " << (int64 <= stringInt) << "\n";
    cout << "Comparison (" << int64 << " >= " << stringInt << "): " << (int64 >= stringInt) << "\n";

}
